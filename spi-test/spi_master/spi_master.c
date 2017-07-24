#include"spi_master.h"
#include"msp430f6638.h"
Uchar SpiSendByte(Uchar dat)
{
	Uchar i,temp;
	temp = 0;	
	SPI_SCLK_DOWN;
	for(i=0; i<8; i++)
	{
		if(dat & 0x80)
		{
	     SPI_MOSI_UP;
		}
		else 
		{
		 SPI_MOSI_DOWN;
		}
		dat <<= 1;
	        SPI_SCLK_UP; 
		temp <<= 1;
	if(SPI_MISO_IN)temp++;  //
		SPI_SCLK_DOWN;
	}
	return temp;
}

