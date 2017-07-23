#include "msp430f6638.h"
#include "AD9854.h"
#include "button.h"
#define kHz      *1000
#define MODE_SWE 0      //sweep frequency mode
#define MODE_POI 1      //point frequency mode
#define BUTTON_UP   3
#define BUTTON_DOWN 1
#define BUTTON_MODE 4
#define NUM_STEP   16   //number of sweep output steps
//mode register
unsigned int mode = 1;
int indice_poi = 8;
//sweep frequency buffer
double swe_buf[NUM_STEP] = {2000, 2100, 2200, 2300,
                                  2400, 2500, 2600, 2700,
                                  2800, 2900, 3000, 3100,
                                  3200, 3300, 3400, 3500};
//button register
uchar last_btn = 0x1F, cur_btn, temp;

#define XT2_FREQ   4000000
#define MCLK_FREQ 16000000
#define SMCLK_FREQ 4000000
void initButton();
void freqOutput();
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

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    init();
    init_9854();
    initButton();
//    set_sine(swe_buf[4] kHz);
    while(1)
    {
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
       	    		if(mode == MODE_SWE)
       	    			mode = MODE_POI;
       	    		else
       	    			mode = MODE_SWE;
       	    	}
       	    	if(i == BUTTON_DOWN)
       	    	{
       	    		if(indice_poi == 0)
       	    			indice_poi = indice_poi;
       	    		else
       	    			indice_poi = indice_poi - 1;
       	    	}
       	    	if(i == BUTTON_UP)
       	    	{
       	    		if(indice_poi == NUM_STEP)
       	    			indice_poi = indice_poi;
       	    		else
       	    			indice_poi = indice_poi + 1;
       	    	}
       	    	//frequency output
   		        freqOutput();
       	    }
       	}

    }
}
void initButton()
{
	int i;
	for(i=0;i<5;++i)
	    *LED_GPIO[i]->PxDIR |= LED_PORT[i];
	P4REN |= 0x1F;
	P4OUT |= 0x1F;
}
void freqOutput(void)
{
	if(mode == MODE_SWE)
	{

		int i = 0;                                            //SWE mode
	    for(i=0; i<NUM_STEP; i++)
	    {
	    	init_9854();
	    	set_sine(swe_buf[i] kHz);
            delayus(10000);
	    }
	}
	else
	{
		init_9854();
		set_sine(swe_buf[indice_poi] kHz);                    //POI  mode
	}
}
