#include "Panic.h"
#include "../../io/output/Display.h"
#include "../../asm/asm.h"

void Panic::displayPanic(const char *message) {
    Display::clearScreen();
    Display::writeString(0, 0, message, TEXT_LIGHT_RED);
    ASM::halt();
}