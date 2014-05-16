#
# An x86-32 assembly program that echos one character
#

	# declare external functions
	.extern getchar		# get one character from the console
	.extern putchar		# write one character to the console

	# declare main as global
	.global main

	# the main program
main:
	call getchar		# get a character
	push %eax		# push argument on the stack

	cmp $-1, %eax
	je endprogram



#if the character is lower case, jump to makeupper
	cmp $98, %eax
	je makeupper
	cmp $109, %eax
	je makeupper
	cmp $97, %eax
	je makeupper
#if the character is upper case, jump to makelower
	cmp $65, %eax
	je makelower
	cmp $77, %eax
	je makelower
	cmp $66, %eax
	je makelower



#the rest of our main program
	call putchar

	add $4,%esp		# pop the stack
	jmp main		#loop

	mov $0,%eax		

	ret			#return
	

endprogram:

	add $4,%esp		# pop the stack
	mov $0, %eax
	ret


makeupper:

	add $4,%esp		# pop the stack
	
	sub $32, %eax
	push %eax
	call putchar
	add $4,%esp		# pop the stack

	jmp main

makelower:

	add $4,%esp		# pop the stack
	
	add $32, %eax
	push %eax
	call putchar
	add $4,%esp		# pop the stack

	jmp main


