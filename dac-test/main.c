#include "msp430f6638.h"
#include "DAC8552.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	DAC8552_init();
	voltage_output(Channel_A, 1);
	voltage_output(Channel_B, 1);
	_NOP();
}
