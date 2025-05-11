#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "registers.h"
#include "idt.h"

//PIT base frequency
#define PIT_BASE_FREQ 1193182

//PIT channels and ports
#define PIT_CHANNEL0 0x40
#define PIT_CMD_PORT 0x43

//PIT command byte components
#define PIT_BINARY_MODE   0x00
#define PIT_BCD_MODE      0x01
#define PIT_MODE_2        0x04
#define PIT_RW_BOTH       0x30
#define PIT_CHANNEL0_SEL  0x00

//Default timer frequency
#define DEFAULT_PIT_FREQ 100

extern uint64 ticks;
/**
 * Initialize the PIT with specified frequency
 * @param freq Desired frequency in Hz
 * @return 0 on success, -1 on invalid frequency
 */
int initTimer(uint32 freq);

/**
 * IRQ0 handler for PIT interrupts
 * @param regs Interrupt registers
 */
void onIrq0(struct InterruptRegisters *regs);

#endif