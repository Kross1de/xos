gcc = i686-elf-gcc
CFLAGS = -ffreestanding -Wall -Wextra -g -O2

all: clean kernel boot image

clean:
	rm -rf *.o
	rm -rf *.iso

kernel:
	$(gcc) $(CFLAGS) -c src/main.c -o obj/main.o
	$(gcc) $(CFLAGS) -c src/drivers/vga.c -o obj/vga.o
	$(gcc) $(CFLAGS) -c src/cpu/gdt.c -o obj/gdt.o
	$(gcc) $(CFLAGS) -c src/utils/basic/util.c -o obj/util.o
	$(gcc) $(CFLAGS) -c src/cpu/idt.c -o obj/idt.o
	$(gcc) $(CFLAGS) -c src/cpu/timer.c -o obj/timer.o

boot:
	nasm -f elf32 src/boot.s -o obj/boot.o
	nasm -f elf32 src/cpu/gdt.s -o obj/gdts.o
	nasm -f elf32 src/cpu/idt.s -o obj/idts.o
image:
	ld -m elf_i386 -T linker.ld -o kernel obj/main.o obj/vga.o obj/boot.o obj/gdt.o obj/gdts.o obj/util.o obj/idt.o obj/idts.o obj/timer.o
	mv kernel XOS/boot/kernel
	grub-mkrescue -o xos.iso XOS/
	rm obj/*.o

run:
	qemu-system-i386 -cdrom xos.iso