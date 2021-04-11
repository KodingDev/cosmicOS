#include <stdint.h> // NOLINT(modernize-deprecated-headers)

#ifndef COSMICOS_PANIC_H
#define COSMICOS_PANIC_H

struct StackFrame {
    struct StackFrame *ebp;
    uint32_t eip;
};

class Panic {
public:
    static void displayPanic(const char *message, ...);
};

#endif //COSMICOS_PANIC_H
