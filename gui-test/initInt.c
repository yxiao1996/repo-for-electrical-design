/*
 * initInt.c
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */
#include"msp430f6638.h"
#include"initInt.h"
void initTA0(unsigned int threshold)
{
	TA0CCR0 = threshold;                        // 定义中断计数周期1s,时钟频率为32.768MHZ,32768 / 32768 = 1s
	TA0CCTL0 = CCIE;                        // TA0CCR0捕获/比较中断寄存器中断使能
	TA0CTL = TASSEL_1 + MC_1 + TACLR;       // TASSEL_1,ACLK时钟源  MC_1,增计数模式
}

unsigned int* initADC12(unsigned char mode)
{
	//Init ADC12 registers
	REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
	                                            // ADC12_A ref control registers
	ADC12CTL0 = ADC12SHT0_8 + ADC12REF2_5V +  ADC12ON;
	                                            // Internal ref = 1.5V
	ADC12CTL1 = ADC12SHP;                     // enable sample timer
	//ADC12 channel selection
	if(mode == ADC12_MODE_DEBUG)
	    ADC12MCTL0 = ADC12INCH_15;  				// ADC i/p ch A10 = temp sense i/p
	if(mode == ADC12_MODE_INPUT)
		ADC12MCTL0 = ADC12INCH_13;
	ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
	__delay_cycles(75);                       // 75us delay to allow Ref to settle
	ADC12CTL0 |= ADC12ENC;
	//Init ADC12 buffers
	unsigned int seq[NUM_SEQ];
	unsigned int *buffer_p;
	buffer_p = seq;
	return buffer_p;
}
