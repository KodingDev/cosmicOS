#include "io/output/Display.h"
#include "setup/interrupts/IDT.h"

extern "C" [[maybe_unused]] void kernel_main() {
    IDT::setup();

    Display::clearScreen();
    Display::writeString(0, 0, (char *) "String writing test!");

    *((char *) 0xffffffffffffff) = 'A';
}