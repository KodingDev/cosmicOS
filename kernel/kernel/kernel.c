#include "io/output/display.h"

__attribute__((unused)) void kernel_main(void) {
    clear_screen();
    write_string(0, 0, "String writing test!");
}