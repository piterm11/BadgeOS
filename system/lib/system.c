#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "../headers/system.h"
uint8_t inportb(uint16_t _port)
{
    unsigned char rv;
    __asm__ __volatile__("inb %1, %0": "=a"(rv): "dN"(_port));
    return rv;
}

void outportb(uint16_t _port, uint16_t _data)
{
    __asm__ __volatile__("outb %1, %0":: "dN"(_port), "a"(_data));
}

void* memcpy(void *dest, const void *src, size_t size)
{
    const uint8_t *csrc = (const uint8_t *)src;
    char *cdest = (char *)dest;

    while (size--)
    {
        *cdest++ = *csrc++;
    }
    return dest;
}

void* memset(void *dest, char val, size_t size)
{

    char *p = (char *)dest;
    while (size--)
    {
        *p++ = val;
    }
    return dest;
}