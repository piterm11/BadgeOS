#include "../headers/ctype.h"

int is_digit(unsigned char c)
{
    return c>='0'&&c<='9'?1:0;
}

int is_alpha(unsigned char c)
{
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z')?1:0;
}