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

void initGdt();
void setGdtGate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);