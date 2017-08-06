/*
 * initInt.h
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */
#include"msp430f6638.h"
#define ADC12_MODE_DEBUG 1
#define ADC12_MODE_INPUT 2
#define NUM_SEQ        256

void initTA0(unsigned int threshold);
unsigned int* initADC12(unsigned char mode);
//sample int program
/*
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)              // 定时器中断触发,P3输出口异或,电平翻转
{
    LED_FLOP;
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
    __bis_SR_register(LPM4_bits + GIE);     // LPM0 with interrupts enabled
    __no_operation();
}
*/

/*
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
	temp = ADC12MEM0;
	temp_seq[indice] = temp;
	indice = (indice + 1) % NUM_SEQ;
	*(temp_buffer + indice) = ADC12MEM0;
    __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}

 */
