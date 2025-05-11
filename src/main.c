#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"

void kmain(void);

void kmain(void){
       Reset();
       print("\t\t\t\t\t\t===============================\r\n");
       print("\t\t\t\t\t\t==     Hello from x86 os!    ==\r\n");
       print("\t\t\t\t\t\t==  Copyright 2025 Kross1de  ==\r\n");
       print("\t\t\t\t\t\t===============================\r\n");
       initGdt();
       print("GDT is done!\r\n");
       initIdt();
       print("IDT is done!\r\n");
       print(1/0);
}
