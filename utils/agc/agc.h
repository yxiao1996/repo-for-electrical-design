/*
 * agc.h
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */
#include "AD9854.h"
#include "DAC8552.h"
#ifndef AGC_H_
#define AGC_H_

#define MODE_AGC 0      //auto gain control mode
#define MODE_GC  1      //gain control mode
#define THRESHOLD_1 2048
#define THRESHOLD_2 1024
#define THRESHOLD_3 3072

unsigned int gradient_optim(unsigned int temp_adc, unsigned int temp_dac, unsigned int threshold, unsigned int lr);
void dac_output(unsigned int mode, unsigned int dac_buf, unsigned int* gc_buf, unsigned int indice_gc);

#endif /* AGC_H_ */
