#include"msp430g2553.h"
#include"spi_slave.h"
/*#define Uchar unsigned char
#define SPI_SCLK_IN    (P1IN & 0x01)
#define SPI_MOSI_IN    (P1IN & 0x02)
#define SPI_MISO_UP    P1OUT |= BIT2
#define SPI_MISO_DOWN  P1OUT &= ~BIT2
#define SPI_CS_IN      (P1IN & 0x08)
#define SPI_SCLK_DIR   P1DIR &= ~BIT0
#define SPI_MOSI_DIR   P1DIR &= ~BIT1
#define SPI_MISO_DIR   P1DIR |= BIT2
#define SPI_CS_DIR     P1DIR &=~BIT3*/
void main(void)
{
	
	SPI_SCLK_DIR_SL;
	SPI_MOSI_DIR_SL;
	SPI_MISO_DIR_SL;
	SPI_CS_DIR_SL;
//	Uchar temp, i;
	Uchar temp = 0;
	while(1)
	{
		/*if(SPI_CS_IN == 1)
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
		}*/
		temp = SpiReceByte();
	}
}
