#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_
//slave device: msp430f6638
#define SPI_CS_DIR   P1DIR &= ~BIT7
#define SPI_CS_UP    ((P1IN &  BIT7) == BIT7)
#define SPI_SCLK_DIR P1DIR &= ~BIT0
#define SPI_SCLK_UP  ((P1IN &  BIT0) == BIT0)
#define SPI_MOSI_DIR P1DIR &= ~BIT2
#define SPI_MOSI_UP  ((P1IN &  BIT2) == BIT2)
#define LED_DIR      P4DIR |=  BIT5
#define LED_UP       P4OUT |=  BIT5
#define LED_DOWN     P4OUT &= ~BIT5
#define BYTE_LEN     8

unsigned char SpiReceByte(void);
void SpiInitSlave(void);


#endif /* SPI_SLAVE_H_ */
