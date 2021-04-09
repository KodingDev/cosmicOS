#include "display.h"

#define MAX_HEIGHT 25
#define MAX_WIDTH  80

int get_index(int row, int column) {
    return row * MAX_WIDTH + column;
}

void write_character(char character, char color, int offset) {
    volatile char *videoMemory = (volatile char *) 0xB8000;
    videoMemory[offset * 2] = character;
    videoMemory[offset * 2 + 1] = color;
}

void write_string(int row, int column, char *string) {
    int index = get_index(row, column);
    while (*string) write_character(*string++, 0xF, index++);
}

void clear_screen(void) {
    for (int i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) write_character(' ', 0, i);
}