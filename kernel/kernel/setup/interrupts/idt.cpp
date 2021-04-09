#include "../../io/output/display.h"
#include "idt.h"

static constexpr uint8_t PRESENT = 1 << 7;
static constexpr uint8_t INTERRUPT_GATE = 0xE;
//static constexpr uint8_t EXCEPTION_GATE = 0xF;

idt::idt_descriptor idt::data[256];

_Noreturn __attribute__ ((interrupt)) void interrupt_double_fault(idt::interrupt_frame *frame __attribute__((unused))) {
    clear_screen();
    write_string(0, 0, (char *) "Double fault! Halting!", TEXT_LIGHT_RED);
    while (true) asm volatile("hlt");
}

void idt::setup() {
    register_handler(13, interrupt_double_fault, INTERRUPT_GATE);
    register_handler(14, interrupt_double_fault, INTERRUPT_GATE);

    struct idtr idtRegister = {sizeof(data), (unsigned long) &data[0]};
    asm volatile ("lidt %0" : : "m"(idtRegister));
}

void idt::register_handler(uint8_t index, void (*handler)(interrupt_frame *), uint8_t type) {
    struct idt_descriptor descriptor{};
    descriptor.offset_0_15 = ((uint64_t) handler & 0xFFFF);
    descriptor.selector = 0x8;
    descriptor.typeAttr = PRESENT | type;
    descriptor.offset_16_32 = ((uint64_t) handler & 0xFFFF0000) >> 16;
    descriptor.offset_32_63 = ((uint64_t) handler & 0xFFFFFFFF00000000) >> 32;
    data[index] = descriptor;
}