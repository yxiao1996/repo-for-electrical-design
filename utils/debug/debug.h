/*
 * debug.h
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define LED1_DIR  P4DIR |=  BIT5
#define LED1_UP   P4OUT |=  BIT5
#define LED1_DOWN P4OUT &= ~BIT5
#define LED1_FLOP P4OUT ^=  BIT5

#define LED2_DIR  P4DIR |=  BIT6
#define LED2_UP   P4OUT |=  BIT6
#define LED2_DOWN P4OUT &= ~BIT6
#define LED2_FLOP P4OUT ^=  BIT6

void initDebug_LED(void);


#endif /* DEBUG_H_ */
