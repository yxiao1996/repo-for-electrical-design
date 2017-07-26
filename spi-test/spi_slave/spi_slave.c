#include"spi_slave.h"
#include"msp430.h"
void SpiInitSlave(void)
{
	 //SPI port init
	 SPI_CS_DIR;
	 SPI_SCLK_DIR;
	 //LED init
     LED_DIR;
}

unsigned char SpiReceByte(void)
{
	int i = 0;
	unsigned char temp = 0;
	while(! SPI_CS_UP)
	    {_NOP();}
	for(i=0; i<BYTE_LEN; i++)
  	{
	    LED_DOWN;
	    while(! SPI_SCLK_UP)
	    	{_NOP();}
	    LED_UP;
	    temp <<= 1;
	    if(SPI_MOSI_UP)
	    {
	    	temp = temp + 1;
	   	}
	   	else
	    {
	    	temp = temp + 0;
	   	}
	    while(SPI_SCLK_UP)
	    	_NOP();
	}
	   	_NOP();//reserved for breakpoint;
	   	return temp;
}

