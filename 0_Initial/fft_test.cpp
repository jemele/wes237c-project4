/*
This is traditional 2-radix DIT FFT algorithm implementation.
It is based on conventional 3-loop structure. 
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "fft.h"

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE WW_R[SIZE], WW_I[SIZE];

int main()
{
	FILE *fp;

	printf("INPUTS\n");
	for(int i=0; i<SIZE; i++){
		In_R[i] = i;
		In_I[i] = 0.0;
	}
	


	//Perform FFT
	fft(In_R, In_I);
	//Print output
	fp=fopen("out.dat", "w");
	printf("Printing FFT Output\n");
	for(int i=0; i<SIZE; i++){
		printf("%4d\t%f\t%f\n",i,In_R[i],In_I[i]);
		fprintf(fp, "%4d\t%f\t%f\n",i,In_R[i],In_I[i]);
	}
	fclose(fp);

	
	printf ("Comparing against output data \n");
  if (system("diff -w out.dat out.gold.dat")) {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
	fprintf(stdout, "*******************************************\n");
     return 1;
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
     return 0;
  }

}
