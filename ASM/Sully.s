section .data
	str: db "section .data%1$c	str: db %2$c%3$s%2$c,0x0%1$c	mode: db %2$cw+%2$c,0x0%1$c	file_fmt: db %2$cSully_%%d.s%2$c,0x0%1$c	launch_fmt: db %2$cnasm -f elf64 -dOFFSET=0 Sully_%%1$d.s && gcc -no-pie Sully_%%1$d.o -o Sully_%%1$d && ./Sully_%%1$d%2$c,0x0%1$c%1$csection .bss%1$c	file: resb 1000%1$c	launch: resb 1000%1$c%1$csection .text%1$c	global main%1$c	extern fprintf%1$c	extern fopen%1$c	extern fclose%1$c	extern exit%1$c	extern sprintf%1$c	extern system%1$c%1$cEXIT:%1$c	mov rdi, 1%1$c	call exit%1$c%1$cmain:%1$c	push rbp%1$c	mov rbp, rsp%1$c	mov r12, %4$d%1$c	add r12, OFFSET%1$c	cmp r12, 0%1$c	jle EXIT%1$c	sub r12, 1%1$c%1$c	mov rdi, file%1$c	lea rsi, [file_fmt]%1$c	mov rdx, r12%1$c	xor rax, rax%1$c	call sprintf%1$c	mov rbx, rax%1$c	cmp rbx, 0%1$c	je EXIT%1$c%1$c	mov rdi, file%1$c	mov rsi, mode%1$c	call fopen%1$c	mov rbx, rax%1$c	cmp rbx, 0%1$c	je EXIT%1$c%1$c	mov rdi, rbx%1$c	lea rsi, [str]%1$c	mov rdx, 0x0A%1$c	mov rcx, 0x22%1$c	lea r8, [str]%1$c	mov r9, r12%1$c	xor rax, rax%1$c	call fprintf%1$c	mov rdi, rbx%1$c	call fclose%1$c%1$c	mov rdi, launch%1$c	lea rsi, [launch_fmt]%1$c	mov rdx, r12%1$c	xor rax, rax%1$c	call sprintf%1$c%1$c	mov rdi, launch%1$c	call system%1$c%1$c	leave%1$c	ret%1$c",0x0
	mode: db "w+",0x0
	file_fmt: db "Sully_%d.s",0x0
	launch_fmt: db "nasm -f elf64 -dOFFSET=0 Sully_%1$d.s && gcc -no-pie Sully_%1$d.o -o Sully_%1$d && ./Sully_%1$d",0x0

section .bss
	file: resb 1000
	launch: resb 1000

section .text
	global main
	extern fprintf
	extern fopen
	extern fclose
	extern exit
	extern sprintf
	extern system

EXIT:
	mov rdi, 1
	call exit

main:
	push rbp
	mov rbp, rsp
	mov r12, 5
	add r12, OFFSET
	cmp r12, 0
	jle EXIT
	sub r12, 1

	mov rdi, file
	lea rsi, [file_fmt]
	mov rdx, r12
	xor rax, rax
	call sprintf
	mov rbx, rax
	cmp rbx, 0
	je EXIT

	mov rdi, file
	mov rsi, mode
	call fopen
	mov rbx, rax
	cmp rbx, 0
	je EXIT

	mov rdi, rbx
	lea rsi, [str]
	mov rdx, 0x0A
	mov rcx, 0x22
	lea r8, [str]
	mov r9, r12
	xor rax, rax
	call fprintf
	mov rdi, rbx
	call fclose

	mov rdi, launch
	lea rsi, [launch_fmt]
	mov rdx, r12
	xor rax, rax
	call sprintf

	mov rdi, launch
	call system

	leave
	ret
