#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include "system.h"
#include "print.h"

void trunc(char *text, char *ret, char *rest);
int strcomp(char *a, char *b);
int strlen(const char *str);
int atoi(const char tab[]);
float atof(const char tab[]);

int itoa(const int v, char *ret);
#endif