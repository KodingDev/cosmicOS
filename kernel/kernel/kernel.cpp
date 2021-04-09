#include "io/output/display.h"
#include "setup/interrupts/idt.h"

extern "C" __attribute__((unused)) void kernel_main() {
    idt::setup();

    clear_screen();
    write_string(0, 0, (char *) "String writing test!");

    *((char *) 0xffffffffffffff) = 'A';
}