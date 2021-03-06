#include "msp430f6638.h"
#include "AD9854.h"
#include "DAC8552.h"
#include "button.h"

//defines of the gradient decent optimization algo
#define THRESHOLD_1 2048
#define THRESHOLD_2 1024
#define THRESHOLD_3 3072
#define LR 1
#define MODE_AGC 0      //auto gain control mode
#define MODE_GC  1      //gain control mode
#define BUTTON_UP   3
#define BUTTON_DOWN 1
#define BUTTON_MODE 4
#define NUM_STEP   16   //number of gain control output steps
//mode register
unsigned int mode = 0;
unsigned char indice_gc = 8;
//gain control outputs (GC mode)
unsigned int gc_buf[NUM_STEP] = {1024,  2048,  3072,  4096,
		                         5120,  6144,  7168,  8192,
                                 9216,  10240, 11264, 12288,
                                 13312, 14336, 15360, 16384};
//adc dac buffer (AGC mode)
uchar temp;
unsigned int adc_buf = 0;
unsigned int dac_buf = 3000;
unsigned int threshold = THRESHOLD_1;
int temp_buf = 0;
int weight = 0;
#define XT2_FREQ   4000000
#define MCLK_FREQ 16000000
#define SMCLK_FREQ 4000000
void initClock()
{
  while(BAKCTL & LOCKIO)
    BAKCTL &= ~(LOCKIO);
  UCSCTL6 &= ~XT1OFF;
  P7SEL |= BIT2 + BIT3;
  UCSCTL6 &= ~XT2OFF;
  while (SFRIFG1 & OFIFG) {
    UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG);
    SFRIFG1 &= ~OFIFG;
  }

  UCSCTL4 = SELA__XT1CLK + SELS__XT2CLK + SELM__XT2CLK;

  UCSCTL1 = DCORSEL_5;
  UCSCTL2 = MCLK_FREQ / (XT2_FREQ / 16);
  UCSCTL3 = SELREF__XT2CLK + FLLREFDIV__16;
  while (SFRIFG1 & OFIFG) {
    UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT2OFFG);
    SFRIFG1 &= ~OFIFG;
  }
  UCSCTL5 = DIVA__1 + DIVS__1 + DIVM__1;
  UCSCTL4 = SELA__XT1CLK + SELS__XT2CLK + SELM__DCOCLK;
}


void dac_output(void)
{
	if(mode == MODE_AGC)
		voltage_output(Channel_A, dac_buf);          //AGC mode
	else
		voltage_output(Channel_A, gc_buf[indice_gc]);//GC  mode
}

void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	init();
	init_9854();
	DAC8552_init();
	//ADC INIT
	REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
	                                            // ADC12_A ref control registers
	ADC12CTL0 = ADC12SHT0_8 + ADC12REF2_5V +  ADC12ON;
	                                            // Internal ref = 1.5V
	ADC12CTL1 = ADC12SHP;                     // enable sample timer
	ADC12MCTL0 = ADC12INCH_15;  				// ADC i/p ch A10 = temp sense i/p
	ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
	__delay_cycles(75);                       // 75us delay to allow Ref to settle
	ADC12CTL0 |= ADC12ENC;
//	test for button program
	int i;
	for(i=0;i<5;++i)
	    *LED_GPIO[i]->PxDIR |= LED_PORT[i];
    P4REN |= 0x1F;
	P4OUT |= 0x1F;
    uchar last_btn = 0x1F, cur_btn, temp;
    //DDS set sine output
	set_sine(2000000);
    while(1)
	{
//		_DINT();
		//check button
    	cur_btn = P4IN & 0x1F;
    	temp = (cur_btn ^ last_btn) & last_btn;
    	last_btn = cur_btn;
    	int i;
    	for(i=0;i<5;++i)
    	{
    	    if(temp & (1 << i))
    	    {
    	        *LED_GPIO[i]->PxOUT ^= LED_PORT[i];
    	    	if(i == BUTTON_MODE)
    	    	{
    	    		if(mode == MODE_AGC)
    	    			mode = MODE_GC;
    	    		else
    	    			mode = MODE_AGC;
    	    	}
    	    	if(i == BUTTON_DOWN)
    	    	{
    	    		if(indice_gc == 0)
    	    			indice_gc = indice_gc;
    	    		else
    	    			indice_gc = indice_gc - 1;
    	    	}
    	    	if(i == BUTTON_UP)
    	    	{
    	    		if(indice_gc == NUM_STEP)
    	    			indice_gc = indice_gc;
    	    		else
    	    			indice_gc = indice_gc + 1;
    	    	}
    	    }
    	}
		//adc output
		dac_output();
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
