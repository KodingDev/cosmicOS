#include <stdint.h> // NOLINT(modernize-deprecated-headers)
#include "IO.h"
#include "../../asm/asm.h"

void IO::pwrite(uint16_t port, uint8_t value) {
    // Wait until the output buffer is flushed
    while (!(ASM::inb(port + 5) & 0b100000));

    // Write our character to the buffer
    ASM::outb(port, value);
}

void IO::print(char *string) {
    while (*string) pwrite(IO::COM1, *string++);
}

void IO::println(char *string) {
    print(string);
    print((char*) "\n");
}
