/*
 * dft.h
 *
 *  Created on: 2017-7-9
 *      Author: fly
 */

#ifndef DFT_H_
#define DFT_H_

void FakeDFT(float* seq, int* seq_dft, int num);
void FFT(float* seq, float* seq_dft, int num);
#endif /* DFT_H_ */
