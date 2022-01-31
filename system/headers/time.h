#ifndef TIME_H
#define TIME_H
#include "system.h"
#include "irq.h"
#include "print.h"

#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS 0x04
#define WEEKDAY 0x06
#define DAY 0x07
#define MONTH 0x08
#define YEAR 0x09
#define CENTURY 0x32
#define REG_B 0x0B



#define FREQUENCY 1000
void timer_phase(int32_t hz);
void timer_handler(struct regs *r);
void timer_install();
void sleep(int32_t milis);
void print_date();
void loop_date();

#endif 