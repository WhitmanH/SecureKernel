;; Haley Whitman and Andrew Hill
;; Derived from Arjun Sreedharan

;;kernal.asm 
bits 32 ;This is NASM specific, specifying a 32bit system.

global startOS
global startSoteria
global entry
global read_port
global write_port
global load_idt
global keyboard_handler

;Memory
global read_cr0
global write_cr0
global read_cr3
global write_cr3

extern kmain ;;Found in kernel.c
extern soteria
extern keyboard_handler_main


; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0             ; align loaded modules on page boundaries
MEMINFO     equ  1<<1             ; provide memory map
 
; This is the virtual base address of kernel space. It must be used to convert virtual
; addresses into physical addresses until paging is enabled. Note that this is not
; the virtual address where the kernel image itself is loaded -- just the amount that must
; be subtracted from a virtual address to get a physical address.
KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's 4MB PTE.


section .data
align 0x1000
BootPageDirectory:
    ; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
    ; All bits are clear except the following:
    ; bit 7: PS The kernel page is 4MB.
    ; bit 1: RW The kernel page is read/write.
    ; bit 0: P  The kernel page is present.
    ; This entry must be here -- otherwise the kernel will crash immediately after paging is
    ; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0  ; Pages after the kernel image.





section .text
align 4
MultiBootHeader:
	dd 0x1BADB002 ;Magic field, declares header
	dd 0x00 ;Flags field, no flags set.
	dd - (0x1BADB002 + 0x00) ;Checksum for all parameters, magic + flag + checksum should be zero.


entry equ (_entry - 0xC0000000)


_entry: 
	;jmp startSoteria
	;To enable multiboot on Linux GRUB based systems, following parameters declared
	;align 4
	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
    mov cr3, ecx                                        ; Load Page Directory Base Register.
 
    mov ecx, cr4
    or ecx, 0x00000010                          ; Set PSE bit in CR4 to enable 4MB pages.
    mov cr4, ecx
 
    mov ecx, cr0
    or ecx, 0x80000000                          ; Set PG bit in CR0 to enable paging.
    mov cr0, ecx
 
    ; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of StartInHigherHalf which is
    ; approximately 0xC0100000.
    lea ecx, [startSoteria]
    jmp ecx 
	


startOS:
	cli ;block all interrupts, causing OS to hang after execution.\
	mov esp, stack_space ;Set stack pointer
	call kmain ;; C code for initializing both the kernel and the keyboard inputs and outputs
	hlt ;halt the cpu

startSoteria:
	call soteria ;;Security Kernel
	jmp startOS


read_port: ;; Initializing ports for individual keyboard inputs
	mov edx, [esp + 4]
	in al, dx
	ret

write_port: ; Initializing ports for individual keyboard outputs on the main window
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

load_idt: ; Loading the Interrupt Descripter Table (IDT), to handle keyboard interrupts and
		  ; avoiding a busy CPU
	mov edx, [esp + 4]
	lidt [edx]
	sti ; this initiates interrupts
	ret

keyboard_handler: ; for all currently implemented interrupts
	call keyboard_handler_main
	iretd

;;MEMORY MANAGEMENT CR0 and CR3 Registers
;CR0, 32bits, controls protections
read_cr0:
	mov eax, cr0
	ret

write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	ret
;CR3, 32bits, the physical base address of the memory.	
read_cr3:
	mov eax, cr3
	ret

write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	ret

section .bss
resb 8192 ;Specifying 8kb for the kernel's stack
stack_space: