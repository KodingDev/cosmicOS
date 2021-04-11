#include "stdint.h"
#include "../setup/interrupts/IDT.h"

#ifndef COSMICOS_ASM_H
#define COSMICOS_ASM_H

class ASM {
public:
    static inline void outb(uint16_t port, uint8_t value) {
        asm volatile ("outb %0, %1"::"a"(value), "Nd"(port));
    }

    static inline uint8_t inb(uint16_t port) {
        uint8_t ret;
        asm volatile ("inb %1, %0": "=a"(ret): "Nd"(port));
        return ret;
    }

    [[maybe_unused]] static inline void ioWait() {
        asm volatile ("jmp 1f\n\t1:jmp 2f\n\t2:" );
    }

    static inline void pwait() {
        asm volatile("outb %%al, $0x80"::"a" (0));
    }

    static inline void sti() {
        asm volatile("sti");
    }

    [[noreturn]] static inline void halt() {
        while (true) asm volatile("hlt");
    }

    [[maybe_unused]] static inline void doubleFault() {
        *((char *) 0xffffffffffffff) = 'A';
    }

    /**
     * The IDTR (interrupt descriptor table register) is an array which stores the
     * registered interrupts and pointers to their functions. (https://wiki.osdev.org/Interrupt_Descriptor_Table)
     */
    static inline void lidt(unsigned short size, unsigned long pointer) {
        struct {
            [[maybe_unused]] unsigned short size; // Size or "limit" of the IDT in bytes - 1
            [[maybe_unused]] unsigned long address; // Address where the IDT starts
        } __attribute__((packed)) idtRegister = {size, pointer};
        asm volatile ("lidt %0" : : "m"(idtRegister));
    }
};

#endif //COSMICOS_ASM_H
