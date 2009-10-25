#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-25 */

int main() {
	mpz_t *f;
	for (uint64_t i=1;; i++) {
		f = gmp_fib(i);

		char *str;
		gmp_asprintf(&str, "%Zd", *f);
		if (strlen(str) >= 1000) {
			gmp_printf("Answer: fib(%lu) = %Zd\n", i, *f);
			break;
		}
		mpz_clear(*f);
	}

	mpz_clear(*f);
	return 0;
}
