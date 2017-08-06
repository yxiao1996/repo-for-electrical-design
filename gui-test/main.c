#include <msp430.h> 
#include "initInt.h"
#include "agc.h"
#include "dr_tft.h"
#include "initClock.h"
#include "button.h"
#include "gui.h"

/*
 * REMENBER: the size of the TFT screen: (319, 239) -- (320, 240)
 */

//global variables
unsigned char option = 1;
unsigned char mode = 1;
unsigned char indice_gc = 8;
unsigned int adc_buf = 0;
unsigned int dac_buf = 3000;
unsigned int threshold = THRESHOLD_1;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	initClock();
	init_9854_port();
	init_9854();
	init_DAC8552();
	initADC12(ADC12_MODE_INPUT);
	initTFT();
	initButton();
	_EINT();
	Draw_OptionBox(2);
	Print_Confirm(mode);
	set_sine(3500000);
	while(1)
	{
		checkButton_gui(&mode, &option, 2);
		Refresh_OptionBox(option, 2);
		if(mode == MODE_GC)
		{
			checkButton_agc_gc(&mode, &indice_gc);
		}
		dac_output(mode, dac_buf, indice_gc);
		ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
		__bis_SR_register(LPM4_bits + GIE);     // LPM0 with interrupts enabled
		__no_operation();
	}
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
	  //gradient decent optimize
      adc_buf = ADC12MEM0;
      dac_buf = gradient_optim(adc_buf, dac_buf, threshold, 1);
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
