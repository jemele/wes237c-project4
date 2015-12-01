#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "ofdm_test_vector.h"

int main(int argc, char **argv)
{
    int fdr, fdw;
	unsigned int out[sizeof(gold_symbols)/sizeof(*gold_symbols)];

    // open the xillybus read/write devices
	fdr = open("/dev/xillybus_read_32", O_RDONLY);
	fdw = open("/dev/xillybus_write_32", O_WRONLY);
	if ((fdr == -1) || (fdw == -1)) {
        fprintf(stderr, "open %d\n", errno);
        return errno;
	}

    // write iq samples and read the resulting symbols
    write(fdw, gold_iq, sizeof(gold_iq));
    read(fdr, out, sizeof(out));

    // close xillybus devices
	close(fdr);
    fdr = -1;
	close(fdw);
    fdw = -1;

    // validate output
    int i;
    for (i = 0; i < sizeof(out)/sizeof(*out); ++i) {
        printf("%d %d\n", i, out[i]);
    }

    // and all is well
	return 0;
}
