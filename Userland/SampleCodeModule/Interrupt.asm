GLOBAL int_80h

section .text

%macro pushState 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    mov rbp,rsp
%endmacro

%macro popState 0
    mov rsp,rbp
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro


int_80h:
    pushState 0

    mov rax,rdi
    mov rbx,rsi
    mov rcx,rdx
    int 80h

    popState 0
    ret