#include "msp430.h"
#define Uchar unsigned char
//device: msp430f6638
//status: master
/*
#define SPI_SCLK_UP       P1OUT |= BIT0
#define SPI_SCLK_DOWN     P1OUT &= ~BIT0
#define SPI_MOSI_UP       P1OUT |= BIT2
#define SPI_MOSI_DOWN     P1OUT &= ~BIT2
#define SPI_MISO_IN       (P1IN & 0x10)
#define SPI_CS_UP         P1OUT |= BIT7
#define SPI_CS_DOWN       P1OUT &= ~BIT7
#define SPI_SCLK_DIR_MA   P1DIR |= BIT0
#define SPI_MOSI_DIR_MA   P1DIR |= BIT2
#define SPI_MISO_DIR_MA   P1DIR &= ~BIT4
#define SPI_CS_DIR_MA     P1DIR |= BIT7
*/
//device: msp430f5529
//status: master
#define SPI_SCLK_UP       P7OUT |= BIT0
#define SPI_SCLK_DOWN     P7OUT &= ~BIT0
#define SPI_MOSI_UP       P7OUT |= BIT1
#define SPI_MOSI_DOWN     P7OUT &= ~BIT1
#define SPI_MISO_IN       (P7IN & 0x04)
#define SPI_CS_UP         P7OUT |= BIT3
#define SPI_CS_DOWN       P7OUT &= ~BIT3
#define SPI_SCLK_DIR_MA   P7DIR |= BIT0
#define SPI_MOSI_DIR_MA   P7DIR |= BIT1
#define SPI_MISO_DIR_MA   P7DIR &= ~BIT2
#define SPI_CS_DIR_MA     P7DIR |= BIT3

//function declare
//master functions:
Uchar SpiSendByte(Uchar data);
