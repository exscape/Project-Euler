#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <errno.h>

/* For stat */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/* Written: 2009-10-17 */

#define DATAFILE "data/problem_8"

int main() {
	struct stat st;
	if (stat(DATAFILE, &st) != 0) {
		fprintf(stderr, "Unable to stat file (%s)\n", DATAFILE);
		perror("stat");
		exit(1);
	}

	off_t size = st.st_size;
	if (size < 50*20+20) { /* 50 chars, 20 lines, plus newlines */
		exit(1);
	}

	FILE *f = fopen(DATAFILE, "r");
	if (!f) {
		fprintf(stderr, "Unable to read data file (%s)\n", DATAFILE);
		exit(1);
	}

	char *buf = malloc(size+1);
	if (fread(buf, 1, size, f) != size) {
		fprintf(stderr, "Unable to read file (%s)\n", DATAFILE);
		exit(1);
	}
	fclose(f); f = NULL;

	char *num = malloc(1000 + 1); /* 1000 digits + 1 NUL */
	char *num_p = num;
	for (char *buf_p = buf; *buf_p != '\0'; buf_p++) {
		if (*buf_p >= '0' && *buf_p <= '9')
			*num_p++ = (*buf_p) - 0x30; /* Convert from '1' to (int)1 etc. */
	}
	num[1000] = '\0';

	free(buf); buf = NULL;

	/* Finally, time for business */
	uint16_t max = 0, curr; /* Max possible value = 9^5 which is less than 2^16, so 16 bits is enough */
	for (uint16_t i = 0; i <= 1000-4; i++) { /* OBOE? */
		curr = num[i] * num[i+1] * num[i+2] * num[i+3] * num[i+4];
		if (curr > max)
			max = curr;
	}

	free(num);
	printf("Answer: %hu\n", max);
	return 0;
}
