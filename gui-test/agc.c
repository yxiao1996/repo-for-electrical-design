/*
 * agc.c
 *
 *  Created on: 2017-8-4
 *      Author: xiaoy
 */
#include "agc.h"

unsigned int gc_buf[NUM_STEP] = {1024,  2048,  3072,  4096,
		                         5120,  6144,  7168,  8192,
                                 9216,  10240, 11264, 12288,
                                 13312, 14336, 15360, 16384};

void dac_output(unsigned int mode, unsigned int dac_buf, unsigned char indice_gc)
{
	if(mode == MODE_AGC)
		voltage_output(Channel_A, dac_buf);          //AGC mode
	else
		voltage_output(Channel_A, gc_buf[indice_gc]);//GC  mode
}

unsigned int gradient_optim(unsigned int temp_adc, unsigned int temp_dac, unsigned int threshold, unsigned int lr)
{
	unsigned int adc_buf = temp_adc;
	unsigned int dac_buf = temp_dac;
	unsigned int LR = lr;
	if(adc_buf > threshold)
	{
        if(dac_buf == 0)
            dac_buf = dac_buf;
        else
        {
    	    if(dac_buf <= adc_buf - threshold)
      		    dac_buf = 0;
      	    else
      		    dac_buf = dac_buf - (adc_buf - threshold) / LR;
        }
	}
	else
	{
        if(dac_buf == 16384)
      	    dac_buf = dac_buf;
        else
        {
      	    if(16384 - dac_buf <= threshold - adc_buf)
      		    dac_buf = 16384;
      	    else
      		    dac_buf = dac_buf + (threshold - adc_buf) / LR;
        }
	}
	return dac_buf;
}


