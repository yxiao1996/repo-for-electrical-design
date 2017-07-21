//test program to combine the acd adc and lcd lab programs
//put lcd display function in the interupt service fuction 
//inlcude head files from adc program
#include <msp430f6638.h>
//include head files from lcd program
#include <msp430f6638.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "dr_lcdseg.h"
#include "dr_tft.h"
#include "QmathLib.h"
#include ".\include\DSPLib.h"
//declare variables from adc program
int temp_seq;
int tmp0=0, tmp=0;
int adc_buffer = 0;
int adc_flag = 0;
int* buffer_p;
volatile long IntDegF;
volatile long IntDegC;
//define static variables from lcd program
#define XT2_FREQ   4000000
#define MCLK_FREQ 16000000
#define SMCLK_FREQ 4000000
//test define
#define SEQ_NUM 2048
#define CYC_FFT 1
//test global variable
int16_t indice = 0;
int cyc = 0;

//init function from lcd program
void initClock()
{
  while(BAKCTL & LOCKIO) // Unlock XT1 pins for operation
    BAKCTL &= ~(LOCKIO);
  UCSCTL6 &= ~XT1OFF; //XT1
  P7SEL |= BIT2 + BIT3; //XT2
  UCSCTL6 &= ~XT2OFF; //XT2
  while (SFRIFG1 & OFIFG) { //
    UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG);
    SFRIFG1 &= ~OFIFG;
  }

  UCSCTL4 = SELA__XT1CLK + SELS__XT2CLK + SELM__XT2CLK; //

  UCSCTL1 = DCORSEL_5; //6000kHz~23.7MHz
  UCSCTL2 = MCLK_FREQ / (XT2_FREQ / 16); //XT2
  UCSCTL3 = SELREF__XT2CLK + FLLREFDIV__16; //XT2
  while (SFRIFG1 & OFIFG) { //
    UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG);
    SFRIFG1 &= ~OFIFG;
  }
  UCSCTL5 = DIVA__1 + DIVS__1 + DIVM__1; //
  UCSCTL4 = SELA__XT1CLK + SELS__XT2CLK + SELM__DCOCLK; //
}
//main function
void main(void)
{
  //set registers from adc program
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  //declare buffers
  int seq[SEQ_NUM];
  int seq_fft[SEQ_NUM];
  buffer_p = seq;
  msp_fft_q15_params params;

  REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                            // ADC12_A ref control registers
  //use timer0 as sample timer
//  TB0CTL = TBSSEL__SMCLK + MC__UP; // SMCLK, up-mode
//  TB0CCR0 = SMCLK_FREQ - 1; // 4MHz -> 6.4kHz
//  TB0CCTL0 = OUTMOD_4; //实际只有3.2kHz
  ADC12CTL0 = ADC12SHT0_0 + ADC12REF2_5V +  ADC12ON + ADC12MSC;
                                            // Internal ref = 1.5V
  ADC12CTL1 = ADC12SHP + ADC12CONSEQ_2;                     // enable sample timer
  ADC12MCTL0 = ADC12INCH_13;  				// ADC i/p ch A10 = temp sense i/p 15FOR ADC CHANNEL
  ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
  __delay_cycles(75);                       // 75us delay to allow Ref to settle
  ADC12CTL0 |= ADC12ENC;
  P8DIR |= BIT0;
  P5DIR |= BIT7;
  P4DIR |= BIT5+BIT6+BIT7;
  //set registers from lcd program
  _DINT();
  initClock();
  initTFT();
//  initLcdSeg();
  _EINT();
  etft_AreaSet(0, 0, 319, 239, 0);
  //main loop {fft, display}
  while(1)
  {
    temp_seq = seq_fft[127];
    //refresh the seq buffer
//    seq[indice] = adc_buffer;
    //try to put fft here
    int j = 0;
    if(indice == (SEQ_NUM-1))
    {
       	if(cyc == (CYC_FFT-1))
       	{
       		_DINT();
       		//load input to seq_fft
       		for(j=0;j<SEQ_NUM;j++)
       		{
       			seq_fft[j] = seq[j];
       		}
       		//initialize fft input
       		params.length = SEQ_NUM;
       		params.bitReverse = true;
       		params.twiddleTable = msp_cmplx_twiddle_table_2048_q15;
       		//perform fft on seq_fft
       		msp_fft_fixed_q15(&params, seq_fft);
       		cyc = 0;
       		//_EINT();
       		//tft display: total 1024 points try to display first 100 points
       		//_DINT();
       		etft_AreaSet(0, 0, 319, 239, 0);
       		for(j=1;j<318;j++)
       		{
       	    	if(seq_fft[j] > 0)
       			    etft_AreaSet(j, 120-(seq_fft[j]/16), j+1,120 , 2047);
       	    }
  		    _EINT();
       	}
       	else
       		cyc = cyc + 1;
        //pick the largest magnitude
       	/*tmp0 = 0, tmp = 0;
    	for(j=1;j<SEQ_NUM/2;j++)
    	{
    		if(seq_fft[j]>tmp0)
    		{
    			tmp = j;
    			tmp0 = seq_fft[j];
    		}
    		else
    			tmp = tmp;
    	}*/
    }
    //try to display a straight line
//    etft_AreaSet(0, 200, 319, 201, 2047);
//    LCDSEG_DisplayNumber(tmp*45, 0); //lcd display
    //debug lines
//    etft_AreaSet(0, 0, 319, 239, 0);
//    etft_DisplayString("hello mcu", 100, 80, 65535, 0);
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
    __bis_SR_register(LPM4_bits + GIE);     // LPM0 with interrupts enabled
    __no_operation();
  }
}
//interupt function from adc program
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    /*if (ADC12MEM0 > 0xa00)
    {
      P8OUT |= BIT0;
      LCDSEG_DisplayNumber(ADC12MEM0, 0); //display
      __delay_cycles(MCLK_FREQ / 10); //delay 100ms
    }
    else
    {
      P8OUT &=~BIT0;
      LCDSEG_DisplayNumber(11111, 0); //display
      __delay_cycles(MCLK_FREQ / 10); //delay100ms
    }*/
	//try to pick out the max in sequence
	indice = (indice + 1) % SEQ_NUM;
	//adc_buffer = ADC12MEM0;
	//adc_flag = 1;
	*(buffer_p + indice) = ADC12MEM0;
	//try tft display
//	etft_AreaSet(0, 0, 319, 239, 0);
//	etft_AreaSet(0, 200, 319, 201, 2047);
//    int tmp0=0, tmp=0, j=0;
//perform fft when finish sampling
/*    if(indice == (SEQ_NUM-1))
    {
    	if(cyc == (CYC_FFT-1))
    	{
    		//load input to seq_fft
    		for(j=0;j<SEQ_NUM;j++)
    		{
    			seq_fft[j] = seq[j];
    		}
    		//initialize fft input
    		params.length = SEQ_NUM;
    		params.bitReverse = true;
    		params.twiddleTable = msp_cmplx_twiddle_table_128_q15;
    		//perform fft on seq_fft
    		msp_fft_fixed_q15(&params, seq_fft);
    		cyc = 0;
    	}
    	else
    		cyc = cyc + 1;
    }
	//pick the largest magnitude
	for(j=1;j<SEQ_NUM/2;j++)
	{
		if(seq_fft[j]>tmp0)
		{
			tmp = j;
			tmp0 = seq_fft[j];
		}
		else
			tmp = tmp;
	}*/

//	LCDSEG_DisplayNumber(tmp, 0); //display
//	__delay_cycles(MCLK_FREQ / 10); //delay100ms
    // Move results, IFG is cleared
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
