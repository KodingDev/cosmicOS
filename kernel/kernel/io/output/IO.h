#ifndef COSMICOS_IO_H
#define COSMICOS_IO_H

class IO {
public:
    static constexpr short COM1 = 0x3F8;

    static void pwrite(uint16_t port, uint8_t value);

    static void print(char *string);

    static void println(char *string);
};

#endif //COSMICOS_IO_H