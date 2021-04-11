#include "boot/interrupts/IDT.h"
#include "boot/pic/PIC.h"
#include "util/timer/Timer.h"
#include "asm/asm.h"
#include "io/output/IO.h"

extern "C" {
// Grub gives us this
extern uint32_t multibootPointer;
extern uint32_t multibootMagic;

extern void (*__CTOR_LIST__)(); // NOLINT(bugprone-reserved-identifier)

[[maybe_unused]] void kernel_main() {
    // TODO: Abstract this when cleaning up
    void (**constructor)() = &__CTOR_LIST__;
    while (*constructor) {
        (*constructor)();
        constructor++;
    }

    IDT::setup();
    PIC::setup();
    Timer::setup();

    ASM::doubleFault();
    ASM::halt();
}
}