#ifndef COMMAND_H
#define COMMAND_H
#include "print.h"
#include "keyboard.h"
#include "time.h"
#include "threads.h"

void command_controller();

void init_cmd();
void echo(char* text);
void length(char* text);
void cls();
void help();
void controls();
void history();
int counter(char* text);
void counting();
void threads();
void _kill(int8_t id);
void kill(char* text);
void mutex_test();
void _mutex_test();
void test();
void testing();


void calc(char* text);
void add(float a, float b);
void sub(float a, float b);
void multiply(float a, float b);
void divide(float a, float b);

#endif