#include "system/headers/print.h"
#include "system/headers/string.h"
#include "system/headers/system.h"
#include "system/headers/gdt.h"
#include "system/headers/idt.h"
#include "system/headers/isr.h"
#include "system/headers/irq.h"
#include "system/headers/time.h"
#include "system/headers/keyboard.h"
#include "system/headers/command.h"
#include "system/headers/threads.h"




void init(){
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_cmd();
    threads_install();
    keyboard_install();
    terminal_install();
    print_logo();
    print_intro();
    start_thread((uint32_t)loop_date,"date");
    __asm__ __volatile__ ("sti");
}

void kernel_main()
{
    clear();
    init();
    
}
