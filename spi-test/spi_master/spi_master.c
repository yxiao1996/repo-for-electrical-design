#include"spi_master.h"
#include"msp430.h"

void SpiSendByte(unsigned char data)
{
	int i;
	//chip select up
	SPI_CS_UP;
	delay(2);
	for(i=0; i<8; i++)
	{
	    //output data to MOSI port
	    if(SPI_OUT_HIGH)
	    {
	        SPI_MOSI_UP;
	    }
	    else
	    {
	        SPI_MOSI_DOWN;
	    }
	    data <<= 1;
	    //synchronize clock up
	    SPI_SCLK_UP;
	    delay(2);
	    //read MISO feedback signal(pending..)
	    // synchronize clock down
	    SPI_SCLK_DOWN;
	    delay(2);
	    _NOP();//reserved for debug
	}
	//chip select down
	SPI_CS_DOWN;
}
void SpiInitMaster(void)
{
	//SPI port init
	SPI_CS_DIR;
	SPI_SCLK_DIR;
	SPI_MOSI_DIR;
	//SPI signal init
	SPI_CS_DOWN;
	SPI_SCLK_DOWN;
}
void delay(double t)
{
	while(t--)
	{
		_NOP();
		_NOP();
		_NOP();
	}
}
