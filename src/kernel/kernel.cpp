#include "setup/interrupts/IDT.h"
#include "setup/pic/PIC.h"
#include "util/timer/Timer.h"
#include "asm/asm.h"
#include "io/output/IO.h"

extern "C" {
extern void (*__CTOR_LIST__)(); // NOLINT(bugprone-reserved-identifier)

[[maybe_unused]] void kernel_main() {
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