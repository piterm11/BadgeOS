#include "../headers/time.h"

void set_frequency(int32_t hz)
{
    int32_t divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

volatile int32_t timer_ticks = 0;
void timer_handler(struct regs *r)
{
    timer_ticks++;
    if(timer_ticks>=1000000) timer_ticks=0;
}

void timer_install()
{
    set_frequency(1000);
    irq_install_handler(0, timer_handler);
}

void sleep(int32_t milis)
{
    unsigned long s_ticks = timer_ticks + milis / (1000 / FREQUENCY);
    while (timer_ticks < s_ticks);
}

uint32_t conv_b2d(uint8_t value)
{
    return (value & 0x0F) + ((value / 16) * 10);
}
char *days_of_week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void print_date()
{
    outportb(0x70, 1 << 7 | SECONDS);
    uint32_t sec = conv_b2d(inportb(0x71));
    outportb(0x70, 1 << 7 | MINUTES);
    uint32_t min = conv_b2d(inportb(0x71));
    outportb(0x70, 1 << 7 | HOURS);
    uint32_t h = conv_b2d(inportb(0x71)) + 1;
    outportb(0x70, 1 << 7 | DAY);
    uint32_t day = conv_b2d(inportb(0x71));
    outportb(0x70, 1 << 7 | MONTH);
    uint32_t mon = conv_b2d(inportb(0x71));
    outportb(0x70, 1 << 7 | CENTURY);
    uint32_t y = conv_b2d(inportb(0x71)) * 100;
    outportb(0x70, 1 << 7 | YEAR);
    y += conv_b2d(inportb(0x71));
    outportb(0x70, 1 << 7 | WEEKDAY);
    uint32_t wday = conv_b2d(inportb(0x71));

    char date[20] = {0};
    char *d = date;
    itoa(h, d);
    itoa(min, (d + 3));
    itoa(sec, (d + 6));
    itoa(day, (d + 9));
    itoa(mon, (d + 12));
    itoa(y, (d + 15));
    if (h < 10)
    {
        put_at('0', 0, 0);
        put_at(*(d), 1, 0);
    }
    else
    {
        put_at(*(d), 0, 0);
        put_at(*(d + 1), 1, 0);
    }
    put_at(':', 2, 0);

    if (min < 10)
    {
        put_at('0', 3, 0);
        put_at(*(d + 3), 4, 0);
    }
    else
    {
        put_at(*(d + 3), 3, 0);
        put_at(*(d + 4), 4, 0);
    }
    put_at(':', 5, 0);
    if (sec < 10)
    {
        put_at('0', 6, 0);
        put_at(*(d + 6), 7, 0);
    }
    else
    {
        put_at(*(d + 6), 6, 0);
        put_at(*(d + 7), 7, 0);
    }

    if (day<10)
    {
        put_at('0', 0, 1);
        put_at(*(d + 9), 1, 1);
    }
    else
    {
        put_at(*(d + 9), 0, 1);
        put_at(*(d + 10), 1, 1);
    }
    put_at('/', 2, 1);

    if (mon < 10)
    {
        put_at('0', 3, 1);
        put_at(*(d + 12), 4, 1);
    }
    else
    {
        put_at(*(d + 12), 3, 1);
        put_at(*(d + 13), 4, 1);
    }
    put_at('/', 5, 1);
    if (y < 10)
    {
        put_at('0', 6, 1);
        put_at(*(d + 15), 7, 1);
    }
    else
    {
        put_at(*(d + 15), 6, 1);
        put_at(*(d + 16), 7, 1);
        put_at(*(d + 17), 8, 1);
        put_at(*(d + 18), 9, 1);
    }
    for(int i=0;i<strlen(*(days_of_week+wday-1));i++)
    {
        put_at(*(*(days_of_week+wday-1)+i),i,2);
    }
}

void loop_date()
{
    for (;;)
    {
        sleep(100);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                put_at(' ', j, i);
            }
        }
        print_date();
    }
}