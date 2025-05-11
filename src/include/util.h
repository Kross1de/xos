#ifndef UTIL_H
#define UTIL_H

#include "stdint.h"

void memset(void *dest, char val, uint32 count);
void outPortB(uint16 port, uint8 value);

struct InterruptRegisters{
  uint32 cr2;
  uint32 ds;
  uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32 int_no, err_code;
  uint32 eip, cs, eflags, useresp, ss;
};

#endif