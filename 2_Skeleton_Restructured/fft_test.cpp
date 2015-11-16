
#include <stdio.h>
#include <stdlib.h>
#include "fft.h"

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE Out_R[SIZE], Out_I[SIZE];

int main()
{
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
     return 1;
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
     return 0;
  }

}