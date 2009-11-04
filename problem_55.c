#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-11-04 */
/* Beware: ugly code! The strings are everywhere! */

int main() {
	uint16_t answer = 0;

	for (uint16_t i = 0; i < 10000; i++) {
		mpz_t n, tmp;
		mpz_init_set_ui(n, i);

		for (int i=0; i<50; i++) {
			char *str;
			gmp_asprintf(&str, "%Zd", n);

			char *rev = reverse(str);
			mpz_init_set_str(tmp, rev, 10);
			mpz_add(n, n, tmp);
			mpz_clear(tmp);

			free(rev);
			free(str);

			if (gmp_is_palindrome(n)) 
				goto nonlychrel;

		}
		// If we exited the for loop, count this as a lychrel number
		answer++;
		nonlychrel:
		mpz_clear(n);
	}

	printf("Answer: %hu lychrel numbers < 10000\n", answer);

	return 0;
}
