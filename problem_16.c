#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-24 */

int main() {
	mpz_t num;
	mpz_init2(num, 1000); /* initialize with 1000 bits */

	mpz_ui_pow_ui(num, 2, 1000);

	printf("Answer: %llu\n", gmp_digital_sum(num));
	mpz_clear(num);
	return 0;
}
