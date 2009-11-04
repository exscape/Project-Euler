#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-11-04 */
/* Beware: ugly code! */

int main() {
	uint16_t answer = 0;
	mpz_t num;
	mpz_init_set_ui(num, 1);

	for (; mpz_cmp_ui(num, 10000) < 0; mpz_add_ui(num, num, 1)) {
		mpz_t n, tmp;
		mpz_init_set(n, num);

		for (int i=0; i<50; i++) {
			char *str;
			gmp_asprintf(&str, "%Zd", n);
			char *rev = reverse(str);
			mpz_init_set_str(tmp, rev, 10);
			mpz_add(n, n, tmp);
			free(rev);
			free(str);
			if (gmp_is_palindrome(n)) 
				goto non;

		}
		// If we exited the for loop, count this as a lychrel number
		answer++;
		non:
		answer = answer; // NOOP to stop warning
	}

	printf("Answer: %hu lychrel numbers < 10000\n", answer);

	mpz_clear(num);

	return 0;
}
