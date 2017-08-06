/*
 * debug.c
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */
#include"msp430f6638.h"
#include"debug.h"
void initDebug_LED(void)
{
	LED1_DIR;
	LED2_DIR;
    LED1_DOWN;
    LED2_UP;
}


