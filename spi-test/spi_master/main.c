#include"msp430g2553.h"
#include"spi_master.h"

unsigned char temp = 0x33;
void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	SpiInitMaster();
	//demo function: auto counting
	int i;
	while(1)
	{
		for(i=0; i<255; i++)
		{
			SpiSendByte(i);
			delay(300);
		}
	}
}
