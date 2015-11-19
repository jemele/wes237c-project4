
#include <math.h>
#include <stdio.h>
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
	
	const int DFTpts = 1<<stage;
	const int numBF = DFTpts/2;
	const DTYPE e = -6.283185307178/DFTpts;
	DTYPE a = 0.0;

	const int phase_increment = 1024/DFTpts;
	int p = 0;
printf("your momma\n");
	for(int j=0; j<numBF; ++j) {

#if 0
		const DTYPE c = cos(a);
		const DTYPE s = sin(a);
#else
		const int sign = (p >= 512) ? -1 : 1;

		const DTYPE c = W_real[p];
		const DTYPE c0 = cos(a);
		printf("%d %f %f %f %f\n", p, a, c, c0, fabs(c-c0));
		const DTYPE s = sign * W_imag[p];
		const DTYPE s0 = sin(a);
		printf("%d %f %f %f %f\n", p, a, s, s0, fabs(s-s0));
#endif

		a = a + e;
		p = (p + phase_increment)%512;
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
//=======================END: FFT fft_stages =========================

