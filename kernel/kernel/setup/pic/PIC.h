#ifndef COSMICOS_PIC_H
#define COSMICOS_PIC_H

class PIC {
public:
    static void remap(int offset1, int offset2);

    static void setup();

    [[maybe_unused]] static void sendEOI();

    [[maybe_unused]] static void PIC1_mask(int mask);

    [[maybe_unused]] static void PIC2_mask(int mask);
};

#endif //COSMICOS_PIC_H
