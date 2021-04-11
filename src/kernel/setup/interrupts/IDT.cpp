#include "IDT.h"
#include "../../io/output/IO.h"
#include "../../util/timer/Timer.h"
#include "../../asm/asm.h"
#include "../panic/Panic.h"

IDT::Descriptor IDT::data[256];

void handleFault(const char *header, IDT::Frame *frame) {
    Panic::displayPanic("!!! Kernel Panic !!!\n"
                        "type: %s\n"
                        "instruction pointer: %l\n"
                        "code segment: %l\n"
                        "flags: %l\n"
                        "stack pointer: %l\n"
                        "stack segment: %l\n",
                        header,
                        frame->instructionPointer,
                        frame->codeSegment,
                        frame->flags,
                        frame->stackPointer,
                        frame->stackSegment);
}

__attribute__ ((interrupt)) void interruptDoubleFault([[maybe_unused]] IDT::Frame *frame) {
    handleFault("Double fault", frame);
}

__attribute__ ((interrupt)) void interruptProtectionFault([[maybe_unused]] IDT::Frame *frame) {
    handleFault("General protection fault", frame);
}

void IDT::setup() {
    IO::println("[IDT] Setting up IDT (Interrupt Descriptor Table)");

    registerExceptionHandler(0x8, interruptDoubleFault);
    registerExceptionHandler(0xD, interruptProtectionFault);
    registerExceptionHandler(0x20, Timer::interrupt);

    ASM::lidt(sizeof(*data) * 256, (unsigned long) &data[0]);
    ASM::sti();

    IO::println("[IDT] IDT configured!");
}

void IDT::registerExceptionHandler(uint8_t index, void (*handler)(IDT::Frame *)) {
    struct Descriptor descriptor{};
    descriptor.offset_0_15 = ((uint64_t) handler & 0xFFFF);
    descriptor.selector = 0x8;
    descriptor.typeAttr = (1 << 7) | (0 << 5) | 0xF;
    descriptor.offset_16_32 = ((uint64_t) handler >> 16) & 0xffff;
    descriptor.offset_32_63 = ((uint64_t) handler >> 32) & 0xffffffff;
    data[index] = descriptor;
}