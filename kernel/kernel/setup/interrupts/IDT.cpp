#include "../../io/output/Display.h"
#include "IDT.h"
#include "../../io/output/IO.h"

static constexpr uint8_t PRESENT = 1 << 7;
static constexpr uint8_t INTERRUPT_GATE = 0xE;
//static constexpr uint8_t EXCEPTION_GATE = 0xF;

IDT::Descriptor IDT::data[256];

_Noreturn __attribute__ ((interrupt)) void interruptDoubleFault([[maybe_unused]] IDT::Frame *frame) {
    Display::clearScreen();
    Display::writeString(0, 0, (char *) "Double fault! Halting!", TEXT_LIGHT_RED);
    while (true) asm volatile("hlt");
}

void IDT::setup() {
    IO::println((char *) "[IDT] Setting up IDT");

    registerHandler(13, interruptDoubleFault, INTERRUPT_GATE);
    registerHandler(14, interruptDoubleFault, INTERRUPT_GATE);

    struct Register idtRegister = {sizeof(data), (unsigned long) &data[0]};
    asm volatile ("lidt %0" : : "m"(idtRegister));
    IO::println((char *) "[IDT] IDT configured!");
}

void IDT::registerHandler(uint8_t index, void (*handler)(Frame *), uint8_t type) {
    struct Descriptor descriptor{};
    descriptor.offset_0_15 = ((uint64_t) handler & 0xFFFF);
    descriptor.selector = 0x8;
    descriptor.typeAttr = PRESENT | type;
    descriptor.offset_16_32 = ((uint64_t) handler & 0xFFFF0000) >> 16;
    descriptor.offset_32_63 = ((uint64_t) handler & 0xFFFFFFFF00000000) >> 32;
    data[index] = descriptor;
}