#$-1, %eax
# An x86-32 assembly program that echos one character
#
.data       
value:
         .long   2

	.globl check
	.globl _check

	# int check(Node* p)
check:
_check:

	mov $0, %eax	   #our count
	
	mov 4(%esp), %edx  #Pointer #1: edx
	mov 4(%esp), %ecx  #Pointer #2: ecx

	#empty list
	cmp $0, %edx	#check if it's the last element in the list
	je endprogram	
	
	jmp checkrun

checkrun:

	mov (%edx), %edx		#move to next node
	add $1, %eax			#increment the count
	cmp $0, %edx			#check if that was the last element in the array
	je endprogram

	mov (%ecx), %ecx		#move to next node
	cmp $0, %ecx			#Check if it was the last node
	je endprogram
	mov (%ecx), %ecx		#move to next node		
	add $1, %eax			#increment the count
	cmp $0, %ecx			#check if it was the last node
	je endprogram

	cmp %ecx, %edx		#check if it's a cycle
	je iscycle

			
	jmp checkrun		#loop around


	.globl reverse
	.globl _reverse
	# void reverse(p)  

iscycle:
	mov $-1, %eax		#Return -1 because it's a cycle
	ret

endprogram:
	mov %eax, %eax
	ret


reverse:
_reverse:

	mov 4(%esp), %ecx  #ecx: pointer 1
	mov 4(%esp), %edx  #edx: pointer 2
	
	cmp $0, %ecx   	#check if it's an empty list
	je endreverse

	jmp pushloop


pushloop:

	cmp $0, %ecx         #we reached the end of our linked list
	je poploop
	push 4(%ecx)		#push the element on to the stack
	mov (%ecx), %ecx	#move to the next element
	jmp pushloop         #loop around


poploop:
	pop 4(%edx)
	mov (%edx), %edx
	cmp $0, %edx
	je endreverse
	jmp poploop

endreverse:
	ret
