;42
%define PROGRAM main:
%define EXIT call exit
%define RETURN ret

section .data
	str: db ";42%1$c%3$cdefine PROGRAM main:%1$c%%define EXIT call exit%1$c%%define RETURN ret%1$c%1$csection .data%1$c	str: db %2$c%4$s%2$c,0x0%1$c	file: db %2$cGrace_kid.s%2$c,0x0%1$c	mode: db %2$cw+%2$c,0x0%1$c%1$csection .text%1$c	global main%1$c	extern fprintf%1$c	extern fopen%1$c	extern exit%1$c%1$cERROR:%1$c	mov rdi, 1%1$c	EXIT%1$c%1$cPROGRAM%1$c	push rbp%1$c	mov rbp, rsp%1$c	lea rsi, [mode]%1$c	lea rdi, [file]%1$c	call fopen%1$c	cmp rax, 0%1$c	je ERROR%1$c	lea r9, [str]%1$c	mov r8, 0x25%1$c	mov rcx, 0x22%1$c	mov rdx, 0x0A%1$c	lea rsi, [str]%1$c	mov rdi, rax%1$c	call fprintf%1$c	mov rax, 0%1$c	leave%1$c	RET%1$c",0x0
	file: db "Grace_kid.s",0x0
	mode: db "w+",0x0

section .text
	global main
	extern fprintf
	extern fopen
	extern exit

ERROR:
	mov rdi, 1
	EXIT

PROGRAM
	push rbp
	mov rbp, rsp
	lea rsi, [mode]
	lea rdi, [file]
	call fopen
	cmp rax, 0
	je ERROR
	lea r9, [str]
	mov r8, 0x25
	mov rcx, 0x22
	mov rdx, 0x0A
	lea rsi, [str]
	mov rdi, rax
	call fprintf
	mov rax, 0
	leave
	RET
