#ifndef BUTTON_H_
#define BUTTON_H_
typedef struct
{
  const volatile uchar* PxIN;
  volatile uchar* PxOUT;
  volatile uchar* PxDIR;
  volatile uchar* PxREN;
  volatile uchar* PxSEL;
} GPIO_TypeDef;

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
const uchar LED_PORT[5] = {BIT5, BIT6, BIT7, BIT7, BIT0};


#endif /* BUTTON_H_ */
