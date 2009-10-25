#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-24 */

int main() {
	mpz_t num;
	mpz_init_set_ui(num, 100);
	for (uint64_t i = 2; i <= 99; i++) {
		mpz_mul_ui(num, num, i);
	}

	printf("Answer: %lu", gmp_digital_sum(num));

	mpz_clear(num);
	return 0;
}
