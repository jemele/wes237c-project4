/*
The bit_reverse part of FFT.
INPUT:
	In[]:

OUTPUT:
	Out[]:
*/

#include "bit_reverse.h"
#include <stdio.h>


// Reverse the bits of the input, assuming a 10-bit input.
static unsigned int reverse(register unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return ((x >> 16) | (x << 16)) >> ((sizeof(x)*8) - M);
}

// XXX describe this function, please
void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE Bit_R[SIZE], DTYPE Bit_I[SIZE]){
	for (unsigned int i = 0; i <SIZE; i++) {
        const unsigned int reversed_i = reverse(i);
        Bit_R[reversed_i] = X_R[i];
        Bit_I[reversed_i] = X_I[i];
	}
}
