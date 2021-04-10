// Run in 64 bit mode
.code64

.extern halt

.section .text
.global _main
.type _main, @function

_main:
    // Load null into some CPU data registers
    mov $0x0, %ax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss

	// Begin executing our kernel code, setup is done
	call kernel_main
    call halt

// Tell the assembler that the start directive is finished here
.size _start, . - _start