#ifndef COSMICOS_DISPLAY_H
#define COSMICOS_DISPLAY_H

static constexpr char TEXT_LIGHT_RED = 12;
static constexpr char TEXT_WHITE = 15;

class Display {
public:
    static void writeCharacter(char character, char color, int index);

    static void writeString(int row, int column, const char *string, char color = TEXT_WHITE);

    static void clearScreen();
};

#endif //COSMICOS_DISPLAY_H
