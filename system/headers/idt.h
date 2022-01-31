#ifndef IDT_H
#define IDT_H
#include "system.h"
#include "idt.h"
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);
void idt_install();
#endif