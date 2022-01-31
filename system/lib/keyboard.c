#include "../headers/keyboard.h"

unsigned char keymap[2][128] =
    {
        {
            0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
            '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
            0, /* Control */
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
            0, /* Left shift */ '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* Right shift */
            0,
            0,                            /* Alt */
            ' ',                          /* Space bar */
            0,                            /* Caps lock */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* < F1 - F10 */
            0,                            /* Num lock*/
            0,                            /* Scroll Lock */
            0, /* Home key */ 0, /* Up Arrow */ 0, /* Page Up */ '-',
            0, /* Left Arrow */ 0, /* Center */ 0, /* Right Arrow */ '+',
            0, /* End key*/ 0, /* Down Arrow */ 0, /* Page Down */
            0,                                     /* Insert Key */
            0,                                     /* Delete Key */
            0, 0, 0,
            0, /* F11 Key */ 0, /* F12 Key */
            0,                  /* Undefined */
        },
        {
            0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
            '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
            0, /* Control */
            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
            0, /* Left shift */ '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, /* Right shift */
            0,
            0,                            /* Alt */
            ' ',                          /* Space bar */
            0,                            /* Caps lock */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* < F1 - F10 */
            0,                            /* Num lock*/
            0,                            /* Scroll Lock */
            0, /* Home key */ 0, /* Up Arrow */ 0, /* Page Up */ '-',
            0, /* Left Arrow */ 0, /* Center */ 0, /* Right Arrow */ '+',
            0, /* End key*/ 0, /* Down Arrow */ 0, /* Page Down */
            0,                                     /* Insert Key */
            0,                                     /* Delete Key */
            0, 0, 0,
            0, /* F11 Key */ 0, /* F12 Key */
            0,                  /* Undefined */
        }};

char buffer[KB_BUFFER] = {0};

void init_history()
{
    for (size_t i = 0; i < HIST_SIZE; i++)
    {
        memcpy(kb_buffer.buffer_history[i], "", 1);
    }
    kb_buffer.history_size = 0;
    kb_buffer.history_pos = -1;
}
void add_to_history(char *text)
{
    for (int i = kb_buffer.history_size; i >= 0; i--)
    {
        memcpy(kb_buffer.buffer_history[i + 1], kb_buffer.buffer_history[i], strlen(kb_buffer.buffer_history[i]) + 1);
    }
    memcpy(kb_buffer.buffer_history[0], text, strlen(text) + 1);
    kb_buffer.history_size++;
    if (kb_buffer.history_size > HIST_SIZE)
    {
        kb_buffer.history_size = HIST_SIZE;
    }
}

int keyboard_enabled = 1;

void kbd_on()
{
    keyboard_enabled = 1;
}
void kbd_off()
{
    keyboard_enabled = 0;
}



void keyboard_handler(struct regs *r)
{
    unsigned char scancode = inportb(0x60);
    if (keyboard_enabled)
    {
        switch (scancode)
        {
        case KEY_CAPS:
            kb_controls.caps_pressed = !kb_controls.caps_pressed;
            break;
        case KEY_LSHIFT_DOWN:
            kb_controls.shift_pressed = 1;
            break;
        case KEY_RSHIFT_DOWN:
            kb_controls.shift_pressed = 1;
            break;
        case KEY_LSHIFT_UP:
            kb_controls.shift_pressed = 0;
            break;
        case KEY_RSHIFT_UP:
            kb_controls.shift_pressed = 0;
            break;
        case KEY_CTRL_DOWN:
            kb_controls.ctrl_pressed = 0;
            break;
        case KEY_CTRL_UP:
            kb_controls.ctrl_pressed = 0;
            break;
        case KEY_ENTER:
            kb_buffer.history_pos = -1;
            putchar('\n');
            buffer_putchar('\n');
            putchar('>');
            break;
        case KEY_NUM_UP:
        {
            if (kb_buffer.history_pos < kb_buffer.history_size - 1)
                kb_buffer.history_pos++;
            clear_input();
            buffer_clear();
            add_to_buffer(kb_buffer.buffer_history[kb_buffer.history_pos]);
            print("%s", kb_buffer.buffer_history[kb_buffer.history_pos]);
            break;
        }
        case KEY_NUM_DOWN:
        {
            if (kb_buffer.history_pos > -1)
                kb_buffer.history_pos--;
            clear_input();
            if (kb_buffer.history_pos != -1)
            {
                buffer_clear();
                add_to_buffer(kb_buffer.buffer_history[kb_buffer.history_pos]);
                print("%s", kb_buffer.buffer_history[kb_buffer.history_pos]);
            }

            break;
        }
        case KEY_NUM_LEFT:
            move(LEFT);
            break;
        case KEY_NUM_RIGHT:
            move(RIGHT);
            break;
        case KEY_F1:
            if (kb_controls.shift_pressed)
                print_set_color(BLACK, BLACK);
            else
                print_set_color(WHITE, BLACK);
            break;
        case KEY_F2:
            if (kb_controls.shift_pressed)
                print_set_color(RED, BLACK);
            else
                print_set_color(LIGHT_RED, BLACK);
            break;
        case KEY_F3:
            if (kb_controls.shift_pressed)
                print_set_color(GREEN, BLACK);
            else
                print_set_color(LIGHT_GREEN, BLACK);
            break;
        case KEY_F4:
            if (kb_controls.shift_pressed)
                print_set_color(BLUE, BLACK);
            else
                print_set_color(LIGHT_BLUE, BLACK);
            break;
        case KEY_F5:
            if (kb_controls.shift_pressed)
                print_set_color(BROWN, BLACK);
            else
                print_set_color(YELLOW, BLACK);
            break;
        case KEY_F6:
            if (kb_controls.shift_pressed)
                print_set_color(MAGENTA, BLACK);
            else
                print_set_color(PINK, BLACK);
            break;
        case KEY_F7:
            if (kb_controls.shift_pressed)
                print_set_color(CYAN, BLACK);
            else
                print_set_color(LIGHT_CYAN, BLACK);
            break;
        case KEY_F8:
            if (kb_controls.shift_pressed)
                print_set_color(DARK_GRAY, BLACK);
            else
                print_set_color(LIGHT_GRAY, BLACK);
            break;
        case KEY_F12:
            if (kb_controls.shift_pressed)
                print_emote();
            break;
        default:
        {
            if (scancode < 128)
            {
                if (kb_controls.caps_pressed)
                {
                    if (kb_controls.shift_pressed)
                    {
                        uint8_t c = is_alpha(keymap[1][scancode]) ? keymap[1][scancode] + 32 : keymap[1][scancode];
                        putchar(c);
                        buffer_putchar(c);
                    }
                    else
                    {
                        uint8_t c = is_alpha(keymap[0][scancode]) ? keymap[0][scancode] - 32 : keymap[0][scancode];
                        putchar(c);
                        buffer_putchar(c);
                    }
                }
                else if (kb_controls.shift_pressed)
                {
                    if (kb_controls.caps_pressed)
                    {
                        uint8_t c = is_alpha(keymap[1][scancode]) ? keymap[1][scancode] + 32 : keymap[1][scancode];
                        putchar(c);
                        buffer_putchar(c);
                    }
                    else
                    {
                        uint8_t c = keymap[1][scancode];
                        putchar(c);
                        buffer_putchar(c);
                    }
                }
                else
                {
                    uint8_t c = keymap[0][scancode];
                    putchar(c);
                    buffer_putchar(c);
                }
            }
            break;
        }
        };
    }
}

void buffer_putchar(uint8_t c)
{
    if (c == '\b')
    {
        buffer_back();
        return;
    }
    if (c == '\n')
    {
        buffer[kb_buffer.size] = 0;
        kb_buffer.text = buffer;
        add_to_history(kb_buffer.text);
        command_controller();
        buffer_clear();
        return;
    }
    for (int i = kb_buffer.size; i >= kb_buffer.position; i--)
        buffer[i + 1] = buffer[i];
    buffer[kb_buffer.position++] = c;
    kb_buffer.size++;
}
void buffer_clear()
{
    kb_buffer.size = 0;
    kb_buffer.position = 0;
    buffer[kb_buffer.size] = 0;
}
void add_to_buffer(char *text)
{
    for (int i = 0;; i++)
    {
        if (text[i] == 0)
            break;
        buffer_putchar(text[i]);
    }
}
void buffer_back()
{
    for (int i = kb_buffer.position; i <= kb_buffer.size; i++)
        buffer[i] = buffer[i + 1];

    kb_buffer.size--;
    kb_buffer.position--;
}
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
    kb_controls.shift_pressed = 0;
    kb_controls.caps_pressed = 0;
    kb_controls.ctrl_pressed = 0;

    kb_buffer.size = 0;
    kb_buffer.position = 0;
    init_history();
}