GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours
GLOBAL setFormat

section .text

setFormat:
	push rbp
	mov rbp,rsp
	mov al,0Bh
	out 70h,al
	in al,71h
	or al,00000100b
	out 71h,al
	mov rsp,rbp
	pop rbp
	ret

getSeconds:
	push rbp
	mov rbp,rsp
	mov al,0
	out 70h,al
	in al,71h

	movzx rax,ax
	mov rsp,rbp
	pop rbp
	ret

getMinutes:
	push rbp
	mov rbp,rsp
	mov al,2
	out 70h,al
	in al,71h
	movzx rax,al
	mov rsp,rbp
	pop rbp
	ret

getHours:
	push rbp
	mov rbp,rsp
	mov al,4
	out 70h,al
	in al,71h
	movzx rax,al
	mov rsp,rbp
	pop rbp
	ret

getMonth:
	push rbp
	mov rbp,rsp
	mov al,8
	out 70h,al
	in al,71h
	movzx rax,al
	mov rsp,rbp
	pop rbp
	ret

getYear:
	push rbp
	mov rbp,rsp
	mov al,9
	out 70h,al
	in al,71h
	movzx rax,al
	mov rsp,rbp
	pop rbp
	ret

section .data
section .bss
