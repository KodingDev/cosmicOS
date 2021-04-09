#include "stdint.h"

#ifndef COSMICOS_ASM_H
#define COSMICOS_ASM_H

class ASM {
public:
    [[maybe_unused]] static inline void outb(uint16_t port, uint8_t value) {
        asm volatile ("outb %0, %1"::"a"(value), "Nd"(port));
    }

    [[maybe_unused]] static inline uint8_t inb(uint16_t port) {
        uint8_t ret;
        asm volatile ("inb %1, %0": "=a"(ret): "Nd"(port));
        return ret;
    }

    [[maybe_unused]] static inline void io_wait() {
        asm volatile ("jmp 1f\n\t1:jmp 2f\n\t2:" );
    }
};

#endif //COSMICOS_ASM_H
