#include "Timer.h"
#include "../../io/output/IO.h"
#include "../../boot/interrupts/IDT.h"
#include "../../boot/pic/PIC.h"
#include "../../asm/asm.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"

int Timer::ticks = 0;

void Timer::setup(int hz) {
    IO::println("[TIMER] Initializing timer");

    int divisor = 1193180 / hz;                     // Calculate our divisor
    IO::pwrite(0x43, 0x36);             // Set our command byte 0x36
    IO::pwrite(0x40, divisor & 0xFF);   // Set low byte of divisor
    IO::pwrite(0x40, divisor >> 8);     // Set high byte of divisor

    IO::println("[TIMER] Timer initialized");
}

void Timer::interrupt([[maybe_unused]] IDT::Frame *frame) {
    Timer::ticks++;
    PIC::sendEOI();
}

[[maybe_unused]] void Timer::sleep(int ms) {
    int start = Timer::ticks;
    int target = ms / (1000 / Timer::HERTZ);
    while (Timer::ticks - start % target != target);
}

#pragma clang diagnostic pop