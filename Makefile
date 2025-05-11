CFLAGS = -m32 -fno-stack-protector -fno-builtin

all: clean kernel boot image

clean:
	rm -rf *.o

kernel:
	gcc $(CFLAGS) -c src/main.c -o obj/main.o
	gcc $(CFLAGS) -c src/vga.c -o obj/vga.o
	gcc $(CFLAGS) -c src/gdt.c -o obj/gdt.o
	gcc $(CFLAGS) -c src/util.c -o obj/util.o

boot:
	nasm -f elf32 src/boot.s -o obj/boot.o
	nasm -f elf32 src/gdt.s -o obj/gdts.o
image:
	ld -m elf_i386 -T linker.ld -o kernel obj/main.o obj/vga.o obj/boot.o obj/gdt.o obj/gdts.o obj/util.o
	mv kernel XOS/boot/kernel
	grub-mkrescue -o xos.iso XOS/
	rm obj/*.o

run:
	qemu-system-i386 -cdrom xos.iso