// When this runs, code should be running in 32bit
.code32

.set ARCH,     0                           // 0 is low endian, 4 is big endian
.set MAGIC,    0xE85250D6                  // The Multiboot2 magic!
.set LENGTH,   .multiboot_end - .multiboot // Length of the header
.set CHECKSUM, -(MAGIC + LENGTH)           // Checksum to prove we are multiboot and valid

.section .headers, "a"
.multiboot:
    .align 8
    .long MAGIC
    .long ARCH
    .long LENGTH
    .long CHECKSUM

    .short 0
    .short 0
    .long 8
.multiboot_end:

.section .text
.type _start, @function
.global _start

.extern _main
.extern check_cpuid
.extern check_long_mode
.extern setup_paging
.extern enable_paging

_start:
    // Setup the stack by moving the ESP register to the top of the stack
	movl $.stack_top, %esp

    // Check if we can enable long mode
    call check_cpuid
    call check_long_mode

    // Enable paging
    call setup_paging
    call enable_paging

    // Load the global descriptor table
    lgdt .pointer

    // Load our code into the appropriate sector
    ljmp $0x8, $_main

.size _start, . - _start

.section .bss
.align 4096

// Reserve a stack for our C code of 16KiB.
stack_bottom:
    .skip 16384 # 16 KiB
.stack_top:
    .size stack_bottom, . - stack_bottom

.section .rodata
.align 8

// Setup the 64 bit global descriptor table
gdt64:
    .quad 0 // 0 entry
.code_segment:
    .quad (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) | 0xF00000000FFFF
    // Here we enabled the executable flag, set the descriptor flag to data segment and enabled the present flag, then
    // enabled the 64 bit flag

    .size gdt64, . - gdt64

// Create a pointer to our GDT
.pointer:
    .short .pointer - gdt64
    .long gdt64
    .size .pointer, . - .pointer