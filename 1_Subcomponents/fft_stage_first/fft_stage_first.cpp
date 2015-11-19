#include"fft_stage_first.h"
#include <stdio.h>
#include <math.h>
/*
 * Function: fft_stage_first_op calculates the first stage of the FFT.
 * 
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	OUT_R, OUT_I[]: Real and Imag parts of Complex signal
*/

//=======================BEGIN: FFT fft_stage_first_op =========================
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

	const int stage = 1;
	const int DFTpts = 1<<stage;
	const int numBF = DFTpts/2;
	const DTYPE e = -6.283185307178/DFTpts;
	const DTYPE a = 0.0;
	const DTYPE c = cos(a);
	const DTYPE s = sin(a);

	for (int i = 0; i < SIZE; i += DFTpts) {
		const int i_lower = i + 1;
		const DTYPE temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
		const DTYPE temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

		OUT_R[i_lower] = X_R[i] - temp_R;
		OUT_I[i_lower] = X_I[i] - temp_I;
		OUT_R[i] = X_R[i] + temp_R;
		OUT_I[i] = X_I[i] + temp_I;
	}

}
//=======================END: FFT fft_stage_first_op =========================

