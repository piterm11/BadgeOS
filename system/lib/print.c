#include "../headers/print.h"



void terminal_install()
{
    term.screen = (struct Char *)0xb8000;
    term.first_column=FIRST_COL;
    term.first_row=FIRST_ROW;
    term.num_cols=NUM_COLS;
    term.num_rows=NUM_ROWS;
    term.col=0;
    term.row=0;
}

uint8_t color = WHITE | BLACK << 4;


void move_csr()
{
    unsigned t = term.col + term.row * 80;
    outportb(0x3D4, 14);
    outportb(0x3D5, t >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, t);
}
void move(enum direction d)
{
    switch (d)
    {
    // case LEFT:
    // {
    //     if (term.col > term.first_column)
    //     {
    //         kb_buffer.position--;
    //         term.col--;
    //     }
    //     else
    //     {
    //         kb_buffer.position = 0;
    //         term.col = term.first_column;
    //     }
    //     break;
    // }
    // case RIGHT:
    // {

    //     if (term.col < term.num_cols - 1)
    //     {
    //         if (term.screen[term.col + term.num_cols * term.row].character != ' ' || term.screen[term.col+1 + term.num_cols * term.row].character != ' ')
    //         {
    //             kb_buffer.position++;
    //             term.col++;
    //         }
    //     }
    //     else
    //     {
    //         kb_buffer.position = term.num_cols - 1;
    //         term.col = term.num_cols - 1;
    //     }
    //     break;
    // }
    }
    move_csr();
}

void clear_input()
{
    struct Char empty = {' ', color};

    for (size_t c = 0; c < term.num_cols; c++)
    {
        term.screen[c + term.num_cols * term.row] = empty;
    }
    term.col = term.first_column;
    putchar('>');
    move_csr();
}

void clear_row(size_t r)
{
    struct Char empty = {' ', color};

    for (size_t c = 0; c < term.num_cols; c++)
    {
        term.screen[c + term.num_cols * r] = empty;
    }
    term.col = term.first_column;
    move_csr();
}

void clear()
{
    for (size_t i = term.first_row-1; i < term.num_rows; i++)
    {
        clear_row(i);
    }
    term.row = term.first_row;
    move_csr();
}

void _newline()
{
    term.col = term.first_column;
    if (term.row < term.num_rows - 1)
    {
        term.row++;
        return;
    }

    for (size_t r = term.first_row; r < term.num_rows; r++)
    {
        for (size_t c = 0; c < term.num_cols; c++)
        {
            struct Char character = term.screen[c + term.num_cols * r];
            term.screen[c + term.num_cols * (r - 1)] = character;
        }
    }

    clear_row(term.num_rows - 1);
}
void _tab()
{
    term.col += 8 - term.col % 8;
}
void _back()
{

    struct Char empty = {' ', color};
    if (term.col > term.first_column + 1)
    {
        term.col--;
    }
    else
        term.col = term.first_column + 1;
    term.screen[term.col + term.num_cols * term.row] = empty;
}
void _return()
{
    term.col = 0;
}
void _vert()
{
    term.row++;
}

void print_logo()
{
    print_set_color(LIGHT_GREEN, BLACK);
    print_ln("                    _               _             ___  ____");
    print_ln("                   | |__   __ _  __| | __ _  ___ / _ \\/ ___|");
    print_ln("                   | '_ \\ / _` |/ _` |/ _` |/ _ \\ | | \\___ \\");
    print_set_color(LIGHT_BLUE, BLACK);
    print_ln("                   | |_) | (_| | (_| | (_| |  __/ |_| |___) |");
    print_ln("                   |_.__/ \\__,_|\\__,_|\\__, |\\___|\\___/|____/");
    print_ln("                                      |___/");
    print_set_color(WHITE, BLACK);
}

void print_emote()
{
    print_ln("                                           ");
    print_ln("    @@@@@@                          @@@@@@    ");
    print_ln("    @@//// @@@(                 (( @@//// @@@   ");
    print_ln("     @@@@@@@     @@@@@@@@@@@     @@@@@@@      ");
    print_ln("        @        @@@@@@@@@@@        @        ");
    print_ln("           ,.@@    @@@@@@@@ ,.@@              ");
    print_ln("     @@    /...    @@@@@@@@ /...     @@@        ");
    print_ln("    @@@@@@          @@@@@@          @@@@@@        ");
    print_ln("    @@@@@@@@@@@@@@@         @@@@@@@@@@@@@@");
    print_ln("    @@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@ ///##///");
    print_ln("    @@@@@@@@@@                 @@@@@@  /####/#///");
    print_ln("    @@@@@@@@@@@    (((##     ( @@@@@  (######/##/");
    print_ln("      @@@@@@@@@@@@  ###(  * @@@@@@@@ ##/##/###//");
    print_ln("            # @@@@@@@@@@@@@@@@@##   (#////////((");
    print_ln("     (   (((        @@@@@       / ###////////((");
    print_ln("       ( (/////////////////****..(#///////((");
}

void print_intro()
{
    print("Hello! If you need write '");
    print_set_color(LIGHT_GREEN, BLACK);
    print("help");
    print_set_color(WHITE, BLACK);
    print_ln("'");
    print(">");
}

void print_char(char character)
{
    if (character == '\n')
    {
        _newline();
        return;
    }

    putchar(character);
}

void print_str(char *str)
{
    for (size_t i = 0;; i++)
    {
        char character = (uint8_t)str[i];

        if (character == '\0')
        {
            return;
        }

        print_char(character);
    }
}

void print_int(int value)
{
    if (value < 0)
    {
        putchar('-');
        value *= -1;
    }
    int t, x = value, rev = 0, len = 0;
    do
    {
        t = x % 10;
        rev = rev * 10 + t;
        x /= 10;
        len++;
    } while (x != 0);
    for (size_t i = 0; i < len; i++)
    {
        t = rev % 10;
        if (rev == 0)
            putchar('0');
        else
            putchar(t + '0');
        rev /= 10;
    }
}

void print_float(float value)
{
    if (value < 0)
    {
        putchar('-');
        value *= -1;
    }
    int a = value;
    print_int(a);
    putchar('.');
    float f1 = value - a;
    for (size_t i = 0; i < 3; i++)
    {
        f1 *= 10;
        if (f1 < 1)
            putchar('0');
    }

    a = f1;
    print_int(a);
}

void print_set_color(uint8_t foreground, uint8_t background)
{
    color = foreground + (background << 4);
}

void check_and_place_newline()
{
    if (term.col > term.num_cols)
    {
        _newline();
    }
}
void putchar(uint8_t c)
{
    check_and_place_newline();
    if (c == '\t')
        _tab();
    else if (c == '\n')
        _newline();
    else if (c == '\b')
        _back();
    else if (c == '\r')
        _return();
    else if (c == '\v')
        _vert();
    else
    {
        check_and_place_newline();
        term.screen[term.col + term.num_cols * term.row].character = c;
        term.screen[term.col + term.num_cols * term.row].color = color;
        term.col++;
        move_csr();
    }
    check_and_place_newline();
    move_csr();
}
void put_at(uint8_t c, uint16_t col, uint16_t row){
    check_and_place_newline();
    if (c == '\t')
        _tab();
    else if (c == '\n')
        _newline();
    else if (c == '\b')
        _back();
    else if (c == '\r')
        _return();
    else if (c == '\v')
        _vert();
    else
    {
        check_and_place_newline();
        term.screen[col + term.num_cols * row].character = c;
        term.screen[col + term.num_cols * row].color = color;
    }
    check_and_place_newline();

}

void print(char *format, ...)
{
    va_list list;
    va_start(list, format);
    int size = (int)strlen(format);
    for (size_t i = 0; i < size;)
    {
        if (*(format + i) == '%')
        {
            i++;
            switch (*(format + i))
            {
            case 'c':
            {
                i++;
                char s = va_arg(list, int);
                putchar(s);
                break;
            }
            case 's':
            {
                i++;
                char *s = va_arg(list, char *);
                int len = (int)strlen(s);
                for (int i = 0; i < len; i++)
                    putchar(*(s + i));
                break;
            }
            case 'd':
            {
                i++;
                int l = va_arg(list, int);
                print_int(l);
                break;
            }
            case 'f':
            {
                i++;
                double f = va_arg(list, double);
                print_float(f);
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else
        {
            putchar(*(format + i));
            i++;
        }
    }
    va_end(list);
}
void print_ln(char *format, ...)
{
    va_list list;
    va_start(list, format);
    int size = (int)strlen(format);
    for (size_t i = 0; i < size;)
    {
        if (*(format + i) == '%')
        {
            i++;
            switch (*(format + i))
            {
            case 'c':
            {
                i++;
                char s = va_arg(list, int);
                putchar(s);
                break;
            }
            case 's':
            {
                i++;
                char *s = va_arg(list, char *);
                int len = (int)strlen(s);
                for (int i = 0; i < len; i++)
                    putchar(*(s + i));
                break;
            }
            case 'd':
            {
                i++;
                int l = va_arg(list, int);
                print_int(l);
                break;
            }
            case 'f':
            {
                i++;
                double f = va_arg(list, double);
                print_float(f);
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else
        {
            putchar(*(format + i));
            i++;
        }
    }
    va_end(list);
    putchar('\n');
}

char getchar()
{
    char c = kb_buffer.text[0];
    for (size_t i = 0; i < kb_buffer.size; i++)
    {
        kb_buffer.text[i] = kb_buffer.text[i + 1];
    }
    kb_buffer.size--;
    return c;
}

// void scan(char *format, ...)
// {
//     va_list list;
//     va_start(list, format);
//     int counter = 0;
//     int size = (int)strlen(format);
//     for (int i = 0; i < size;)
//     {
//         if (*(format + i) == '%')
//         {
//             i++;
//             switch (*(format + i))
//             {
//             case 's':
//             {
//                 i++;
//                 char *r = va_arg(list, char *);
//                 if (get_str(r) == 0)
//                     counter++;
//                 break;
//             }
//             case 'd':
//             {
//                 i++;
//                 int *r = va_arg(list, int *);
//                 if (get_int(r) == 0)
//                     counter++;
//                 break;
//             }
//             case 'f':
//             {
//                 i++;
//                 double *r = va_arg(list, double *);
//                 if (get_float(r) == 0)
//                     counter++;
//                 break;
//             }
//             default:
//             {
//                 break;
//             }
//             }
//         }
//         else
//         {
//             i++;
//         }
//     }
//     va_end(list);
// }
// int get_str(char *res)
// {
//     char c;
//     char *t = res;
//     for (int i = 0;; i++)
//     {
//         c = getchar();
//         if (c == 0 || c == '\n' || c == ' ')
//         {
//             *t++ = 0;
//             break;
//         }
//         else
//             *t++ = c;
//     }
// }
// int get_int(int *res)
// {
//     int neg = 1, w = 0;
//     char c;
//     for (int i = 0;; i++)
//     {
//         c = getchar();
//         if (i == 0 && is_alpha(c))
//             return -1;
//         if (i == 0 && c == '-')
//             neg = -1;
//         else if (is_digit(c))
//         {
//             w *= 10;
//             w += c - '0';
//         }
//         else if (c == 0 || c == '\n' || c == ' ' || is_alpha(c))
//             break;
//         else
//             return -1;
//     }
//     w *= neg;
//     *res = w;
//     return 0;
// }
// int get_float(double *res)
// {
//     int integer = 0;
//     double fact = 0;
//     int neg = 1, dotto = 0, fact_len = 0;
//     char c;
//     for (int i = 0;; i++)
//     {
//         c = getchar();
//         if (i == 0 && is_alpha(c))
//             return -1;
//         if (i == 0 && c == '-')
//             neg = -1;
//         else if (i != 0 && c == '.' && dotto == 0)
//             dotto++;
//         else if (is_digit(c) && dotto == 0)
//         {
//             integer *= 10;
//             integer += c - '0';
//         }
//         else if (is_digit(c) && dotto == 1)
//         {
//             fact *= 10;
//             fact += c - '0';
//             fact_len++;
//         }
//         else if (c == 0 || c == '\n' || c == ' ' || is_alpha(c))
//             break;
//         else
//             return -1;
//     }
//     for (int i = 0; i < fact_len; i++)
//         fact /= 10;
//     double w = (integer + fact) * neg;
//     *res = w;
//     return 0;
// }