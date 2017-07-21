#ifndef _DAC8552_h_
#define _DAC8552_h_

#include "msp430f6638.h"
#define CTL_1 P3DIR |= 0x0f
#define CTL_0 P3DIR &= ~0x00

#define SYNC1 P3OUT |= BIT0
#define SCLK1 P3OUT |= BIT1
#define DIN1 P3OUT |= BIT2

#define SYNC0 P3OUT &= ~BIT0
#define SCLK0 P3OUT &= ~BIT1
#define DIN0 P3OUT &= ~BIT2

#define Channel_B 0x10u
#define Channel_A 0x24u
#define Channel_AB 0x30u

void DAC8552_write(unsigned char commond, unsigned int date);
//void voltage_output(unsigned char channel, double vl2);
void voltage_output(unsigned char channel, unsigned int vl2);
void DAC8552_init(void);

#endif
