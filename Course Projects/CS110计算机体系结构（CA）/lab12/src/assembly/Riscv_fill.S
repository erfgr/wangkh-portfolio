.section .text
.globl Riscv_fill
.type Riscv_fill, @function
Riscv_fill:
	li a0, 1
	li a1, 1
	li a2, 20
	li a3, 20
	li a4, 0xFFE0
	jal LCD_Fill

	li a0, 60
	li a1, 45
	li a2, 10
	li a3, 0xF800
	jal LCD_DrawCircle


	# The above lines declares a function that can be accessed from C code.
	# When you're implementing your own function, you make a new file in
	# this folder, copy the above 4 lines, and replace all
	# "your_function_name" to your function's name.

	# Then you can add code after the label on line 4.

	# The rest of things work the same as in Venus, except that the directive
	# ".asciiz" is removed. Use ".string" instead.

	# Also, please make sure that each assembly function has a filename with 
	# extension name ".S", not ".s". Otherwise it will not be recognized
	# by the riscv-nuclei-elf-as and will throw an error.

	# You're free to remove this function after you've read the above.