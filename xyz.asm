.data
prompt: .asciiz "Enter a string: "
input_buffer: .space 256   # allocate a buffer for input string

.text
main:
    # Prompt user to enter a string
    li $v0, 4
    la $a0, prompt
    syscall

    # Read input string from user
    li $v0, 8
    la $a0, input_buffer
    li $a1, 256
    syscall

    # Allocate space on the heap for input string
    li $v0, 9
    li $a0, 256
    syscall
    move $s0, $v0  # save start address of heap block to $s0

    # Copy input string to heap
    la $s1, input_buffer   # $s1 = address of input_buffer
    li $t0, 0              # $t0 = offset
copy_loop:
    lb $t1, ($s1)          # $t1 = input_buffer[offset]
    beqz $t1, end_copy     # if $t1 == 0, end loop
    addu $t2, $s0, $t0     # $














    
















    




































