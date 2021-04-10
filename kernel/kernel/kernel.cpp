#include "io/output/Display.h"
#include "setup/interrupts/IDT.h"
#include "setup/pic/PIC.h"
#include "util/timer/Timer.h"
#include "asm/asm.h"

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

        Display::clearScreen();
        Display::writeString(0, 0, "Waiting 3s");
        Timer::sleep(3000);
        Display::writeString(0, 0, (char *) "String writing test!");
        ASM::halt();
    }
}