#ifndef BUTTON_H_
#define BUTTON_H_
#include "msp430.h"

#define BUTTON_UP   3
#define BUTTON_DOWN 1
#define BUTTON_MODE 4
#define NUM_STEP   16   //number of gain control output steps

typedef struct
{
  const volatile unsigned char* PxIN;
  volatile unsigned char* PxOUT;
  volatile unsigned char* PxDIR;
  volatile unsigned char* PxREN;
  volatile unsigned char* PxSEL;
} GPIO_TypeDef;
/*
const GPIO_TypeDef GPIO4 =
{
  &P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL
};

const GPIO_TypeDef GPIO5 =
{
  &P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL
};

const GPIO_TypeDef GPIO8 =
{
  &P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL
};

const GPIO_TypeDef* LED_GPIO[5] = {&GPIO4, &GPIO4, &GPIO4, &GPIO5, &GPIO8};
const unsigned char LED_PORT[5] = {BIT5, BIT6, BIT7, BIT7, BIT0};
*/
void initButton(void);
void checkButton_agc_gc(unsigned char* mode, unsigned char* indice_gc);

#endif /* BUTTON_H_ */
