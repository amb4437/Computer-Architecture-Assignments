.data       
array: .fill 258,1,48 #fill 258 spaces with 1 byte values of 48 (ascii 0)


.text               
.global count         
count:
 
 	mov $array, %edx
	mov 4(%esp), %ecx #Move first pointer to %ecx
	
	##Check if null
	cmp $0, %ecx
	je endprogram
	
	
    movb (%ecx), %al  #Get the first value. Sucess, gets correct ascii
	jmp loop1
	
loop1:
	
	mov (%ecx), %al
	cmpb $0, %al
	je setup
	
	#increment array counts
	add $1, (%edx, %eax, 1)
	
	#Next character in string
	add $1, %ecx
	movb (%ecx), %al  #Get the first value. Sucess, gets correct ascii
	
	#Repeat loop
	jmp loop1

	
setup:

	#setting up for loop2
	mov $0, %ecx 
	jmp loop2

loop2:

	movb (%edx, %ecx, 1), %al  #move count of array index to eax

	cmp $255, %ecx	#Check if it's the last index
	je endprogram
	
	cmp %eax, 257(%edx)  #Check if currentcount > maxcount
	jl setmax
	
	cmp %eax, 257(%edx)  #If counts are equal, pick one with lower ascii
	je charmax
	
	add $1, %ecx		#Increment the array
	jmp loop2
	
setmax:

	movb %al, 257(%edx)  ## move the count into the max count
	movb %cl, 255(%edx)  ## move the character into max char
	add $1, %ecx
	jmp loop2
	
charmax:
	cmpb %cl, 255(%edx)
	jg newchar
	add $1, %ecx
	jmp loop2
	
newchar:
	movb %cl, 255(%edx)  # move the character into max char
	add $1, %ecx
	jmp loop2
	
endprogram:
	movb 255(%edx), %al  
	ret
	