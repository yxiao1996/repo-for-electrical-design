
/**********************************************************
                       康威科技
更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://kvdz.taobao.com/
**********************************************************/

#ifndef _ADF4351_H_
#define _ADF4351_H_
#include "stdint.h"
/*
#include "sys.h"

#define ADF4351_CLK PBout(15)
#define ADF4351_OUTPUT_DATA PBout(14)
#define ADF4351_LE PBout(13)
#define ADF4351_CE PBout(12)

#define ADF4351_INPUT_DATA PBin(14)
*/
//test device: MSP430G2553
//port: CLK(P1.0), DATA(P1.1), LE(P1.2), CE(P1.3)
//port directions:
#define ADF4351_CLK_DIR           P1DIR |=  BIT0
#define ADF4351_OUTPUT_DATA_DIR   P1DIR |=  BIT1
#define ADF4351_INPUT_DATA_DIR    P1DIR &= ~BIT1
#define ADF4351_LE_DIR            P1DIR |=  BIT2
#define ADF4351_CE_DIR            P1DIR |=  BIT3
//output ports:
#define ADF4351_CLK_UP            P1OUT |=  BIT0
#define ADF4351_CLK_DOWN          P1OUT &= ~BIT0
#define ADF4351_OUTPUT_DATA_UP    P1OUT |=  BIT1
#define ADF4351_OUTPUT_DATA_DOWN  P1OUT &= ~BIT1
#define ADF4351_LE_UP             P1OUT |=  BIT2
#define ADF4351_LE_DOWN           P1OUT &= ~BIT2
#define ADF4351_CE_UP             P1OUT |=  BIT3
#define ADF4351_CE_DOWN           P1OUT &= ~BIT3
//input ports:
#define ADF4351_INPUT_DATA        ((P1IN & BIT1) == BIT1)
/*
//test device: MSP430F6638
#define ADF4351_CLK_DIR           P6DIR |=  BIT0
#define ADF4351_OUTPUT_DATA_DIR   P6DIR |=  BIT1
#define ADF4351_INPUT_DATA_DIR    P6DIR &= ~BIT1
#define ADF4351_LE_DIR            P6DIR |=  BIT2
#define ADF4351_CE_DIR            P6DIR |=  BIT3
//output ports:
#define ADF4351_CLK_UP            P6OUT |=  BIT0
#define ADF4351_CLK_DOWN          P6OUT &= ~BIT0
#define ADF4351_OUTPUT_DATA_UP    P6OUT |=  BIT1
#define ADF4351_OUTPUT_DATA_DOWN  P6OUT &= ~BIT1
#define ADF4351_LE_UP             P6OUT |=  BIT2
#define ADF4351_LE_DOWN           P6OUT &= ~BIT2
#define ADF4351_CE_UP             P6OUT |=  BIT3
#define ADF4351_CE_DOWN           P6OUT &= ~BIT3
//input ports:
#define ADF4351_INPUT_DATA        ((P6IN & BIT1) == BIT1)
*/

void ADF4351Init(void);
void ADF_Output_GPIOInit(void);
void ReadToADF4351(unsigned char count, unsigned char *buf);
void WriteToADF4351(unsigned char count, unsigned char *buf);
//void WriteOneRegToADF4351(u32 Regster);
void ADF4351_Init_some(void);
void ADF4351WriteFreq(float Fre);		//	(xx.x) M Hz
void ADF4351Init_210(void);

#endif

