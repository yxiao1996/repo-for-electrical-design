//test program for ADF4351
#include "msp430g2553.h"
#include "ADF4351.h"
#include "delay.h"
//#include "initClock.h"
unsigned char buf[4] = {0,0,0,0};

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
//    initClock();
//	ADF_Output_GPIOInit();
//	ADF4351Init();
	ADF4351Init_210();
	P1DIR |= BIT6;
	P1DIR &= ~BIT7;
	while(1)
	{
		if(P1IN & BIT7)
			P1OUT |= BIT6;
		if(!(P1IN & BIT7))
			P1OUT &= ~BIT6;
	}
/*	buf[3] = 0x00;
	buf[2] = 0x58;
	buf[1] = 0x00;				
 	buf[0] = 0x05;				
	WriteToADF4351(4,buf);	
	
    ADF_put_GPIOInit();*/
}
