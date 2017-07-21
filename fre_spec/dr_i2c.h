#ifndef __DR_I2C_H_
#define __DR_I2C_H_

#include <stdint.h>

#ifndef SMCLK_FREQ
  #define SMCLK_FREQ 20000000
#endif

#define I2C_FREQ 100000

//��ʼ��I2C����
void initI2C();

//������regд��value�����������Ƿ���뻺����
int I2C_RequestSend(uint8_t slave, uint8_t reg, uint8_t value);

//���һ��I2C�����󣬷��ز�ѯ�ô���
int I2C_AddRegQuery(uint8_t slave, uint8_t reg);

//���һ��I2C�������Ƿ��Ѷ�����ֵ
int I2C_QueryHasNew(int index);

//Ҫ�󷵻�һ��I2C�������ֵ��ͬʱ���ԭʼֵΪ�ɣ�׼��������һ�β�ѯ
uint16_t I2C_CheckQuery(int index);

#endif
