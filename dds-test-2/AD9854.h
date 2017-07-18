#ifndef __AD9854_H
#define __AD9854_H	
#include "msp430f6638.h"

#define AD9854_DataBus_OUT P6OUT
#define AD9854_DataBus_DIR P6DIR
#define AD9854_DataBus_IN P6IN

#define AD9854_AddrBus_OUT P2OUT
#define AD9854_AddrBus_DIR P2DIR

#define AD9854_CtrlBus_DIR P8DIR
#define AD9854_RST_h P8OUT |= BIT1
#define AD9854_RST_l P8OUT &= ~BIT1
#define AD9854_UDCLK_h P8OUT |= BIT2
#define AD9854_UDCLK_l P8OUT &= ~BIT2
#define AD9854_WR_h P8OUT |= BIT3
#define AD9854_WR_l P8OUT &= ~BIT3
#define AD9854_RD_h P8OUT |= BIT4
#define AD9854_RD_l P8OUT &= ~BIT4
#define AD9854_OSK_h P8OUT |= BIT5
#define AD9854_OSK_l P8OUT &= ~BIT5
#define AD9854_FDATA_h P8OUT |= BIT6
#define AD9854_FDATA_l P8OUT &= ~BIT6

#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long

extern void AD9854_Init(void);
extern void AD9854_SetSine(ulong Freq, uint Shape);

#endif
