.data
    x: .long 100
    y: .byte 500

    .global indepAdd32Ops
indepAdd32Ops:
 	movd x, %XMM0

 	.rept 1000
 	paddd %XMM0, %XMM1
 	paddd %XMM0, %XMM2
 	paddd %XMM0, %XMM3
 	paddd %XMM0, %XMM4
 	paddd %XMM0, %XMM5
 	paddd %XMM0, %XMM6
 	paddd %XMM0, %XMM7

 	.endr

 	emms

 	mov $28000, %eax
    ret

	.global indepAdd8Ops
indepAdd8Ops:

    movd y, %XMM0

 	.rept 1000
 	paddb %XMM0, %XMM1
 	paddb %XMM0, %XMM2
 	paddb %XMM0, %XMM3
 	paddb %XMM0, %XMM4
 	paddb %XMM0, %XMM5
 	paddb %XMM0, %XMM6
 	paddb %XMM0, %XMM7

 	.endr

 	emms

 	mov $112000, %eax
    ret

	.global indepLoads
indepLoads:
    push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi
	push %ebp

	.rept 1000
	mov x, %eax
	mov x, %ebx
	mov x, %ecx
	mov x, %edx
	mov x, %esi
	mov x, %edi
	mov x, %ebp
	.endr

	pop %ebp
	pop %edi
	pop %esi
	pop %edx
	pop %ecx
	pop %ebx

	mov $7000,%eax
	ret

	.global depLoads
depLoads:

	.rept 10000
	mov x, %eax
	mov %eax, x
	.endr

	mov $20000,%eax
	ret

	.global indepMuls
indepMuls:

    push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi
	push %ebp

	.rept 1000
	imul $1, %eax
	imul $1, %ebx
	imul $1, %ecx
	imul $1, %esi
	imul $1, %edi
	imul $1, %ebp
	imul $1, %edx
	.endr

	pop %ebp
	pop %edi
	pop %esi
	pop %edx
	pop %ecx
	pop %ebx

	mov $7000, %eax
	ret

	.global depMuls
depMuls:
    mov    $1, %eax
    mov    $1, %ecx

	.rept 10000
	mul %ecx
	.endr

    mov $10000, %eax
	ret

	.global indepDivs
indepDivs:

	push %ebx

	.rept 10000
	mov $1, %eax
	cdq
	mov $1, %ebx
	idiv %ebx
	.endr

	pop %ebx

	mov $10000, %eax
	ret

	.global depDivs
depDivs:

 	push %ebx
	push %esi
	push %edi
	push %ebp

    push %ecx
	push %edx
    mov $100, %eax
    

	.rept 10000
	mov x, %ecx
	cdq
	div %ecx
	div %ebx
	div %esi
	div %edi
	div %ebp
	.endr

	pop %edx
	pop %ecx

	mov $10000, %eax

	ret

	.global depUncond
depUncond:

    mov $1, %eax
    cmp $0, %eax

    .rept 10000
    jle end
    .endr

    mov $10000, %eax
    ret

	.global depTaken
depTaken:

    mov $100, %eax
    cmp $100, %eax

    .rept 5000
    je 1f

    1:
    
    .endr

    mov $5000, %eax
    ret

	.global depUntaken
depUntaken:

	mov $100, %eax
    cmp $99, %eax

    .rept 5000
    jle 1f

    1:

    .endr

    mov $5000, %eax
    ret

	.globl indepAdds
indepAdds:
    push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi
	push %ebp

	.rept 1000
	add $1,%eax
	add $1,%ebx
	add $1,%ecx
	add $1,%edx
	add $1,%esi
	add $1,%edi
	add $1,%ebp
	.endr

	pop %ebp
	pop %edi
	pop %esi
	pop %edx
	pop %ecx
	pop %ebx

	mov $7000,%eax
	ret

	.globl depAdds
depAdds:

    mov $0, %eax

	.rept 10000
	add $1, %eax
	.endr

	ret

