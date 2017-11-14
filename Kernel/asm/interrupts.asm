
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL printRegisters

GLOBAL _int80Handler
GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
;GLOBAL _int80Handler
GLOBAL _exception6Handler
GLOBAL _exception0Handler
GLOBAL _exception4Handler

GLOBAL _exception0Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sys_handler
EXTERN printRegister
EXTERN printString

SECTION .text

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
%endmacro

%macro popState 0
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

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro irqHandlerMaster 0
	pushState

	mov rdi, %0 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro


%macro exceptionHandler 1
	mov [aux], rsp
	pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, [aux]
	call exceptionDispatcher

	mov rax, [aux]
	call printRegisters

	mov rsp, [aux]
	mov qword [rsp], 0x0000000000400000

	iretq
%endmacro


;Recibe en rax el rsp desde donde se pushearon los registros (Similar al implementado por pure64)
printRegisters:
	pushState
	mov rbx, 15
	mov r15, rax
	sub r15, 8

	.loop:
		cmp rbx, 0
		jz .finish
		mov rdi, s0
		mov rax, 15
		sub rax, rbx
		mov rcx, 4 ; cada string tiene 4
		mul rcx
		add rdi, rax
		call printString
		mov rdi, [r15]
		mov rsi, rbx
		call printRegister
		sub r15, 8
		dec rbx
		jmp .loop

	.finish:
		popState
		ret

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

;SYS
_int80Handler:
	pushState
	call sys_handler
	popState
	iretq

;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Overflow Exception
_exception4Handler:
	exceptionHandler 4

;Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6


haltcpu:
	cli
	hlt
	ret

SECTION .data
	s0: db "RAX", 0
	s1: db "RBX", 0
	s2: db "RCX", 0
	s3: db "RDX", 0
	s4: db "RBP", 0
	s5: db "RDI", 0
	s6: db "RSI", 0
	s7: db "R8", 0, 0
	s8: db "R9", 0, 0
	s9: db "R10", 0
	s10: db "R11", 0
	s11: db "R12", 0
	s12: db "R13", 0
	s13: db "R14", 0
	s14: db "R15", 0

SECTION .bss
	aux resq 1
