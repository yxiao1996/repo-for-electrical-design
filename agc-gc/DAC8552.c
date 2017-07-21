#include "DAC8552.h"

#define Vref  2.48f

void DAC8552_init(void)
{
	CTL_1;					 
}
void DAC8552_write(unsigned char commond, unsigned int date)
{
	unsigned char i;
	SCLK1;
	SYNC0;
	for(i=0; i<8; i++)
	{
		if (commond & 0x80)
		{
		  DIN1;
		}
		else
		{
		  DIN0;
		}
		SCLK0;
		commond <<= 1;
		SCLK1;
	} 
	for (i=0; i<16; i++)
	{
		if (date & 0x8000)
		{
			DIN1;
		}
		else
		{
			DIN0;
		}
		SCLK0;
		date <<= 1;
		SCLK1;
	} 
	SYNC1;
}
void voltage_output(unsigned char channel, unsigned int vl2)
{
	DAC8552_write(channel, vl2);
}
/*
void voltage_output(unsigned char channel, double vl2)
{
	unsigned int vl;
	
	vl = (unsigned int)(vl2 / Vref * 0xffff);
	DAC8552_write(channel, vl);
}
*/
