#ifndef UTIL_H
#define UTIL_H

#include "stdint.h"

void memset(void *dest, char val, uint32 count);
void outPortB(uint16 port, uint8 value);

#endif