	.section .text

	.global set_gdt
set_gdt:
	cli
	lgdt (%rdi)
	ret

	.global reload_sgmt
reload_sgmt:
	# Reload CS
	pushq $0x0008
	lea reload_cs(%rip), %rax
	pushq %rax
	lretq
reload_cs:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ret

	.global load_tss
load_tss:
	ltr %di
	ret
