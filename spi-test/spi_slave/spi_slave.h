#include "msp430.h"
#define Uchar unsigned char

//device: msp430g2553
//status: slave
#define SPI_SCLK_IN       (P1IN & 0x01)
#define SPI_MOSI_IN       (P1IN & 0x02)
#define SPI_MISO_UP       P1OUT |= BIT2
#define SPI_MISO_DOWN     P1OUT &= ~BIT2
#define SPI_CS_IN         (P1IN & 0x08)
#define SPI_SCLK_DIR_SL   P1DIR &= ~BIT0
#define SPI_MOSI_DIR_SL   P1DIR &= ~BIT1
#define SPI_MISO_DIR_SL   P1DIR |= BIT2
#define SPI_CS_DIR_SL     P1DIR &=~BIT3
//function declare
//slave functions:
Uchar SpiReceByte(void);
