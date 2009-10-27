#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <errno.h>

/* Written: 2009-10-17 */

#define DATAFILE "data/problem_8"

int main() {
	FILE *f = fopen(DATAFILE, "r");
	if (!f) {
		fprintf(stderr, "Unable to read data file (%s)\n", DATAFILE);
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	rewind(f);

	char *buf = malloc(size+1);
	if (fread(buf, 1, size, f) != size) {
		fprintf(stderr, "Unable to read file (%s)\n", DATAFILE);
		exit(1);
	}
	fclose(f); f = NULL;

	char *num = malloc(1000); /* 1000 digits, no NUL */
	char *num_p = num;
	for (char *buf_p = buf; *buf_p != '\0'; buf_p++) {
		if (*buf_p >= '0' && *buf_p <= '9')
			*num_p++ = (*buf_p) - 0x30; /* Convert from '1' to (int)1 etc. */
	}

	free(buf); buf = NULL;

	/* Finally, time for business */
	uint16_t max = 0, curr; /* Max possible value = 9^5 which is less than 2^16, so 16 bits is enough */
	for (uint16_t i = 0; i < 1000-4; i++) {
		curr = num[i] * num[i+1] * num[i+2] * num[i+3] * num[i+4];
		if (curr > max)
			max = curr;
	}

	free(num);
	printf("Answer: %hu\n", max);
	return 0;
}
