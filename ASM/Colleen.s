;comment1
section .data
	str: db ";comment1%1$csection .data%1$c	str: db %2$c%3$s%2$c%1$csection .text%1$c	global main%1$c	extern printf%1$cmain:%1$c	;comment2%1$c	push rbp%1$c	mov rbp, rsp%1$c	lea rcx, [str]%1$c	mov rdx, 0x22%1$c	mov rsi, 0x0A%1$c	lea rdi, [str]%1$c	call printf%1$c	call func%1$c	leave%1$c	ret%1$cfunc:%1$c	leave%1$c	ret%1$c"
section .text
	global main
	extern printf
main:
	;comment2
	push rbp
	mov rbp, rsp
	lea rcx, [str]
	mov rdx, 0x22
	mov rsi, 0x0A
	lea rdi, [str]
	call printf
	call func
	leave
	ret
func:
	leave
	ret
