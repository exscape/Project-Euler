#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/* Written: 2009-11-03 */

int main() {
	mpz_t num;
	mpz_init(num);
	mpz_ui_pow_ui(num, 2, 7830457);
	mpz_mul_ui(num, num, 28433);
	mpz_add_ui(num, num, 1);

	unsigned long answer = mpz_fdiv_ui(num, 10000000000); /* get the last 10 digits */
	printf("%lu\n", answer);

	mpz_clear(num);

	return 0;
}
