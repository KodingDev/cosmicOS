#include "stdint.h" // NOLINT(modernize-deprecated-headers)

#ifndef COSMICOS_IO_H
#define COSMICOS_IO_H

class IO {
public:
    static constexpr short COM1 = 0x3F8;

    static void comWrite(uint16_t port, uint8_t value);

    static void pwrite(uint16_t port, uint8_t value);

    static void putChar(char c);

    static void print(const char *string);

    static void println(const char *string);

    [[maybe_unused]] static void printf(const char *format, ...);
};

#endif //COSMICOS_IO_H
