#include "../../io/output/Display.h"
#include "IDT.h"
#include "../../io/output/IO.h"
#include "../../util/timer/Timer.h"
#include "../../asm/asm.h"

IDT::Descriptor IDT::data[256];

_Noreturn __attribute__ ((interrupt)) void interruptDoubleFault([[maybe_unused]] IDT::Frame *frame) {
    Display::clearScreen();
    Display::writeString(0, 0, "Double fault! Halting!", TEXT_LIGHT_RED);
    ASM::halt();
}

_Noreturn __attribute__ ((interrupt)) void interruptProtectionFault([[maybe_unused]] IDT::Frame *frame) {
    Display::clearScreen();
    Display::writeString(0, 0, "General protection fault! Halting!", TEXT_LIGHT_RED);
    ASM::halt();
}

void IDT::setup() {
    IO::println("[IDT] Setting up IDT");

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