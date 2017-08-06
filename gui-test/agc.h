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

#define MODE_AGC 1      //auto gain control mode
#define MODE_GC  2      //gain control mode
#define THRESHOLD_1 2048
#define THRESHOLD_2 1024
#define THRESHOLD_3 3072
#define NUM_STEP   16   //number of gain control output steps

unsigned int gradient_optim(unsigned int temp_adc, unsigned int temp_dac, unsigned int threshold, unsigned int lr);
void dac_output(unsigned int mode, unsigned int dac_buf, unsigned char indice_gc);

#endif /* AGC_H_ */
//sample init
/*
 * initClock();
	init_9854_port();
	init_9854();
	init_DAC8552();
    set_sine(2000000);
 */
