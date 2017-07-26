#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

#define SPI_CS_DIR    P1DIR |=  BIT3
#define SPI_CS_UP     P1OUT |=  BIT3
#define SPI_CS_DOWN   P1OUT &= ~BIT3
#define SPI_SCLK_DIR  P1DIR |=  BIT0
#define SPI_SCLK_UP   P1OUT |=  BIT0
#define SPI_SCLK_DOWN P1OUT &= ~BIT0
#define SPI_MOSI_DIR  P1DIR |=  BIT1
#define SPI_MOSI_UP   P1OUT |=  BIT1
#define SPI_MOSI_DOWN P1OUT &= ~BIT1
#define SPI_OUT_HIGH  ((data &  BIT7) == BIT7)
void delay(double t);
void SpiSendByte(unsigned char data);
void SpiInitMaster(void);


#endif /* SPI_MASTER_H_ */
