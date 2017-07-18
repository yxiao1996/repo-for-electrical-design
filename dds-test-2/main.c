#include "msp430f6638.h"
#include "AD9854.h"

//test register
uchar temp;

void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	AD9854_CtrlBus_DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
//	AD9854_RST_l;
//	_NOP();
//	AD9854_RST_h;
//	_NOP();
//	AD9854_RST_l;
	AD9854_UDCLK_l;
	AD9854_RST_h;
	delay(4);
	AD9854_RST_l;
	temp = AD9854_RD_Byte(0x1D);
	AD9854_Init();
	AD9854_SetSine(50000000, 4095);
	while(1);
}
