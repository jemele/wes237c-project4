/*
This is traditional 2-radix DIT FFT algorithm implementation.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	Out_R, Out_I[]: Real and Imag parts of Complex signal
*/

#include <stdio.h>
#include <math.h>
#include "fft.h"

void ofdm(const DTYPE input[SIZE*2], unsigned int output[SIZE]);
void demultiplex_input(const DTYPE input[SIZE], DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
void bit_reverse(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE Bit_R[SIZE], DTYPE Bit_I[SIZE]);
void fft_stage_first(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stages(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], int STAGES, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_last(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void qpsk_decoder(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], unsigned int output_symbols[SIZE]);

void ofdm(const DTYPE in[SIZE*2], unsigned int out[SIZE])
{
#pragma AP interface ap_fifo port=in
#pragma AP interface ap_fifo port=out
#pragma AP interface ap_ctrl_none port=return

#pragma HLS DATAFLOW
    DTYPE X_R[SIZE], X_I[SIZE];
	DTYPE Bit_R[SIZE], Bit_I[SIZE];
	DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
	DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
	DTYPE Stage3_R[SIZE], Stage3_I[SIZE];
	DTYPE Stage4_R[SIZE], Stage4_I[SIZE];
	DTYPE Stage5_R[SIZE], Stage5_I[SIZE];
	DTYPE Stage6_R[SIZE], Stage6_I[SIZE];
	DTYPE Stage7_R[SIZE], Stage7_I[SIZE];
	DTYPE Stage8_R[SIZE], Stage8_I[SIZE];
	DTYPE Stage9_R[SIZE], Stage9_I[SIZE];
	DTYPE OUT_R[SIZE], OUT_I[SIZE];

    demultiplex_input(in, X_R, X_I);
	bit_reverse(X_R, X_I, Bit_R, Bit_I);
	fft_stage_first(Bit_R, Bit_I, Stage1_R, Stage1_I);
	fft_stages(Stage1_R, Stage1_I, 2, Stage2_R, Stage2_I);
	fft_stages(Stage2_R, Stage2_I, 3, Stage3_R, Stage3_I);
	fft_stages(Stage3_R, Stage3_I, 4, Stage4_R, Stage4_I);
	fft_stages(Stage4_R, Stage4_I, 5, Stage5_R, Stage5_I);
	fft_stages(Stage5_R, Stage5_I, 6, Stage6_R, Stage6_I);
	fft_stages(Stage6_R, Stage6_I, 7, Stage7_R, Stage7_I);
	fft_stages(Stage7_R, Stage7_I, 8, Stage8_R, Stage8_I);
	fft_stages(Stage8_R, Stage8_I, 9, Stage9_R, Stage9_I);
	fft_stage_last(Stage9_R, Stage9_I, OUT_R, OUT_I);
    qpsk_decoder(OUT_R, OUT_I, out);
}

void demultiplex_input(const DTYPE input_iq[SIZE*2], DTYPE X_R[SIZE], DTYPE X_I[SIZE])
{
#pragma HLS DATAFLOW
    for (int i = 0; i < SIZE; ++i) {
#pragma HLS PIPELINE enable_flush
        X_R[i] = input_iq[(i*2)];
        X_I[i] = input_iq[(i*2)+1];
    }
}

inline unsigned int reverse(unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    x = ((x >> 16) | (x << 16));

    const unsigned shift = (sizeof(x)*8) - M;
    return x >> shift;
}

// XXX describe this function, please
void bit_reverse(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE Bit_R[SIZE], DTYPE Bit_I[SIZE]){
#pragma HLS dataflow
	for (unsigned int i = 0; i <SIZE; i++) {
#pragma HLS pipeline enable_flush
        const unsigned int reversed_i = reverse(i);
        Bit_R[reversed_i] = X_R[i];
        Bit_I[reversed_i] = X_I[i];
	}
}

/*=======================BEGIN: FFT=========================*/
//stage 1
void fft_stage_first(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
#pragma HLS DATAFLOW
	const int stage = 1;
	const int DFTpts = 1<<stage;
	const int numBF = DFTpts/2;
	const int phase_increment = 1024/DFTpts;
	const int p = 0;
    const DTYPE c = W_real[p];
    const DTYPE s = W_imag[p];
	for (int i = 0; i < SIZE; i += DFTpts) {
#pragma HLS PIPELINE enable_flush
		const int i_lower = i + 1;
		const DTYPE temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
		const DTYPE temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

		OUT_R[i_lower] = X_R[i] - temp_R;
		OUT_I[i_lower] = X_I[i] - temp_I;
		OUT_R[i] = X_R[i] + temp_R;
		OUT_I[i] = X_I[i] + temp_I;
	}
}

//stages
void fft_stages(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
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

//last stage
void fft_stage_last(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
#pragma HLS DATAFLOW
	int stage = 10;
    const int DFTpts = 1<<stage;
    const int numBF = DFTpts/2;
    const int phase_increment = 1024/DFTpts;
    int p = 0;
    for (int i=0; i<SIZE2; ++i) {
#pragma HLS PIPELINE enable_flush
        const DTYPE c = W_real[p];
        const DTYPE s = W_imag[p];
        p = (p + phase_increment)%512;
		const int i_lower = i + numBF;
		const DTYPE temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
		const DTYPE temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

		OUT_R[i_lower] = X_R[i] - temp_R;
		OUT_I[i_lower] = X_I[i] - temp_I;
		OUT_R[i] = X_R[i] + temp_R;
		OUT_I[i] = X_I[i] + temp_I;
    }
}

void qpsk_decoder(const DTYPE X_R[SIZE], const DTYPE X_I[SIZE], unsigned int output_symbols[SIZE])
{
#pragma HLS DATAFLOW
    for (int i = 0; i < SIZE; ++i) {
#pragma HLS PIPELINE enable_flush
        if (X_R[i] > 0) {
        	if (X_I[i] > 0) {
        		output_symbols[i] = 0;
        	} else {
        		output_symbols[i] = 2;
        	}
        } else {
        	if (X_I[i] > 0) {
        		output_symbols[i] = 1;
        	} else {
        		output_symbols[i] = 3;
        	}
        }
    }
}
