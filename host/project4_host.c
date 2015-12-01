#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "ofdm_test_vector.h"

int main(int argc, char **argv)
{
    // open all needed files, validate later
    int fdr = open("/dev/xillybus_read_32", O_RDONLY);
    int fdw = open("/dev/xillybus_write_32", O_WRONLY);

    // validate open succeeded
    if ((fdr == -1) || (fdw == -1)) { 
        fprintf(stderr, "open %d\n", errno);
        return errno;
    }
    
    // write iq samples and read the resulting symbols
    unsigned int out[sizeof(gold_symbols)/sizeof(*gold_symbols)];
    write(fdw, gold_iq, sizeof(gold_iq));
    read(fdr, out, sizeof(out));

    // close xillybus devices
    close(fdr); fdr = -1;
    close(fdw); fdw = -1;

    // for plot's sake, write i/q and output
    FILE *ifile = fopen("input_i.txt", "w");
    FILE *qfile = fopen("input_q.txt", "w");
    FILE *ofile = fopen("output.txt" , "w");
    if (!ifile || !qfile || !ofile) {
        fprintf(stderr, "open %d\n", errno);
        return errno;
    }
    int i;
    for (i = 0; i < sizeof(out)/sizeof(*out); ++i) {
        fprintf(ifile, "%f,", gold_i[i]);
        fprintf(qfile, "%f,", gold_q[i]);
        fprintf(ofile, "%d,", out[i]);
    }
    fclose(ifile); ifile = 0;
    fclose(qfile); qfile = 0;
    fclose(ofile); ofile = 0;

    // validate output
    int errors = 0;
    for (i = 0; i < sizeof(out)/sizeof(*out); ++i) {
        printf("%d %d %d\n", i, out[i], gold_symbols[i]);
        if (out[i] != gold_symbols[i]) {
            fprintf(stderr, "symbol error\n");
            ++errors;
        }
    }

    // return the number of errors
    return errors;
}
