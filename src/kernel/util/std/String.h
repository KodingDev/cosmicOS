#ifndef COSMICOS_STRING_H
#define COSMICOS_STRING_H

template<class T>
static const char *toString(T value) {
    static char buf[(sizeof(value) << 1) + 2];
    size_t idx = (sizeof(value) << 1) + 1;
    buf[idx] = '\0';

    bool negative = value < 0;
    if (negative) value = -value;

    while (value >= 16) {
        buf[--idx] = "0123456789ABCDEF"[value & 0xF];
        value >>= 4;
    }

    buf[--idx] = "0123456789ABCDEF"[value & 0xF];
    if (negative) buf[--idx] = '-';
    return &buf[idx];
}

#endif //COSMICOS_STRING_H
