#include "msp430f6638.h"
#include "AD9854.h"
#include "DAC8552.h"

//defines of the gradient decent algo
#define THRESHOLD_1 2048
#define THRESHOLD_2 1024
#define THRESHOLD_3 3072
#define LR 1
//test register
uchar temp;
unsigned int adc_buf = 0;
unsigned int dac_buf = 3000;
unsigned int threshold = 0;
int temp_buf = 0;
int weight = 0;
void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	AD9854_CtrlBus_DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
	AD9854_UDCLK_l;
	AD9854_RST_h;
	delay(4);
	AD9854_RST_l;
	temp = AD9854_RD_Byte(0x1D);
	AD9854_Init();
	DAC8552_init();
	//ADC INIT
	  REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
	                                            // ADC12_A ref control registers
	  ADC12CTL0 = ADC12SHT0_8 + ADC12REF2_5V +  ADC12ON;
	                                            // Internal ref = 1.5V
	  ADC12CTL1 = ADC12SHP;                     // enable sample timer
	  ADC12MCTL0 = ADC12INCH_13;  				// ADC i/p ch A10 = temp sense i/p
	  ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
	  __delay_cycles(75);                       // 75us delay to allow Ref to settle
	  ADC12CTL0 |= ADC12ENC;
//	AD9854_SetSine(50_000_000, 4095);
	int i = 0;
	while(1)
	{
//		_DINT();
		AD9854_SetSine(20000, 4095);
        threshold = THRESHOLD_1;
//		temp_buf = (330 - (adc_buf/10))*40;
//		dac_buf = (unsigned int)temp_buf;
		voltage_output(Channel_A, dac_buf);
//		_EINT();
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
	  //fix step length optimize
	  /*if (ADC12MEM0 > 2048)
	  {
	      if(dac_buf <= 32 )
	          dac_buf = dac_buf;
		  else
		      dac_buf = dac_buf - 16;
	  }
	  else
	  {
	   	  if(dac_buf > 16384)
	   		  dac_buf = dac_buf;
    	  else
    		  dac_buf = dac_buf + 16;
      }*/
	  //gradient decent optimize
      adc_buf = ADC12MEM0;
	  if(adc_buf > threshold)
	  {
          if(dac_buf == 0)
              dac_buf = dac_buf;
          else
          {
        	  if(dac_buf <= adc_buf - threshold)
        		  dac_buf = 0;
        	  else
        		  dac_buf = dac_buf - (adc_buf - threshold) / LR;
          }
	  }
	  else
	  {
          if(dac_buf == 16384)
        	  dac_buf = dac_buf;
          else
          {
        	  if(16384 - dac_buf <= threshold - adc_buf)
        		  dac_buf = 16384;
        	  else
        		  dac_buf = dac_buf + (threshold - adc_buf) / LR;
          }
	  }
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
