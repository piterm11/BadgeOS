#include "../headers/string.h"

void trunc(char *text, char *ret, char *rest)
{

    char *p = text;
    int len = 0, len_rest = 0;
    for (size_t i = 0;; i++)
    {
        if (len == 0)
        {
            if (*p == ' ' || *p == 0 || *p == '\n')
            {
                len = i;
            }
        }
        else
        {
            if (*p == 0 || *p == '\n')
            {
                len_rest = i-len;
                break;
            }
        }
        p++;
    }
    memcpy(ret, text, len);
    ret[len] = 0;
    memcpy(rest, text+len+1, len_rest);
}

int strcomp(char *a, char *b)
{
    if (a == 0 && b == 0)
        return 0;
    if (b == 0)
        return -1;
    if (a == 0)
        return 1;

    int len = strlen(a) > strlen(b) ? strlen(a) : strlen(b);
    for (size_t i = 0; i < len; i++)
    {
        if (a[i] == 0 || b[i] == 0)
            break;
        if (a[i] != b[i])
        {
            return a[i] > b[i] ? -1 : 1;
        }
    }
    if(strlen(a) == strlen(b))
        return 0;
    return strlen(a) > strlen(b) ? -1 : 1;
}
int strlen(const char *str)
{
    int i = 0;
    for (;;)
    {
        if (str[i] == '\0')
            break;
        i++;
    }
    return i;
}
int atoi(const char tab[])
{
    int i = 0, znak = 1, wynik = 0;
    if (tab[0] == '-')
    {
        znak = -1;
        i++;
    }
    for (; i < 16; i++)
    {
        if (tab[i] == '.')
        {
            break;
        }
        else if (tab[i] == '\0' || tab[i] == '\n')
        {
            break;
        }
        else if (tab[i] >= 48 && tab[i] <= 57)
        {
            wynik = wynik * 10 + tab[i] - 48;
        }
    }
    return wynik * znak;
}
float atof(const char tab[])
{

    int i = 0, znak = 1;
    float wynik = 0.0;
    if (tab[0] == '-')
    {
        znak = -1;
        i++;
    }
    for (; i < 16; i++)
    {
        if (tab[i] == '.')
        {
            i++;
            break;
        }
        else if (tab[i] == '\0' || tab[i] == '\n')
        {
            break;
        }
        else if (tab[i] >= 48 && tab[i] <= 57)
        {
            wynik = wynik * 10 + tab[i] - 48;
        }
    }
    int power = 10;
    for (; i < 16; i++)
    {
        if (tab[i] == '\0' || tab[i] == '\n')
        {
            break;
        }
        else if (tab[i] >= 48 && tab[i] <= 57)
        {
            wynik = wynik + (tab[i] - 48) / (float)power;
            power *= 10;
        }
    }

    return wynik * znak;
}

int itoa(const int v, char *ret)
{
    char* p = ret;
    int x = v;
    if (x < 0)
    {
        *p++='-';
        x *= -1;
    }
    int t, rev = 0, len = 0;
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
        {
            *p++='0';
        }
        else
        {
            *p++='0'+t;
        }
        rev /= 10;
    }
    *p=0;
}