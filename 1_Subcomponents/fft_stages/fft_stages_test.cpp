/* 
 * Testbench for fft_stages 
 */

#include <stdio.h>
#include <stdlib.h>
#include "fft_stages.h"

//stage 2
DTYPE In_R2[SIZE], In_I2[SIZE];
DTYPE Out_R2[SIZE], Out_I2[SIZE];

//stage 3
DTYPE In_R3[SIZE], In_I3[SIZE];
DTYPE Out_R3[SIZE], Out_I3[SIZE];

//stage 4
DTYPE In_R4[SIZE], In_I4[SIZE];
DTYPE Out_R4[SIZE], Out_I4[SIZE];

//stage 5
DTYPE In_R5[SIZE], In_I5[SIZE];
DTYPE Out_R5[SIZE], Out_I5[SIZE];

//stage 6
DTYPE In_R6[SIZE], In_I6[SIZE];
DTYPE Out_R6[SIZE], Out_I6[SIZE];

//stage 7
DTYPE In_R7[SIZE], In_I7[SIZE];
DTYPE Out_R7[SIZE], Out_I7[SIZE];

//stage 8
DTYPE In_R8[SIZE], In_I8[SIZE];
DTYPE Out_R8[SIZE], Out_I8[SIZE];

//stage 9
DTYPE In_R9[SIZE], In_I9[SIZE];
DTYPE Out_R9[SIZE], Out_I9[SIZE];



int main()
{
	FILE *fp;
	
	//Setup input data
	for(int i=0; i<SIZE; i++){
		//Stage 2
		In_R2[i] = i;
		In_I2[i] = 0.0;
		Out_R2[i] = 0.0;
		Out_I2[i] = 0.0;

		//Stage 3
		In_R3[i] = i;
		In_I3[i] = 0.0;
		Out_R3[i] = 0.0;
		Out_I3[i] = 0.0;

		//Stage 4
		In_R4[i] = i;
		In_I4[i] = 0.0;
		Out_R4[i] = 0.0;
		Out_I4[i] = 0.0;

		//Stage 5
		In_R5[i] = i;
		In_I5[i] = 0.0;
		Out_R5[i] = 0.0;
		Out_I5[i] = 0.0;

		//Stage 6
		In_R6[i] = i;
		In_I6[i] = 0.0;
		Out_R6[i] = 0.0;
		Out_I6[i] = 0.0;

		//Stage 7
		In_R7[i] = i;
		In_I7[i] = 0.0;
		Out_R7[i] = 0.0;
		Out_I7[i] = 0.0;

		//Stage 8
		In_R8[i] = i;
		In_I8[i] = 0.0;
		Out_R8[i] = 0.0;
		Out_I8[i] = 0.0;

		//Stage 9
		In_R9[i] = i;
		In_I9[i] = 0.0;
		Out_R9[i] = 0.0;
		Out_I9[i] = 0.0;

	}

	//Perform FFT

	//Stage 2
	fft_stages(In_R2, In_I2, 2, Out_R2, Out_I2);

	//Print output
	fp=fopen("out2.dat", "w");
	//printf("Printing FFT Output\n");
	for(int i=0; i<SIZE; i++){
		//printf("%4d\t%f\t%f\n",i,Out_R2[i],Out_I2[i]);
		fprintf(fp, "%4d\t%f\t%f\n",i,Out_R2[i],Out_I2[i]);
	}
	fclose(fp);

	//Check against golden output.
	printf ("Comparing against output data (STAGE 2)\n");
  if (system("diff -w out2.dat out2.gold.dat")) {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "STAGE 2 FAIL: Output DOES NOT match the golden output\n");
	fprintf(stdout, "*******************************************\n");
     //return 1;
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "STAGE 2 PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
     //return 0;
  }

  //Stage 3
  	fft_stages(In_R3, In_I3, 3, Out_R3, Out_I3);


  	fp=fopen("out3.dat", "w");
  	for(int i=0; i<SIZE; i++){
  		//printf("%4d\t%f\t%f\n",i,Out_R3[i],Out_I3[i]);
  		fprintf(fp, "%4d\t%f\t%f\n",i,Out_R3[i],Out_I3[i]);
  	}
  	fclose(fp);

  	//Check against golden output.
  	printf ("Comparing against output data (STAGE 3)\n");
    if (system("diff -w out3.dat out3.gold.dat")) {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "STAGE 3 FAIL: Output DOES NOT match the golden output\n");
  	fprintf(stdout, "*******************************************\n");
       //return 1;
    } else {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "STAGE 3 PASS: The output matches the golden output!\n");
  	fprintf(stdout, "*******************************************\n");
       //return 0;
    }

    //Stage 4
    	fft_stages(In_R4, In_I4, 4, Out_R4, Out_I4);
    	fp=fopen("out4.dat", "w");
    	for(int i=0; i<SIZE; i++){
    		fprintf(fp, "%4d\t%f\t%f\n",i,Out_R4[i],Out_I4[i]);
    	}
    	fclose(fp);

    	//Check against golden output.
    	printf ("Comparing against output data (STAGE 4)\n");
      if (system("diff -w out4.dat out4.gold.dat")) {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "STAGE 4 FAIL: Output DOES NOT match the golden output\n");
    	fprintf(stdout, "*******************************************\n");

      } else {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "STAGE 4 PASS: The output matches the golden output!\n");
    	fprintf(stdout, "*******************************************\n");

      }

      //Stage 5
      	fft_stages(In_R5, In_I5, 5, Out_R5, Out_I5);
      	fp=fopen("out5.dat", "w");
      	for(int i=0; i<SIZE; i++){
      		fprintf(fp, "%5d\t%f\t%f\n",i,Out_R5[i],Out_I5[i]);
      	}
      	fclose(fp);

      	//Check against golden output.
      	printf ("Comparing against output data (STAGE 5)\n");
        if (system("diff -w out5.dat out5.gold.dat")) {
      	fprintf(stdout, "*******************************************\n");
      	fprintf(stdout, "STAGE 5 FAIL: Output DOES NOT match the golden output\n");
      	fprintf(stdout, "*******************************************\n");

        } else {
      	fprintf(stdout, "*******************************************\n");
      	fprintf(stdout, "STAGE 5 PASS: The output matches the golden output!\n");
      	fprintf(stdout, "*******************************************\n");

        }

        //Stage 6
        	fft_stages(In_R6, In_I6, 6, Out_R6, Out_I6);
        	fp=fopen("out6.dat", "w");
        	for(int i=0; i<SIZE; i++){
        		fprintf(fp, "%6d\t%f\t%f\n",i,Out_R6[i],Out_I6[i]);
        	}
        	fclose(fp);

        	//Check against golden output.
        	printf ("Comparing against output data (STAGE 6)\n");
          if (system("diff -w out6.dat out6.gold.dat")) {
        	fprintf(stdout, "*******************************************\n");
        	fprintf(stdout, "STAGE 6 FAIL: Output DOES NOT match the golden output\n");
        	fprintf(stdout, "*******************************************\n");

          } else {
        	fprintf(stdout, "*******************************************\n");
        	fprintf(stdout, "STAGE 6 PASS: The output matches the golden output!\n");
        	fprintf(stdout, "*******************************************\n");

          }

          //Stage 7
          	fft_stages(In_R7, In_I7, 7, Out_R7, Out_I7);
          	fp=fopen("out7.dat", "w");
          	for(int i=0; i<SIZE; i++){
          		fprintf(fp, "%7d\t%f\t%f\n",i,Out_R7[i],Out_I7[i]);
          	}
          	fclose(fp);

          	//Check against golden output.
          	printf ("Comparing against output data (STAGE 7)\n");
            if (system("diff -w out7.dat out7.gold.dat")) {
          	fprintf(stdout, "*******************************************\n");
          	fprintf(stdout, "STAGE 7 FAIL: Output DOES NOT match the golden output\n");
          	fprintf(stdout, "*******************************************\n");

            } else {
          	fprintf(stdout, "*******************************************\n");
          	fprintf(stdout, "STAGE 7 PASS: The output matches the golden output!\n");
          	fprintf(stdout, "*******************************************\n");

            }

            //Stage 8
            	fft_stages(In_R8, In_I8, 8, Out_R8, Out_I8);
            	fp=fopen("out8.dat", "w");
            	for(int i=0; i<SIZE; i++){
            		fprintf(fp, "%8d\t%f\t%f\n",i,Out_R8[i],Out_I8[i]);
            	}
            	fclose(fp);

            	//Check against golden output.
            	printf ("Comparing against output data (STAGE 8)\n");
              if (system("diff -w out8.dat out8.gold.dat")) {
            	fprintf(stdout, "*******************************************\n");
            	fprintf(stdout, "STAGE 8 FAIL: Output DOES NOT match the golden output\n");
            	fprintf(stdout, "*******************************************\n");

              } else {
            	fprintf(stdout, "*******************************************\n");
            	fprintf(stdout, "STAGE 8 PASS: The output matches the golden output!\n");
            	fprintf(stdout, "*******************************************\n");

              }
              //Stage 9
              	fft_stages(In_R9, In_I9, 9, Out_R9, Out_I9);
              	fp=fopen("out9.dat", "w");
              	for(int i=0; i<SIZE; i++){
              		fprintf(fp, "%9d\t%f\t%f\n",i,Out_R9[i],Out_I9[i]);
              	}
              	fclose(fp);

              	//Check against golden output.
              	printf ("Comparing against output data (STAGE 9) \n");
                if (system("diff -w out9.dat out9.gold.dat")) {
              	fprintf(stdout, "*******************************************\n");
              	fprintf(stdout, "STAGE 9 FAIL: Output DOES NOT match the golden output\n");
              	fprintf(stdout, "*******************************************\n");
                return 1;
                } else {
              	fprintf(stdout, "*******************************************\n");
              	fprintf(stdout, "STAGE 9 PASS: The output matches the golden output!\n");
              	fprintf(stdout, "*******************************************\n");
                return 0;
                }
}
