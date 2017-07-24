#include"msp430f6638.h"
#include"spi_master.h"
Uchar temp = 0;

void main(void)
{
	SPI_SCLK_DIR_MA;
	SPI_CS_DIR_MA;
	SPI_MISO_DIR_MA;
	SPI_MOSI_DIR_MA;
	Uchar data = 0xEE;
	while(1)
	{
		temp = SpiSendByte(data);
		_NOP();
	}
}
