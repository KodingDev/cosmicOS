// Run in 64 bit mode
.code64

// Begin the code storage section 'text'
.section .text

// Define our start method as a global and function
.global _start
.type _start, @function

_start:
    // Move the top of the stack to the stack pointer
	movl $stack_top, %esp

	// Begin executing our kernel code, setup is done
	call kernel_main

	// If the kernel returns, hang indefinitley. 'cli' disables interrupts
	cli

// Goes into an infinite loop until power down
sleep:
    hlt
	jmp sleep

// Tell the assembler that the start directive is finished here
.size _start, . - _start