#include "PIC.h"
#include "../../asm/asm.h"
#include "../../io/output/IO.h"

#define PIC1        0x20        /* IO base address for master PIC */
#define PIC2        0xA0        /* IO base address for slave PIC */

#define PIC1_COMMAND    PIC1
#define PIC1_DATA    (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA    (PIC2+1)

#define ICW1_INIT    0x10        /* Initialization - required! */
#define ICW1_ICW4    0x01        /* ICW4 (not) needed */
#define ICW4_8086    0x01        /* 8086/88 (MCS-80/85) mode */

void PIC::remap(int offset1, int offset2) {
    unsigned char a1, a2;

    a1 = ASM::inb(PIC1_DATA);                        // Save masks
    a2 = ASM::inb(PIC2_DATA);

    IO::pwrite(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // Starts the initialization sequence (in cascade mode)
    IO::pwrite(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    IO::pwrite(PIC1_DATA, offset1);                   // ICW2: Master PIC vector offset
    IO::pwrite(PIC2_DATA, offset2);                   // ICW2: Slave PIC vector offset
    IO::pwrite(PIC1_DATA,
               4);                         // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    IO::pwrite(PIC2_DATA, 2);                         // ICW3: tell Slave PIC its cascade identity (0000 0010)

    IO::pwrite(PIC1_DATA, ICW4_8086);
    IO::pwrite(PIC2_DATA, ICW4_8086);

    IO::pwrite(PIC1_DATA, a1);   // restore saved masks.
    IO::pwrite(PIC2_DATA, a2);
}

void PIC::setup() {
    remap(0x20, 0x28);
}

[[maybe_unused]] void PIC::PIC1_mask(int mask) {
    IO::pwrite(PIC1_DATA, mask);
}

[[maybe_unused]] void PIC::PIC2_mask(int mask) {
    IO::pwrite(PIC1_DATA, mask);
}

[[maybe_unused]] void PIC::sendEOI() {
    IO::pwrite(PIC1_COMMAND, 0x20);
}