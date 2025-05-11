nasm -f elf32 boot.s -o boot.o
gcc -m32 -fno-stack-protector -fno-builtin -c main.c -o main.o
gcc -m32 -fno-stack-protector -fno-builtin -c vga.c -o vga.o
ld -m elf_i386 -T linker.ld -o kernel main.o vga.o boot.o
mv kernel XOS/boot/kernel
grub-mkrescue -o xos.iso XOS/
qemu-system-i386 -cdrom xos.iso