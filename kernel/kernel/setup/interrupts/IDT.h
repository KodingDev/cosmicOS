#include <stdint.h> // NOLINT(modernize-deprecated-headers)
#include <stddef.h> // NOLINT(modernize-deprecated-headers)

#ifndef COSMICOS_IDT_H
#define COSMICOS_IDT_H

class IDT {
public:
    struct Frame {
        [[maybe_unused]] size_t ip;
        [[maybe_unused]] size_t cs;
        [[maybe_unused]] size_t flags;
        [[maybe_unused]] size_t sp;
        [[maybe_unused]] size_t ss;
    };

    static void setup();

    static void registerHandler(uint8_t index, void (*handler)(Frame *), uint8_t type);

private:
    struct Descriptor {
        [[maybe_unused]] unsigned short offset_0_15; // Lower part of the offset address
        [[maybe_unused]] unsigned short selector; // Selector of the interrupt for the kernel (https://wiki.osdev.org/Selector)
        [[maybe_unused]] unsigned char ist; // Completely unused
        [[maybe_unused]] unsigned char typeAttr; // Gate type. To prevent issues, enable flag has to be set
        [[maybe_unused]] unsigned short offset_16_32; // Offset address bits 13-31
        [[maybe_unused]] unsigned int offset_32_63; // Offset address bits 32-63
        [[maybe_unused]] unsigned int zero; // Reserved & unused
    };

    /**
     * The IDTR (interrupt descriptor table register) is an array which stores the
     * registered interrupts and pointers to their functions. (https://wiki.osdev.org/Interrupt_Descriptor_Table)
     */
    struct Register {
        [[maybe_unused]] unsigned short size; // Size or "limit" of the IDT in bytes - 1
        [[maybe_unused]] unsigned long address; // Address where the IDT starts
    } __attribute__((packed));

    static Descriptor data[256];
};

#endif //COSMICOS_IDT_H
