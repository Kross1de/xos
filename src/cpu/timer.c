#include "../include/stdint.h"
#include "../include/util.h"
#include "../include/idt.h"
#include "../include/vga.h"
#include "../include/timer.h"

uint64 ticks = 0;
static uint32 current_freq = 0;

void onIrq0(struct InterruptRegisters *regs) {
    ticks++;
}

int initTimer(uint32 freq) {
    if (freq == 0 || freq > PIT_BASE_FREQ) {
        return -1;
    }

    current_freq = freq;
    ticks = 0;

    irq_install_handler(0, &onIrq0);

    uint32 divisor = PIT_BASE_FREQ / freq;

    outPortB(PIT_CMD_PORT, 
             PIT_BINARY_MODE | PIT_MODE_2 | PIT_RW_BOTH | PIT_CHANNEL0_SEL);

    outPortB(PIT_CHANNEL0, (uint8)(divisor & 0xFF));
    outPortB(PIT_CHANNEL0, (uint8)((divisor >> 8) & 0xFF));

    return 0;
}