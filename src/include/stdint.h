#include <stdbool.h>

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed long int int32;
typedef unsigned long int uint32;

typedef signed long long int int64;
typedef unsigned long long int uint64;

#ifndef __bool_true_false_are_defined
typedef uint8 bool;
#define true 1 
#define false 0
#endif