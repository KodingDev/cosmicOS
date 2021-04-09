#ifndef COSMICOS_DISPLAY_H
#define COSMICOS_DISPLAY_H

void write_character(char character, char color, int index);

void write_string(int row, int column, char *string);

void clear_screen(void);

#endif //COSMICOS_DISPLAY_H
