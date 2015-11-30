
#include <stdio.h>
#include <stdlib.h>
#include "fft.h"
#include "ofdm_test_vector.h"

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE Out_R[SIZE], Out_I[SIZE];

int main()
{
#if 0
	FILE *fp;

	//Generate input data
	for(int i=0; i<SIZE; i++)	{
		In_R[i] = i;
		In_I[i] = 0.0;
		Out_R[i]=i;

		Out_I[i]=1;
	}
	
	//Perform FFT
	fft(In_R, In_I, Out_R, Out_I);

	fp=fopen("out.dat", "w");
	printf("Printing FFT Output (OUT of Place)\n");
	for(int i=0; i<SIZE; i++){
		//printf("%4d\t%f\t%f\n",i,Out_R[i],Out_I[i]);
		fprintf(fp, "%4d\t%f\t%f\n",i,Out_R[i],Out_I[i]);
	}
	fclose(fp);

	//Check against golden output.
	printf ("Comparing against output data \n");
  if (system("diff -w out.dat out.gold.dat")) {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
	fprintf(stdout, "*******************************************\n");
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
  }
#endif
    // Validate ofdm test vector.
    // Input gold_i/q into the fft.
    // Verify the gold symbols match fft output.
    unsigned int symbols[SIZE];
    ofdm(gold_iq, symbols);
    for (int i = 0; i < SIZE; ++i) {
    	printf("%d %d\n", symbols[i], gold_symbols[i]);
    	if (symbols[i] != gold_symbols[i]) {
            printf("symbol error %d %d\n", symbols[i], gold_symbols[i]);
        }
    }
    return 0;
}
