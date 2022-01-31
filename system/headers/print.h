#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include "colors.h"
#include "system.h"
#include "string.h"
#include "ctype.h"
#include "time.h"
#include "keyboard.h"

enum direction{
    UP,DOWN,LEFT,RIGHT
};
#define FIRST_COL 0
#define FIRST_ROW 6
#define NUM_COLS 80
#define NUM_ROWS 25
struct Char
{
    uint8_t character;
    uint8_t color;
};
struct terminal_t{
    struct Char *screen;

    uint16_t first_column;
    uint16_t first_row;

    uint16_t num_cols;
    uint16_t num_rows;

    uint16_t col;
    uint16_t row;
} term;

void terminal_install();


void move_csr();
void move(enum direction d);

void clear_input();
void clear_row(size_t row);
void clear();
void _newline();
void _tab();
void _back();
void _return();
void _vert();
void print_char(char character);
void print_str(char *string);
void print_int(int value);
void print_float(float value);
void print_set_color(uint8_t foreground, uint8_t background);
void check_and_place_newline();
void putchar(uint8_t c);
void put_at(uint8_t c, uint16_t col, uint16_t row);


void print_logo();
void print_emote();
void print_intro();
char getchar();
void print(char *format, ...);
void print_ln(char *format, ...);
// void scan(char *format, ...);
// int get_str(char* res);
// int get_int(int* res);
// int get_float(double* res);
#endif
