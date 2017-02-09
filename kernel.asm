;; Haley Whitman and Andrew Hill
;; Derived from Arjun Sreedharan

;;kernal.asm 
bits 32 ;This is NASM specific, specifying a 32bit system.

global start
global entry
extern kmain ;;Found in kernel.c

section .text
entry: jmp start
		;To enable multiboot, following parameters declared
		align 4
		dd 0x1BADB002 ;Magic field, declares header
		dd 0x00 ;Flags field, no flags set.
		dd - (0x1BADB002 + 0x00) ;Checksum for all parameters, magic + flag + checksum should be zero.


start:
	cli ;block all interrupts, causing OS to hang after execution.
	mov esp, stack_space ;Set stack pointer
	call kmain
	hlt ;halt the cpu

section .bss
resb 8192 ;Specifying 8kb for the stack
stack_space: