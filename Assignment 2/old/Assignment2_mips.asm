.data
	array:		.word	0 : 15		# an array of word, for storing values.
	size:		.word	10		# actual count of the elements in the array.
	a:		.word	5		# starting value of the gp.
	r:		.word	5		# common ratio of the gp.
	space:		.asciiz " "		# a space string.
	line:		.asciiz	"\n"		# a newline string.
	colonsp:	.asciiz ": "	# a colon string with space.

	number_of_elements_input:	.asciiz	"Input number of values to be sorted (0 < N < 10): "
	a_input_w:			.asciiz	"Input a value: "
	r_input_w:			.asciiz	"Input r value: "
	direct_array_string:		.asciiz	"Ascending order: "
	sorted_array_string:		.asciiz "Sorted: "
	no_of_comparisions:		.asciiz "No. of comparisions taken are: "
	shuffled_array_string:		.asciiz "Randomized: "
	reverse_array_string:		.asciiz	"Descending order: "

.text
.globl	main
	main:
		starting_instruction:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, number_of_elements_input	# load number_of_elements_input to argument register $a0.
			syscall
		read_num_of_elements:
			li	$v0, 5			# 5 is read int syscall.
			syscall
			la	$t0, size		# load address of size to $t0.
			sw	$v0, 0($t0)		# store returned value in $v0 to size.
		a_input:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, a_input_w		# load a_input_w to argument register $a0.
			syscall
		read_a:
			li	$v0, 5			# 5 is read int syscall.
			syscall
			la	$t0, a			# load address of a to $t0.
			sw	$v0, 0($t0)		# store returned value in $v0 to a.
		r_input:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, r_input_w		# load r_input_w to argument register $a0.
			syscall
		read_r:
			li	$v0, 5			# 5 is read int syscall.
			syscall
			la	$t0, r			# load address of r to $t0.
			sw	$v0, 0($t0)		# store returned value in $v0 to r.
		gp_array_prep:
			la	$t0, array		# load array to $t0.
			lw	$t1, size		# load size to $t1.
			li	$t2, 0			# $t2 being loop runner, starting from 0.
			lw	$t3, a			# load a to $t3.
			lw	$t4, r			# load r to $t4.
		gp_array_loop:
			bge	$t2, $t1, gp_array_end	# while ($t2 < $t1).
			add	$a0, $zero, $t3		# storing current array element in register $a0.
			sw	$a0, 0($t0)		# store returned value in $a0 in the array.
			mul	$t3, $t3, $t4		# multiplying (k-1)th term with r.
			addi	$t0, $t0, 4		# increment array pointer by 4.
			addi	$t2, $t2, 1		# increment loop runner by 1.
			j	gp_array_loop		# jump back to the beginning of the loop.
		gp_array_end:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, direct_array_string	# load direct_array_string to argument register $a0.
			syscall
			jal	print			# call print.
		sorting_ascending_order:
			add	$v1, $zero, 0		# Setting $v1 to store number of comparisions.
			jal	sort			# call sort.
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, no_of_comparisions	# load no_of_comparisions to argument register $a0.
			syscall
			li	$v0, 1			# 1 is print int syscall.
			move	$a0, $v1		# copying $t1 to address register $a0.
			syscall
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall
		sorting_reverse_order:
			jal	reverse			# call reverse.
			add	$v1, $zero, 0		# Setting $v1 to store number of comparisions.
			jal	sort			# call sort.
			li	$v0, 4			# 4 is print_string syscall.
			la	$a0, no_of_comparisions	# load no_of_comparisions to argument register $a0.
			syscall
			li	$v0, 1			# 1 is print int syscall.
			move	$a0, $v1		# copying $t1 to address register $a0.
			syscall
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall
		sorting_random_order:
			jal	shuffle			# call shuffle.
			add	$v1, $zero, 0		# Setting $v1 to store number of comparisions.
			jal	sort			# call sort.
			li	$v0, 4			# 4 is print_string syscall.
			la	$a0, no_of_comparisions	# load no_of_comparisions to argument register $a0.
			syscall
			li	$v0, 1			# 1 is print int syscall.
			move	$a0, $v1		# copying $t1 to argument register $a0.
			syscall
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall
		exit:
			li	$v0, 10			# 10 is exit syscall.
			syscall				# issue a system call.

	print:
		print_loop_prep:
			la	$t0, array		# load array to $t0.
			lw	$t1, size		# load size to $t1.
			li	$t2, 0			# $t2 being loop runner, starting from 0.
		print_loop:
			bge	$t2, $t1, print_end	# while ($t2 < $t1).
			li	$v0, 1			# 1 is print int syscall.
			lw	$a0, 0($t0)		# store returned value in $a0 in the array.
			syscall
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, space		# load pace to argument register $a0.
			syscall
			addi	$t0, $t0, 4		# increment array pointer by 4.
			addi	$t2, $t2, 1		# increment loop runner by 1.
			j	print_loop		# jump back to the beginning of the loop.
		print_end:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall
			jr	$ra			#jump register with the return address.
	
	sort:	
		move	$s0, $ra			# copying function return address from ra.
		sort_prep:
			la	$t0, array		# load array to $t0.
			lw	$t1, size		# load array size to $t1.
			li	$t2, 1			# loop runner, starting from 1.
		sort_firstloop:
			la	$t0, array		# load array to $t0.
			bge	$t2, $t1, sort_firstloop_end	# while (t2 < $t1).
			move	$t3, $t2		# copy $t2 to $t3.
		sort_secondloop:
			la	$t0, array		# load array to $t0.
			mul	$t5, $t3, 4		# multiply $t3 with 4, and store in $t5
			add	$t0, $t0, $t5		# add the array address with $t5, which is the index multiplied with 4.
			ble	$t3, $zero, sort_secondloop_end	# while (t3 > 0).
			lw	$t7, 0($t0)		# load array[$t3] to $t7.
			lw	$t6, -4($t0)		# load array[$t3 - 1] to $t6.
			bge	$t7, $t6, sort_secondloop_end	# while (array[$t3] < array[$t3 - 1]).
			add	$v1, $v1, 1		# adding 1 to the total comparisions.
			lw	$t4, 0($t0)		# load array[$t3] to $t4.
			sw	$t6, 0($t0)		# store array[$t3] to $t6.
			sw	$t4, -4($t0)		# store array[$t3 - 1] to $t4.
			subi $t3, $t3, 1		# # subtracting 1 from $t3.
			j	sort_secondloop		# jump back to the beginning of the sort_secondloop.
		sort_secondloop_end:
			slt	$t8, $zero, $t3
			add	$v1, $v1, $t8		# adding 1 to the total comparisions.
			addi	$t2, $t2, 1		# increment loop runner by 1.
			j	sort_firstloop		# jump back to the beginning of the sort_firstloop.
		sort_firstloop_end:
			li	$v0, 4			# 4 = print_string syscall.
			la	$a0, sorted_array_string	# load sorted_array_string to argument register $a0.
			syscall				# issue a system call.
			li	$v0, 4			# 4 = print_string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall				# issue a system call.
			jal	print			# call print routine.
		move	$ra, $s0			# getting the return address back to $ra.
		jr	$ra				# jump register with the return address.
	
	reverse:
		move	$s0, $ra			# copying function return address from ra.
		lw	$t5, size			# load array size to $t5.
		add	$a1, $zero, $t5			# upper_limit to rand
		addi	$a1, $a1, -1
		reverse_prep:
			la	$t0, array		# load array to $t0.
			lw	$t1, size		# load array size to $t1.
			li	$t2, 0			# loop runner, starting from 1.		
		reverse_loop:
			la	$t0, array		# load array to $t0.
			la	$t3, array		# load array to $t3.
			bge	$t2, $a1, reverse_loop_end	# while (t2 < $t1).
			syscall
			mul	$t9, $t2, 4		# multiply $t2 with 4, and store in $t9.
			mul	$t8, $a1, 4		# multiply $a1 with 4, and store in $t8.
			add	$t0, $t0, $t9		# going to [$t2] from start of the array.
			add	$t3, $t3, $t8		# going to [$a1] from start of the array.
			lw	$t7, 0($t0)		# load array[$t2] to $t7.
			lw	$t6, 0($t3)		# load array[$a1] to $t7.
			move	$t4, $t0		# copying $t0 to $t4.
			sw	$t7, 0($t3)		# store array[$a1] to $t7.
			sw	$t6, 0($t4)		# store array[$t2] to $t6.
			addi	$t2, $t2, 1		# increment loop runner by 1.
			addi	$a1, $a1, -1		# subtracting 1 from $t3.
			j	reverse_loop		# jump back to the beginning of the reverse_loop.
		reverse_loop_end:
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, reverse_array_string	# load reverse_array_string to argument register $a0.
			syscall				# issue a system call.
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall				# issue a system call.
			jal	print			# call print routine.
		move	$ra, $s0			# getting the return address back to $ra.
		jr	$ra				# jump register with the return address.
	
	shuffle:
		move	$s0, $ra			# copying function return address from ra.
		lw	$t5, size			# load array size to $t5.
		add	$a1, $zero, $t5			# upper_limit to rand.
		shuffle_prep:
			la	$t0, array		# load array to $t0.
			lw	$t1, size		# load array size to $t1.
			li	$t2, 1			# loop runner, starting from 1.		
		shuffle_loop:
			la	$t0, array		# load array to $t0.
			la	$t3, array		# load array to $t3.
			bge	$t2, $t1, shuffle_loop_end	# while (t2 < $t1).
			addi 	$v0, $zero, 42		# stores random number in $a0 with upper limit $a1.
			syscall
			mul	$t9, $t2, 4		# multiply $t2 with 4, and store in $t9.
			mul	$t8, $a0, 4		# multiply $a0 with 4, and store in $t8.
			add	$t0, $t0, $t9		# going to [$t2] from start of the array.
			add	$t3, $t3, $t8		# going to [$a0] from start of the array.
			lw	$t7, 0($t0)		# load array[$t2] to $t7.
			lw	$t6, 0($t3)		# load array[$a0] to $t6.
			move	$t4, $t0		# copying $t0 to $t4.
			sw	$t7, 0($t3)		# store array[$a0] to $t7.
			sw	$t6, 0($t4)		# store array[$t2] to $t6.
			addi	$t2, $t2, 1		# increment loop runner by 1.
			j	shuffle_loop		# jump back to the beginning of the shuffle_loop.
		shuffle_loop_end:
			li	$v0, 4			# 4 is print_string syscall.
			la	$a0, shuffled_array_string	# load shuffled_array_string to argument register $a0.
			syscall				# issue a system call.
			li	$v0, 4			# 4 is print string syscall.
			la	$a0, line		# load line to argument register $a0.
			syscall				# issue a system call.
			jal	print			# call print routine.
		move	$ra, $s0			# getting the return address back to $ra.
		jr	$ra				# jump register with the return address.