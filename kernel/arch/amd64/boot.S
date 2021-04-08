// When this runs, code should be running in 32bit
.code32

.set ARCH,     0                           // 0 is low endian, 4 is big endian
.set MAGIC,    0xE85250D6                  // The Multiboot2 magic!
.set LENGTH,   .multiboot_end - .multiboot // Length of the header
.set CHECKSUM, -(MAGIC + LENGTH)           // Checksum to prove we are multiboot and valid

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

.section .bss:
    .align 16

// Reserve a stack for our C code of 16KiB.
stack_bottom:
    .skip 16384 # 16 KiB
stack_top: