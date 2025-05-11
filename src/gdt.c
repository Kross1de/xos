#include "include/gdt.h"
#include "include/util.h"

extern void gdt_flush(uint32);
extern void tss_flush();

struct gdt_entry gdt_entries[6];
struct gdt_ptr gdt_ptr;
struct tss_entry tss_entry;

void initGdt(){
  gdt_ptr.limit = (sizeof(struct gdt_entry) * 6) - 1;
  gdt_ptr.base = (uint32)&gdt_entries;

  setGdtGate(0,0,0,0,0);  //Null segment
  setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF); //Kernel code segment
  setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF); //Kernel data segment
  setGdtGate(3,0,0xFFFFFFFF,0xFA,0xCF); //User code segment
  setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF); //User data segment
  writeTSS(5,0x10,0x0);
  gdt_flush((uint32)&gdt_ptr);
  tss_flush();
}

void writeTSS(uint32 num, uint16 ss0, uint32 esp0){
  uint32 base = (uint32) &tss_entry;
  uint32 limit = base + sizeof(tss_entry);

  setGdtGate(num, base, limit, 0xE9, 0x00);
  memset(&tss_entry, 0, sizeof(tss_entry));

  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;
  tss_entry.cs = 0x08 | 0x3;
  tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
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