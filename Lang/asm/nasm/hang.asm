
struc sigaction
    .sa_handler  resq 1
    .sa_flags    resq 1
    .sa_restorer resq 1
    .sa_mask     resq 1
endstruc

section .bss
act resb sigaction_size

section .text
global _start
	lea rax, [handler]
	mov [act + sigaction.sa_handler], rax
	mov [act + sigaction.sa_flags], dword 0x04000000  ; SA_RESTORER
	lea rax, [restorer]
	mov [act + sigaction.sa_restorer], rax

	mov rax, 0x0d  ; sys_rt_sigaction
	mov rdi, 0x0f  ; SIGTERM
	lea rsi, [act]
	mov rdx, 0x00
	mov r10, 0x08
	syscall

	mov rax, 0x22  ; sys_pause
	syscall

handler:
	ret

restorer:
    mov rax, 0x0f  ; sys_rt_sigreturn
    syscall
