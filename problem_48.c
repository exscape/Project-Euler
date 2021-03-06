#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-24, 2009-10-25 (substr / modulo part, substr part) */

int main() {
	mpz_t n, sum;

	// Init with 10k bits, to reduce reallocations
	mpz_init2(n, 10000);
	mpz_init2(sum, 10000);

	for (uint64_t i=1; i <= 1000; i++) {
		mpz_ui_pow_ui(n, i, i);
		mpz_add(sum, sum, n);
	}

	gmp_printf("Answer: %lu\n", mpz_fdiv_ui(sum, int_pow(10, 10)));

	/* Alternate, less mathy way */
	char *str;
	gmp_asprintf(&str, "%Zd", sum);
	char *answer = substr(str, -10, 0);
	printf("Answer: %s\n", answer);
	free(answer);
	free(str);

	mpz_clear(sum);
	mpz_clear(n);

	return 0;
}
