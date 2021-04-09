#include <stdint.h> // NOLINT(modernize-deprecated-headers)
#include <stddef.h> // NOLINT(modernize-deprecated-headers)

#ifndef COSMICOS_IDT_H
#define COSMICOS_IDT_H

class idt {
public:
    struct interrupt_frame {
        size_t ip     __attribute__((unused));
        size_t cs     __attribute__((unused));
        size_t flags  __attribute__((unused));
        size_t sp     __attribute__((unused));
        size_t ss     __attribute__((unused));
    };

    static void setup();

    static void register_handler(uint8_t index, void (*handler)(interrupt_frame *), uint8_t type);

private:
    struct idt_descriptor {
        unsigned short offset_0_15  __attribute__((unused)); // Lower part of the offset address
        unsigned short selector     __attribute__((unused)); // Selector of the interrupt for the kernel (https://wiki.osdev.org/Selector)
        unsigned char ist           __attribute__((unused)); // Completely unused
        unsigned char typeAttr      __attribute__((unused)); // Gate type. To prevent issues, enable flag has to be set
        unsigned short offset_16_32 __attribute__((unused)); // Offset address bits 13-31
        unsigned int offset_32_63   __attribute__((unused)); // Offset address bits 32-63
        unsigned int zero           __attribute__((unused)); // Reserved & unused
    };

    /**
     * The IDTR (interrupt descriptor table register) is an array which stores the
     * registered interrupts and pointers to their functions. (https://wiki.osdev.org/Interrupt_Descriptor_Table)
     */
    struct idtr {
        unsigned short size    __attribute__((unused)); // Size or "limit" of the IDT in bytes - 1
        unsigned long address  __attribute__((unused)); // Address where the IDT starts
    } __attribute__((packed));

    static idt_descriptor data[256];
};

#endif //COSMICOS_IDT_H
