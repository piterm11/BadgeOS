OUTFILE := kernel.bin 
TARGET := target
DIST := dist
ISODIR := isodir
SRC := $(shell find system/ -name "*.c")
OBJECTS := $(patsubst %.c, $(TARGET)/%.o, $(SRC))
CFLAGS := -O2 -fomit-frame-pointer -fno-builtin -m32 -fno-pie -fno-stack-protector


full:
	make comp
	make clean

comp:
	nasm start.asm -f elf32 -o $(TARGET)/start.o
	gcc system/lib/print.c -c -o $(TARGET)/system/lib/print.o $(CFLAGS)
	gcc system/lib/string.c -c -o $(TARGET)/system/lib/string.o $(CFLAGS)
	gcc system/lib/system.c -c -o $(TARGET)/system/lib/system.o $(CFLAGS)
	gcc system/driver/gdt.c -c -o $(TARGET)/system/driver/gdt.o $(CFLAGS)
	gcc system/driver/idt.c -c -o $(TARGET)/system/driver/idt.o $(CFLAGS)
	gcc system/driver/isr.c -c -o $(TARGET)/system/driver/isr.o $(CFLAGS)
	gcc system/driver/irq.c -c -o $(TARGET)/system/driver/irq.o $(CFLAGS)
	gcc system/lib/time.c -c -o $(TARGET)/system/lib/time.o $(CFLAGS)
	gcc system/lib/keyboard.c -c -o $(TARGET)/system/lib/keyboard.o $(CFLAGS)
	gcc system/lib/ctype.c -c -o $(TARGET)/system/lib/ctype.o $(CFLAGS)
	gcc system/lib/command.c -c -o $(TARGET)/system/lib/command.o $(CFLAGS)
	gcc system/lib/threads.c -c -o $(TARGET)/system/lib/threads.o $(CFLAGS)

	gcc kernel.c -m32 -O2 -fno-pie -fno-stack-protector -fno-builtin -c -o $(TARGET)/kernel.o
	ld -Tlinker.ld -o $(ISODIR)/boot/$(OUTFILE) $(OBJECTS) $(TARGET)/kernel.o $(TARGET)/start.o
	grub-mkrescue /usr/lib/grub/i386-pc -o $(DIST)/badgeOS.iso $(ISODIR)

clean:
	find . -type f -name '*.o' -delete