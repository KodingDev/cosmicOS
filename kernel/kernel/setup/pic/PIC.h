#ifndef COSMICOS_PIC_H
#define COSMICOS_PIC_H

#define PIC1 0x20
#define PIC2 PIC1 + 8
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW4_8086 0x01

class PIC {
public:
    static void remap();

    static void setup();

    [[maybe_unused]] static void sendEOI();

    [[maybe_unused]] static void PIC1_mask(int mask);

    [[maybe_unused]] static void PIC2_mask(int mask);
};

#endif //COSMICOS_PIC_H
