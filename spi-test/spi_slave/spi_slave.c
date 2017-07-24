#include"spi_slave.h"
#include"msp430g2553.h"

Uchar SpiReceByte(void)
{
	Uchar temp = 0, i = 0;
	if(SPI_CS_IN == 1)
	{
		if(SPI_SCLK_IN == 1)
		{
			temp = temp + SPI_MOSI_IN;
			temp <<= 1;
			i++;
			SPI_MISO_UP;
		}
			else
				SPI_MISO_DOWN;
	}
	return temp;
}
