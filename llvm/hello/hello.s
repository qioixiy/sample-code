	.text
	.file	"hello.bc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$.Lstr, %edi
	callq	puts
	xorl	%eax, %eax
	popq	%rdx
	retq
.Ltmp1:
	.size	main, .Ltmp1-main
	.cfi_endproc

	.type	.Lstr,@object           # @str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lstr:
	.asciz	"hello world!"
	.size	.Lstr, 13


	.ident	"clang version 3.5.0 (http://llvm.org/git/clang.git d31bc8bc756b3734c79e3748627938ce25b8f30c) (http://llvm.org/git/llvm.git 7921239c411aeeaef55998cc64495aa1ea1a3ea3)"
	.section	".note.GNU-stack","",@progbits
