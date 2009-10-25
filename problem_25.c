#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-25 */

int main() {
	for (uint64_t i=1;; i++) {
		mpz_t *f = gmp_fib(i);

		if (gmp_get_length(*f) >= 1000) {
			gmp_printf("Answer: fib(%lu) = %Zd\n", i, *f);
			mpz_clear(*f);
			return 0;
		}
	}

	return 0;
}
