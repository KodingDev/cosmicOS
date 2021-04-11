#include <stdint.h> // NOLINT(modernize-deprecated-headers)
#include <stdarg.h> // NOLINT(modernize-deprecated-headers)
#include "IO.h"
#include "../../asm/asm.h"
#include "../../util/std/String.h"

void IO::comWrite(uint16_t port, uint8_t value) {
    // Wait until the output buffer is flushed
    while (!(ASM::inb(port + 5) & 0b100000));

    // Write our character to the buffer
    ASM::outb(port, value);
}

void IO::pwrite(uint16_t port, uint8_t value) {
    ASM::pwait();
    ASM::outb(port, value);
}

void IO::putChar(char c) {
    comWrite(IO::COM1, c);
}

void IO::print(const char *string) {
    while (*string) putChar(*string++);
}

void IO::println(const char *string) {
    print(string);
    print("\n");
}

[[maybe_unused]] void IO::printf(const char *format, ...) {
    // TODO: Make this up to the full specification

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;

            switch (*format++) {
                case '%': {
                    putChar('%');
                    break;
                }
                case 'd':
                case 'i': {
                    print(toString(va_arg(args, int)));
                    break;
                }
                case 'l': {
                    print(toString(va_arg(args, long)));
                    break;
                }
                case 'c': {
                    putChar(va_arg(args, int));
                    break;
                }
                case 's': {
                    print(va_arg(args, const char*));
                    break;
                }
            }
        } else IO::putChar(*format++);
    }

    va_end(args);
}