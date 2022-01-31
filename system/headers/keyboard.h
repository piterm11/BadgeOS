#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "system.h"
#include "irq.h"
#include "print.h"
#include "string.h"
#include "command.h"

#define HIST_SIZE 10


void kbd_on();
void kbd_off();
void keyboard_handler(struct regs *r);
void keyboard_install();
void buffer_putchar(uint8_t c);
void buffer_back();
void buffer_clear();
void add_to_buffer(char* text);
void init_history();
void add_to_history(char* text);

enum mode{
    FREE,
    CONSOLE
};

struct kb_controls_t{
    uint8_t shift_pressed;
    uint8_t caps_pressed;
    uint8_t ctrl_pressed;
    enum mode mode;
}kb_controls;


#define KB_BUFFER 1000
struct buffer_t{
    int8_t* text;
    uint16_t size;
    uint16_t position;
    int8_t buffer_history[HIST_SIZE][100];
    uint8_t history_size;
    int8_t history_pos;
}kb_buffer;


enum {
    KEY_NONE = 0,
    KEY_ESC = 1,
    KEY_1 = 2,
    KEY_2 = 3,
    KEY_3 = 4,
    KEY_4 = 5,
    KEY_5 = 6,
    KEY_6 = 7,
    KEY_7 = 8,
    KEY_8 = 9,
    KEY_9 = 10,
    KEY_0 = 11,
    KEY_MINUS = 12,
    KEY_EQUALS = 13,
    KEY_BACKSPACE = 14,
    KEY_TAB = 15,
    KEY_Q = 16,
    KEY_W = 17,
    KEY_E = 18,
    KEY_R = 19,
    KEY_T = 20,
    KEY_Y = 21,
    KEY_U = 22,
    KEY_I = 23,
    KEY_O = 24,
    KEY_P = 25,
    KEY_L_BRACKET = 26,
    KEY_R_BRACKET = 27,
    KEY_ENTER = 28,
    KEY_CTRL_DOWN = 29,KEY_CTRL_UP = 157,
    KEY_A = 30,
    KEY_S = 31,
    KEY_D = 32,
    KEY_F = 33,
    KEY_G = 34,
    KEY_H = 35,
    KEY_J = 36,
    KEY_K = 37,
    KEY_L = 38,
    KEY_SEMICOLON = 39,
    KEY_APOSTROPHE = 40,
    KEY_GRAVE = 41,
    KEY_LSHIFT_DOWN = 42, KEY_LSHIFT_UP = 170,
    KEY_BACKSLASH = 43,
    KEY_Z = 44,
    KEY_X = 45,
    KEY_C = 46,
    KEY_V = 47,
    KEY_B = 48,
    KEY_N = 49,
    KEY_M = 50,
    KEY_COMA = 51,
    KEY_DOT = 52,
    KEY_SLASH = 53,
    KEY_RSHIFT_DOWN = 54, KEY_RSHIFT_UP = 182,
    KEY_PRT_SRC = 55,
    KEY_ALT = 56,
    KEY_SPACE = 57,
    KEY_CAPS = 58,
    KEY_F1 = 59,
    KEY_F2 = 60,
    KEY_F3 = 61,
    KEY_F4 = 62,
    KEY_F5 = 63,
    KEY_F6 = 64,
    KEY_F7 = 65,
    KEY_F8 = 66,
    KEY_F9 = 67,
    KEY_F10 = 68,
    KEY_NUM = 69,
    KEY_SCROLL = 70,
    KEY_NUM_HOME = 71,
    KEY_NUM_UP = 72,
    KEY_NUM_PG_UP = 73,
    KEY_NUM_MINUS = 74,
    KEY_NUM_LEFT = 75,
    KEY_NUM_CENTER = 76,
    KEY_NUM_RIGHT = 77,
    KEY_NUM_PLUS = 78,
    KEY_NUM_END = 79,
    KEY_NUM_DOWN = 80,
    KEY_NUM_PG_DN = 81,
    KEY_INSERT = 82,
    KP_DELETE = 83,
    KEY_F11 = 87,
    KEY_F12 = 88,
};
#endif