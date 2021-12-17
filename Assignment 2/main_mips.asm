.data 
	input_number_of_elements:	.asciiz"Input value of N from 1 to 10: \n"
	input_a_message:		.asciiz"input value for a: \n"
	input_r_message:		.asciiz"input value for r: \n"
	ascending_order_message:	.asciiz"Ascending Order : Comparisons\n"
	descending_order_message:	.asciiz"Descending Order : \n"
	random_order_message:		.asciiz"Random Order : \n"
	array_num:			.space 40
	new_line:			.asciiz "\n"
	space_print:			.asciiz " "
	separator_print:		.asciiz": "
	
.text
	main:
											#prompt user to give input for N
		li		$v0, 4							# 4 denotes printing string system call
		la		$a0, input_number_of_elements
		syscall

											#Get input from user for N
		li		$v0, 5							#5 denotes getting integer input from system call
		syscall
		
											#Store the value of N in $s0
		move		$s0, $v0
		addi		$s7, $zero, 0
		
		la		$a1, array_num						# storing address of array in $a1
		addi		$a2, $s0, 0						#storing address of N in $a2
		
		jal		gp_number_func						#call function gp_number_func

											#End of Program
	li	$v0, 10									#10 denotes end of program system call
	syscall
	
	gp_number_func:
		addi		$sp, $sp, -32						#making space on stack for return address
		sw		$ra, 0($sp)

											#prompt user to give input for a
		li		$v0, 4							# 4 denotes printing string system call
		la		$a0, input_a_message
		syscall

											#get input from user for a
		li		$v0, 5							#5 denotes getting integer input from system call
		syscall
											#store the value of a in $s1
		move		$s1, $v0
											#prompt user to give input for r
		li		$v0, 4							# 4 denotes printing string system call
		la		$a0, input_r_message
		syscall
											#get input from user for r
		li		$v0, 5							#5 denotes getting integer input from system call
		syscall

											#store the value of r in $s2
		move		$s2, $v0
		addi		$t0, $zero, 0						#initializing $t0 to 0	$t0 = i = 0
		add		$t2, $s1, $zero						# $t2 stores value of previous element of array_num ie array_num[i - 1]
		sw		$s1, array_num($t0)					#storing value of a in the 0th index of array	array_num[0] = a
		addi		$t0, $t0, 4						#incrementing $t0 by 4 for each word
		addi		$t1, $t1, 1						#incrementing $t1 by 1 for next index	i = 1

											#loop for storing the gp in the array
		while_gp: 
			beq 	$t1, $s0, exit_gp_while					#if i = N then exit from loop
			mul	$t2, $t2, $s2						# $t2 = $t2 * r = array_num[i - 1] * r		
        	#addi $t3, $t2, 0
			sw	$t2, array_num($t0)					# array_num[i] = $t2
			addi	$t0, $t0, 4						#incrementing $t0 by 4 for each word
			addi	$t1, $t1, 1						# i++
			j	while_gp						#jump back to loop

		exit_gp_while:
			li	$v0, 4							# 4 denotes printing string system call
			la	$a0, ascending_order_message				# print message for showing ascending order sort time
			syscall
			jal	insertion_sort						#jump to insertion sort function

			li	$v0, 4							# 4 denotes printing string system call
			la	$a0, descending_order_message				# print message for showing descending order sort time
			syscall
			
			jal	desc_sort						# Sort array_num in descending order
			jal	insertion_sort						# jump to insertion sort function

			li	$v0, 4							# 4 denotes printing string system call
			la	$a0, random_order_message				# print message for showing random order sort time
			syscall
			
			jal	random_sort						# Sort array_num in random order
			jal	insertion_sort						#jump to insertion sort function

			lw	$ra, 0($sp)						# load return address in stack pointer
			addi	$sp, $sp, 32						# shift stack pointer back to its original place
			jr	$ra							#jump back to main

	insertion_sort:
		move		$s4, $s7						#compare_counter = 0
		addi		$t0, $zero, 1						# i = 1
		outer_loop:
			slt	$t3, $t0, $a2						#if i >= N then exit the loop
			beq	$t3, $zero, exit_outer
			sll	$t4, $t0, 2						# i * 4 for word
			add	$t4, $t4, $a1						# array_num[i]
			lw	$t5, 0($t4)						# $t5 = array_num[i] = num
			addi	$t1, $t0, -1						# tmp = i - 1
			inner_loop:
				slt		$t4, $t1, $zero				# if tmp is < 0 then exit the inner loop
				bne		$t4, $zero, exit_inner
				sll		$t4, $t1, 2
				add		$t4, $t4, $a1				# $t4 = array_num[tmp] address
				lw		$t4, 0($t4)				# $t4 = array_num[tmp]
				slt		$t6, $t5, $t4				# if num > array_num[tmp] then exit the inner loop
				beq		$t6, $zero, exit_inner
				addi		$t6, $t1, 1				#
				sll		$t6, $t6, 2				#
				add		$t6, $t6, $a1				#putting array_num[tmp + 1] = array_num[tmp]
				sw		$t4, 0($t6)				#
				addi		$t1, $t1, -1				#tmp--
				addi		$s4, $s4, 1				#compare_counter++
				j		inner_loop				#jump back to inner loop
			exit_inner:
				blt		$t1, $zero, counter_not_add		#if tmp >= 0 then compare_counter++
				addi		$s4, $s4, 1
				counter_not_add:
					addi	$t6, $t1, 1				#
					sll	$t7, $t6, 2				#putting array_num[tmp + 1] = num
					add	$t7, $t7, $a1				#
					sw	$t5, 0($t7)				#
					addi	$t0, $t0, 1				#i++
					j	outer_loop				#jump back to outer loop
		exit_outer:
			addi	$t0, $zero, 0						# $t0 = 0 for word
			addi	$t1, $zero, 0						#i = 0 loop counter
			while_print:
				beq		$t1, $s0, exit_print			# i = N then exit loop
				lw		$t6, array_num($t0)			#load array_num[i] in $t6
				addi		$t0, $t0, 4				# $t0 = $t0 + 4
				addi		$t1, $t1, 1				# i++
				li		$v0, 1					# 1 denotes printing int system call
				move		$a0, $t6				# print $t6
				syscall
				li		$v0, 4
				la		$a0, space_print			# 4 denotes printing string system call
				syscall
				j		while_print				#jump back to loop
			exit_print:
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, separator_print			# prints ':'
				syscall
				li		$v0, 1					# 1 denotes printing int system call
				move		$a0, $s4				# prints comparison counter
				syscall
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, new_line
				syscall
				jr		$ra					#jumps back to gp_number_func

	desc_sort:
		la		$a1, array_num						#initializing $a1 with address of array_num
		addu		$t3, $zero, $a1						# putting the address in $t3
		sll		$t0, $a2, 2						# putting N * 4 in $t0
		addu		$t3, $t3, $t0
		addiu		$t3, $t3, -4						#getting position number for last element of array_num
		srl		$t2, $a2, 1						# putting $t2 = N / 2 = i
		desc_loop:
			#beqz $t2, exit_desc_loop			
			beq		$t2, $zero, exit_desc_loop			#if t2 = i = 0 then exit loop
			lw		$t0, ($a1)					#load ith element in $t0
			lw		$t1, ($t3)					#load N - 1 - i th element in $t1
			sw		$t1, ($a1)					#swap procedure
			sw		$t0, ($t3)
			addiu		$t3, $t3, -4					# decrease 4 to go to previous word
			addiu		$a1, $a1, 4					#increament by 4 to go to next work
			addi		$t2, $t2, -1					#i--
			j		desc_loop
		exit_desc_loop:
			addi		$t0, $zero, 0					# $t0 = 0 for word
			addi		$t1, $zero, 0					#i = 0 loop counter
			while_print_desc:
				beq		$t1, $s0, exit_print_desc		# i = N then exit loop
				lw		$t6, array_num($t0)			#load array_num[i] in $t6
				addi		$t0, $t0, 4				# $t0 = $t0 + 4
				addi		$t1, $t1, 1				# i++
				li		$v0, 1					# 1 denotes printing int system call
				move		$a0, $t6				# print $t6
				syscall
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, space_print
				syscall
				j		while_print_desc			#jump back to loop
			exit_print_desc:
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, new_line
				syscall
				la		$a1, array_num
				jr		$ra					#jumps back to gp_number_func


	random_sort:
		add		$a1, $zero, $s0						#upper bound for random which is N
		addi		$t0, $zero, 0						#i = 0
		random_loop:
			slt		$t1, $t0, $s0					#if i >= N
			beq		$t1, $zero, exit_random_loop			#break loop
			#addi $v0, $zero, 42
			li		$v0, 42						# 42 denotes random number generator
			syscall
			
			sll		$t2, $t0, 2					# t2 = $t0 * 4 = i * 4
			lw		$t3, array_num($t2)				#temp = array_num[i]
			sll		$t4, $a0, 2					# index * 4
			lw		$t5, array_num($t4)				# 
			sw		$t5, array_num($t2)				# swap procedure
			sw		$t3, array_num($t4)				#
			addi		$t0, $t0, 1					# i ++
		exit_random_loop:
			addi		$t0, $zero, 0					# $t0 = 0 for word
			addi		$t1, $zero, 0					#i = 0 loop counter
			while_print_rand:
				beq		$t1, $s0, exit_print_rand		# i = N then exit loop
				lw		$t6, array_num($t0)			#load array_num[i] in $t6
				addi		$t0, $t0, 4				# $t0 = $t0 + 4
				addi		$t1, $t1, 1				# i++
				li		$v0, 1					# 1 denotes printing int system call
				move		$a0, $t6				# print $t6
				syscall
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, space_print
				syscall
				j		while_print_rand			#jump back to loop
			exit_print_rand:
				li		$v0, 4					# 4 denotes printing string system call
				la		$a0, new_line
				syscall
				la		$a1, array_num
				jr		$ra					#jumps back to gp_number_func
