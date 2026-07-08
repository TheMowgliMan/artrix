	.section .text

	.extern handle_int

	.macro pusha
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	pushq %rdi
	pushq %rsi
	pushq %rbp
	pushq %r8
	pushq %r9
	pushq %r10
	pushq %r11
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	.endm

	.macro popa
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rbp
	popq %rsi
	popq %rdi
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax
	.endm

	.macro dispatch
	cld
	movq %rsp, %rdi

	sti
	call handle_int
	cli
	nop
	.endm

	.macro isr vec:req
	.global isr\vec:
isr\vec:
	cli
	nop

	pushq $0
	pushq $\vec
	pusha

	dispatch

	popa
	add $16, %rsp

	sti
	iretq

	.macro isrerr vec:req
isr/vec:
	cli
	nop

	pushq $\vec
