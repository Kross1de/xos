#include "gdt.h"

extern void gdt_flush(struct gdt_ptr *ptr);

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdt_ptr;

void initGdt(){
  gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
  gdt_ptr.base = (unsigned int)&gdt_entries;

  setGdtGate(0,0,0,0,0);  //Null segment
  setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF); //Kernel code segment
  setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF); //Kernel data segment
  setGdtGate(3,0,0xFFFFFFFF,0xFA,0xCF); //User code segment
  setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF); //User data segment
  gdt_flush(&gdt_ptr);
}

void setGdtGate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran){
  gdt_entries[num].base_low = (base & 0xffff);
  gdt_entries[num].base_mid = (base >> 16) & 0xff;
  gdt_entries[num].base_high = (base >> 24) & 0xff;
  gdt_entries[num].limit = (limit & 0xffff);
  gdt_entries[num].flags = (limit >> 16) & 0x0f;
  gdt_entries[num].flags |= (gran & 0xf0);
  gdt_entries[num].access = access;
}