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

    struct StackFrame *stk;
    asm volatile("mov %%rbp, %0" : "=r" (stk));
    IO::println("stack trace:");
    for (unsigned int frame = 0; stk && frame < 5; ++frame) {
        IO::printf("  0x%l\n", stk->eip);
        stk = stk->ebp;
    }

    va_end(args);
    ASM::halt();
}