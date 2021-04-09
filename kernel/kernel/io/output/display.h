#ifndef COSMICOS_DISPLAY_H
#define COSMICOS_DISPLAY_H

static constexpr char TEXT_LIGHT_RED = 12;
static constexpr char TEXT_WHITE = 15;

void write_character(char character, char color, int index);

void write_string(int row, int column, char *string, char color = TEXT_WHITE);

void clear_screen();

#endif //COSMICOS_DISPLAY_H
