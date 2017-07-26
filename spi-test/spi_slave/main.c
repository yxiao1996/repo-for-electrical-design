#include <msp430f6638.h>
#include <stdint.h>
#include"spi_slave.h"
#include "dr_lcdseg.h"
//global variables (put in header file)
unsigned char data = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    SpiInitSlave();
    initLcdSeg();
    while(1)
    {
        data = SpiReceByte();
        LCDSEG_DisplayNumber(data, 0);
    }
}
