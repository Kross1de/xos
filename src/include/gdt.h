#include "stdint.h"

struct gdt_entry{
  uint16 limit;
  uint16 base_low;
  uint8 base_mid;
  uint8 access;
  uint8 flags;
  uint8 base_high;
} __attribute__((packed));

struct gdt_ptr{
  uint16 limit;
  unsigned int base;
} __attribute__((packed));

struct tss_entry{
  uint32 prev_tss;
  uint32 esp0;
  uint32 ss0;
  uint32 esp1;
  uint32 ss1;
  uint32 esp2;
  uint32 ss2;
  uint32 cr3;
  uint32 eip;
  uint32 eflags;
  uint32 eax;
  uint32 ecx;
  uint32 edx;
  uint32 ebx;
  uint32 esp;
  uint32 ebp;
  uint32 esi;
  uint32 edi;
  uint32 es;
  uint32 cs;
  uint32 ss;
  uint32 ds;
  uint32 fs;
  uint32 gs;
  uint32 ldt;
  uint32 trap;
  uint32 iomap_base;
} __attribute__((packed));

void initGdt();
void setGdtGate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);
void writeTSS(uint32 num, uint16 ss0, uint32 esp0);