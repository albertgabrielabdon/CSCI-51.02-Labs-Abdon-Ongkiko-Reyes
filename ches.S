	.file	"Lab5_AbdonOngkikoReyes_code.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.globl	caseAmt
	.bss
	.align 4
	.type	caseAmt, @object
	.size	caseAmt, 4
caseAmt:
	.zero	4
	.globl	pointAmt
	.align 4
	.type	pointAmt, @object
	.size	pointAmt, 4
pointAmt:
	.zero	4
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.zero	4
	.globl	j
	.align 4
	.type	j, @object
	.size	j, 4
j:
	.zero	4
	.globl	mDistance
	.align 4
	.type	mDistance, @object
	.size	mDistance, 4
mDistance:
	.zero	4
	.section	.text._ZN5PointC2Ev,"axG",@progbits,_ZN5PointC5Ev,comdat
	.align 2
	.weak	_ZN5PointC2Ev
	.type	_ZN5PointC2Ev, @function
_ZN5PointC2Ev:
.LFB2645:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2645:
	.size	_ZN5PointC2Ev, .-_ZN5PointC2Ev
	.weak	_ZN5PointC1Ev
	.set	_ZN5PointC1Ev,_ZN5PointC2Ev
	.section	.text._ZN5PointC2Eiii,"axG",@progbits,_ZN5PointC5Eiii,comdat
	.align 2
	.weak	_ZN5PointC2Eiii
	.type	_ZN5PointC2Eiii, @function
_ZN5PointC2Eiii:
.LFB2648:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	%ecx, -20(%rbp)
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	-16(%rbp), %edx
	movl	%edx, 4(%rax)
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2648:
	.size	_ZN5PointC2Eiii, .-_ZN5PointC2Eiii
	.weak	_ZN5PointC1Eiii
	.set	_ZN5PointC1Eiii,_ZN5PointC2Eiii
	.text
	.globl	main
	.type	main, @function
main:
.LFB2650:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$112, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	leaq	caseAmt(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt3cin(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSirsERi@PLT
	jmp	.L4
.L17:
	movq	%rsp, %rax
	movq	%rax, %r14
	leaq	pointAmt(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt3cin(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSirsERi@PLT
	movl	pointAmt(%rip), %eax
	movslq	%eax, %rbx
	movabsq	$768614336404564650, %rax
	cmpq	%rbx, %rax
	jb	.L5
	movq	%rbx, %rax
	addq	%rax, %rax
	addq	%rbx, %rax
	salq	$2, %rax
	movq	%rax, %rdi
	call	_Znam@PLT
	movq	%rax, %r13
	movq	%r13, %r12
	leaq	-1(%rbx), %rax
	movq	%rax, %rbx
	jmp	.L8
.L5:
	movq	-40(%rbp), %rax
	subq	%fs:40, %rax
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	call	__cxa_throw_bad_array_new_length@PLT
.L9:
	movq	%r12, %rdi
	call	_ZN5PointC1Ev
	subq	$1, %rbx
	addq	$12, %r12
.L8:
	testq	%rbx, %rbx
	jns	.L9
	movq	%r13, -112(%rbp)
	movl	pointAmt(%rip), %eax
	leal	-1(%rax), %ebx
	movslq	%ebx, %rax
	subq	$1, %rax
	movq	%rax, -104(%rbp)
	movslq	%ebx, %rax
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -96(%rbp)
	movl	$0, j(%rip)
	jmp	.L10
.L12:
	leaq	-136(%rbp), %rax
	movq	%rax, %rsi
	leaq	_ZSt3cin(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSirsERi@PLT
	movq	%rax, %rdx
	leaq	-132(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSirsERi@PLT
	movq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSirsERi@PLT
	movl	-128(%rbp), %ecx
	movl	-132(%rbp), %edx
	movl	-136(%rbp), %esi
	leaq	-52(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN5PointC1Eiii
	movl	j(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	-52(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	-44(%rbp), %edx
	movl	%edx, 8(%rax)
	movl	j(%rip), %eax
	testl	%eax, %eax
	jle	.L11
	movl	j(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
	movl	j(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	-12(%rax), %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -64(%rbp)
	movq	-72(%rbp), %rax
	movl	(%rax), %ecx
	movq	-64(%rbp), %rax
	movl	(%rax), %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	movl	%eax, %ecx
	movq	-72(%rbp), %rax
	movl	4(%rax), %esi
	movq	-64(%rbp), %rax
	movl	4(%rax), %edx
	movl	%esi, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	leal	(%rcx,%rax), %esi
	movq	-72(%rbp), %rax
	movl	8(%rax), %ecx
	movq	-64(%rbp), %rax
	movl	8(%rax), %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	addl	%esi, %eax
	movl	%eax, mDistance(%rip)
	movl	j(%rip), %eax
	leal	-1(%rax), %edx
	movl	mDistance(%rip), %ecx
	movq	-96(%rbp), %rax
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
.L11:
	movl	j(%rip), %eax
	addl	$1, %eax
	movl	%eax, j(%rip)
.L10:
	movl	j(%rip), %edx
	movl	pointAmt(%rip), %eax
	cmpl	%eax, %edx
	jl	.L12
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -120(%rbp)
	movslq	%ebx, %rax
	leaq	0(,%rax,4), %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -80(%rbp)
	jmp	.L13
.L14:
	movq	-120(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -124(%rbp)
	movl	-124(%rbp), %eax
	movl	%eax, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSolsEi@PLT
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	addq	$4, -120(%rbp)
.L13:
	movq	-120(%rbp), %rax
	cmpq	-80(%rbp), %rax
	jne	.L14
	movl	caseAmt(%rip), %eax
	leal	-1(%rax), %edx
	movl	i(%rip), %eax
	cmpl	%eax, %edx
	jle	.L15
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
.L15:
	cmpq	$0, -112(%rbp)
	je	.L16
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L16:
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
	movq	%r14, %rsp
.L4:
	movl	i(%rip), %edx
	movl	caseAmt(%rip), %eax
	cmpl	%eax, %edx
	jl	.L17
	movl	$0, %eax
	movq	-40(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2650:
	.size	main, .-main
	.section	.rodata
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedImEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE:
	.byte	1
	.ident	"GCC: (GNU) 14.2.1 20250207"
	.section	.note.GNU-stack,"",@progbits
