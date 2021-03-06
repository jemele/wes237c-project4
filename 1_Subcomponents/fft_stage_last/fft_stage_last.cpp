#include"fft_stage_last.h"

/*
 * Function: fft_stage_first_op calculates the LAST stage of FFT.
 * 
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	OUT_R, OUT_I[]: Real and Imag parts of Complex signal

*/

//=======================BEGIN: FFT fft_stage_last =========================
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

//Write code that computes last stage of FFT 
	int stage = 10;
	const int DFTpts = 1<<stage;
	const int numBF = DFTpts/2;

#if 0
	const DTYPE e = -6.283185307178/DFTpts;
	DTYPE a = 0.0;
#else
	const int phase_increment = 1024/DFTpts;
	int p = 0;
#endif
	for(int j=0; j<numBF; ++j) {

#if 0
		const DTYPE c = cos(a);
		const DTYPE s = sin(a);
		a = a + e;
#else
		const DTYPE c = W_real[p];
		const DTYPE s = W_imag[p];
		p = (p + phase_increment)%512;
#endif
		for (int i = j; i < SIZE; i += DFTpts) {
			const int i_lower = i + numBF;
			const DTYPE temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
			const DTYPE temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

			OUT_R[i_lower] = X_R[i] - temp_R;
			OUT_I[i_lower] = X_I[i] - temp_I;
			OUT_R[i] = X_R[i] + temp_R;
			OUT_I[i] = X_I[i] + temp_I;
		}
	}

	
}
//=======================END: FFT fft_stage_last =========================

