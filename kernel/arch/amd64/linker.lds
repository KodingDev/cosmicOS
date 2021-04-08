ENTRY(_start)

SECTIONS {
    . = 1M;

    .headers ALIGN(4K) : ALIGN(16) {
        KEEP(*(.multiboot))
        KEEP(*(.text))
     }

    .text ALIGN(4K) : { *(.text .text.*) }

    .bss ALIGN(4K) : {
        *(.bss .bss.*)
    }
}