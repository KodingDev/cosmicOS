#ifndef COSMICOS_TIMER_H
#define COSMICOS_TIMER_H

#include "../../boot/interrupts/IDT.h"

class Timer {
public:
    static void setup(int hz = HERTZ);

    [[maybe_unused]] static void sleep(int ms);

    __attribute__((interrupt))
    static void interrupt([[maybe_unused]] IDT::Frame *frame);

private:
    static constexpr int HERTZ = 100;

    static int ticks;
};

#endif //COSMICOS_TIMER_H
