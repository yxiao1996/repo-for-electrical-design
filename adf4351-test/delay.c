#include"msp430.h"
#include"delay.h"

void delay_us(unsigned char t)
{
	while(t--)
	{
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
	}
}