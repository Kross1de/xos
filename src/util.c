#include "include/util.h"

void memset(void *dest, char val, uint32 count){
  char *temp = (char*) dest;
  for(; count != 0; count--){
    *temp++ = val;
  }
}