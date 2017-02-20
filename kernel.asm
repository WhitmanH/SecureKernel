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


extern kmain ;;Found in kernel.c
extern soteria
extern keyboard_handler_main

section .text
entry: jmp startSoteria
		;To enable multiboot on Linux GRUB based systems, following parameters declared
		align 4
		dd 0x1BADB002 ;Magic field, declares header
		dd 0x00 ;Flags field, no flags set.
		dd - (0x1BADB002 + 0x00) ;Checksum for all parameters, magic + flag + checksum should be zero.


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

section .bss
resb 8192 ;Specifying 8kb for the kernel's stack
stack_space: