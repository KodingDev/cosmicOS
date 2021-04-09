// Run in 64 bit mode
.code64

.section .text
.global _main
.type _main, @function

_main:
    // Load null into some CPU data registers
    mov %ax, 0
    mov %ss, %ax
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax

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