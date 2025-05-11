#ifndef REGISTERS_H
#define REGISTERS_H

#include "stdint.h"

struct InterruptRegisters{
  uint32 cr2;
  uint32 ds;
  uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32 int_no, err_code;
  uint32 eip, cs, eflags, useresp, ss;
};

#endif