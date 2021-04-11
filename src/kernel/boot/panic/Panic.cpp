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

    IDT::Frame frame = va_arg(args, IDT::Frame);
    IO::printf("!!! Kernel Panic !!!\n"
               "type: %s\n"
               "instruction pointer: %l\n"
               "code segment: %l\n"
               "flags: %l\n"
               "stack pointer: %l\n"
               "stack segment: %l\n",
               message,
               frame.instructionPointer,
               frame.codeSegment,
               frame.flags,
               frame.stackPointer,
               frame.stackSegment);

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