#include <stdarg.h> // NOLINT(modernize-deprecated-headers)
#include "Panic.h"
#include "../../io/output/Display.h"
#include "../../asm/asm.h"
#include "../../io/output/IO.h"
#include "../pic/PIC.h"

void Panic::displayPanic(const char *message, ...) {
    va_list args;
    va_start(args, message);

    ASM::cli();
    PIC::PIC1_mask(0b11111111);
    PIC::PIC2_mask(0b11111111);

    Display::clearScreen();
    Display::writeString(0, 0, "SYSTEM ERROR!", TEXT_LIGHT_RED);

    IO::printf(message, args);
    ASM::halt();

    va_end(args);
}