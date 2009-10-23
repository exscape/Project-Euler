#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>


/*
 *
 *
 *
 *
 *
 * ÖVERBELASTA INTE MED GMP! Ta det lugnt!!!
 *
 *
 *
 *
 *
 */


/* Written: */

uint64_t gmp_digitalsum(mpz_t n) {
	// Orkar inte just nu...
}


int main() {
	mpz_t i;
	mpz_init(i);
	mpz_set_ui(i, 1234);

	uint64_t digsum = gmp_digitalsum(i);
	gmp_printf("number is %Zd, digital sum = %ll (correct answer = 10 for 1234)\n", i, digsum);
	mpz_clear(i);

	return 0;
}
