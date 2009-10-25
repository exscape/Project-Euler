#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* For stat */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Written: 2009-10-25, some file IO copied from problem 8 */

#define DATAFILE "data/problem_13"

int main() {
	struct stat st;
	if (stat(DATAFILE, &st) != 0) {
		fprintf(stderr, "Unable to stat file (%s)\n", DATAFILE);
		perror("stat");
		exit(1);
	}

	off_t size = st.st_size;
	if (size < 50*100 + 100) { /* 50 digits, 100 numbers, plus newlines */
		exit(1);
	}

	FILE *f = fopen(DATAFILE, "r");
	if (!f) {
		fprintf(stderr, "Unable to read data file (%s)\n", DATAFILE);
		exit(1);
	}

	mpz_t numbers[100];
	char buf[51];
	for (uint8_t i=0; i<100; i++) {
		if (fread(buf, 1, 51, f) != 51) { // read the 50 digits plus the newline
			perror("fread");
			exit(1);
		}
		buf[50] = 0; // overwrite the newline with a NUL
		mpz_init_set_str(numbers[i], buf, 10); // base 10
	}
	fclose(f);
	f = NULL;

	mpz_t sum;
	mpz_init(sum);
	for (uint8_t i=0; i<100; i++) {
		mpz_add(sum, sum, numbers[i]);
	}

	// TODO: A mathematical solution would be preferable.
	char *str;
	gmp_asprintf(&str, "%Zd", sum);
	char *start = substr(str, 0, 10);
	printf("Answer: %s\n", start);

	/* Clean up */
	for (uint8_t i=0; i<100; i++) {
		mpz_clear(numbers[i]);
	}
	mpz_clear(sum);
	free(str);
	free(start);

	return 0;
}
