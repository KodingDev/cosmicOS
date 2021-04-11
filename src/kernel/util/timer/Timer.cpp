#include "Timer.h"
#include "../../io/output/IO.h"
#include "../../setup/interrupts/IDT.h"
#include "../../setup/pic/PIC.h"
#include "../../asm/asm.h"

int Timer::ticks = 0;

void Timer::setup(int hz) {
    int divisor = 1193180 / hz;                     // Calculate our divisor
    IO::pwrite(0x43, 0x36);             // Set our command byte 0x36
    IO::pwrite(0x40, divisor & 0xFF);   // Set low byte of divisor
    IO::pwrite(0x40, divisor >> 8);     // Set high byte of divisor
}

void Timer::interrupt([[maybe_unused]] IDT::Frame *frame) {
    Timer::ticks++;
    PIC::sendEOI();
}

void Timer::sleep(int ms) {
    while (Timer::ticks % (ms / (1000 / Timer::HERTZ)) != 0);
}