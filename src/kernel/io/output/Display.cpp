#include "Display.h"

#define MAX_HEIGHT 25
#define MAX_WIDTH  80
#define SIZE       MAX_HEIGHT * MAX_WIDTH

int getIndex(int row, int column) {
    return row * MAX_WIDTH + column;
}

void Display::writeCharacter(char character, char color, int offset) {
    volatile char *videoMemory = (volatile char *) 0xB8000;
    if (offset > SIZE) return;

    videoMemory[offset * 2] = character;
    videoMemory[offset * 2 + 1] = color;
}

void Display::writeString(int row, int column, const char *string, char color) {
    int index = getIndex(row, column);

    while (*string) {
        if (*string == '\n') {
            index += MAX_WIDTH - (index % MAX_WIDTH);
            string++;
            continue;
        }

        writeCharacter(*string++, color, index++);
    }
}

void Display::clearScreen() {
    for (int i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) writeCharacter(' ', 0, i);
}