#include "../../include/util.h"

void memset(void *dest, char val, uint32 count){
  char *temp = (char*) dest;
  for(; count != 0; count--){
    *temp++ = val;
  }
}

void outPortB(uint16 port, uint8 value){
  asm volatile ("outb %1, %0" : : "dN"(port), "a"(value));
}