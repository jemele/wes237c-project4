#include<stdio.h>
#include"fft_stages.h"
/*
 * Function: fft_stage_first_op calculates the first stage of FFT.
 * 
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal
	stage: stage number: //Possible values of STAGE=2,3,4,5,6,7,8,9

OUTPUT:
	OUT_R, OUT_I[]: Real and Imag parts of Complex signal
*/

//=======================BEGIN: FFT fft_stages =========================
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
#pragma HLS DATAFLOW
	const int DFTpts = 1<<stage;
	const int numBF = DFTpts/2;
	const int phase_increment = 1024/DFTpts;
	int p = 0;
	int i = 0;
	int iteration = 0;
	DTYPE c = W_real[p];
	DTYPE s = W_imag[p];
	for (int j=0; j<SIZE2; ++j, i+= DFTpts) {
#pragma HLS PIPELINE enable_flush
		if (i >= SIZE) {
			i = ++iteration;
			p = (p + phase_increment)%512;
			c = W_real[p];
			s = W_imag[p];
		}

		const int i_lower = i + numBF;
		const DTYPE temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
		const DTYPE temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

		OUT_R[i_lower] = X_R[i] - temp_R;
		OUT_I[i_lower] = X_I[i] - temp_I;
		OUT_R[i] = X_R[i] + temp_R;
		OUT_I[i] = X_I[i] + temp_I;
	}
}
//=======================END: FFT fft_stages =========================
