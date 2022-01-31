#ifndef SYSTEM_H
#define SYSTEM_H
#include <stddef.h>
#include <stdint.h>
struct regs
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void* memcpy(void *dest, const void *src, size_t size);
void* memset(void *dest, char value, size_t size);
uint8_t inportb (uint16_t _port);
void outportb (uint16_t _port, uint16_t _data);
#endif