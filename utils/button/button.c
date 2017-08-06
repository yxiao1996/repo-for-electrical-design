#include "button.h"
#include "agc.h"
#include "initClock.h"

const GPIO_TypeDef GPIO4 =
{
  &P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL
};

const GPIO_TypeDef GPIO5 =
{
  &P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL
};

const GPIO_TypeDef GPIO8 =
{
  &P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL
};

const GPIO_TypeDef* LED_GPIO[5] = {&GPIO4, &GPIO4, &GPIO4, &GPIO5, &GPIO8};
const unsigned char LED_PORT[5] = {BIT5, BIT6, BIT7, BIT7, BIT0};

unsigned char last_btn = 0x1F, cur_btn, temp;

void initButton(void)
{
	int i;
	for(i=0;i<5;++i)
	    *LED_GPIO[i]->PxDIR |= LED_PORT[i];
    P4REN |= 0x1F;
	P4OUT |= 0x1F;
}

void checkButton_agc_gc(unsigned char* mode, unsigned char* indice_gc)
{
	cur_btn = P4IN & 0x1F;
	temp = (cur_btn ^ last_btn) & last_btn;
	last_btn = cur_btn;
	unsigned char temp_btn;
	int i;
	for(i=0;i<5;++i)
	{
	    if(temp & (1 << i))
	    {
	    	_delay_cycles(MCLK_FREQ/100);
	    	temp_btn = P4IN & 0x1F;
	    	/*temp = (cur_btn ^ last_btn) & last_btn;
	    	last_btn = cur_btn;*/
	    	if(cur_btn == temp_btn)
	    	{
	    	*LED_GPIO[i]->PxOUT ^= LED_PORT[i];
	    	if(i == BUTTON_MODE)
	    	{
	    		if(*mode == MODE_AGC)
	    			*mode = MODE_GC;
	    		else
	    			*mode = MODE_AGC;
	    	}
	    	if(i == BUTTON_DOWN)
	    	{
	    		if(*indice_gc == 0)
	    			*indice_gc = *indice_gc;
	    		else
	    			*indice_gc = *indice_gc - 1;
	    	}
	    	if(i == BUTTON_UP)
	    	{
	    		if(*indice_gc == NUM_STEP)
	    			*indice_gc = *indice_gc;
	    		else
	    			*indice_gc = *indice_gc + 1;
	    	}
	    	}
	    }
	}
}
