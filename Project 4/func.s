	.text
	.globl count1
	

	# int count1(char p[], int size, int limit)
count1:

	#Setup

	push %ebp
	push %edi
	mov $0, %edi
	mov $0, %ebp

	mov 12(%esp), %ecx #array
	mov 16(%esp), %edx #size
	mov 20(%esp), %eax #limit
	
loop1:
	
	cmpl $0, %edx 		 #Compare increment to the length of the array
	je endprogram		 
	
	cmp %eax, (%ecx)     #compare character to max
	jl incrementcount          #if charcter < max, count++
	
	sub $1, %edx    	 #Increment the count
	add $4, %ecx         #Go to the next character in the array
	
	jmp loop1
	
incrementcount:
	add $1, %edi      #Increment the count
	sub $1, %edx 	  #Decrement the array
	add $4, %ecx      #Go to the next character in the array
	jmp loop1
	
endprogram:
	mov %edi, %eax
	pop %ebp
	pop %edi
	ret



	.globl count2

count2:

	#Setup
	push %ebp
	push %edi
	mov $0, %edi
	mov $0, %ebp

	mov 12(%esp), %ecx #array
	mov 16(%esp), %edx #size
	mov 20(%esp), %eax #limit

	jmp loop2

loop2:

	cmpl $0, %edx 		 #Compare increment to the length of the array
	je endprogram		

	mov %edi, %ebp		 #Move the count to ebp, then add 1 to it
	add $1, %ebp 
	
	cmp %eax, (%ecx)     #Compare character to max
	cmovl %ebp, %edi     #If charcter < max, count++
	
	sub $1, %edx   	 	 #Decrement the array
	add $4, %ecx         #Go to the next character in the array
	
	jmp loop2

endprogram2:

	mov %edi, %eax
	pop %ebp
	pop %edi
	ret

