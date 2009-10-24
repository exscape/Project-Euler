#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>

/* Written: 2009-10-24 */

int main() {
	mpz_t num;
	mpz_init2(num, 1000); /* initialize with 1000 bits */

	// num = int_pow(2,1000)
	mpz_ui_pow_ui(num, 2, 1000);

	uint64_t sum = 0;

//  while (num != 0) 
	while (mpz_cmp_ui(num, 0) != 0) {
//		sum += num % 10;
		sum += mpz_fdiv_ui(num, 10);

//		num /= 10;
		mpz_tdiv_q_ui(num, num, 10);
	}

	printf("Answer: %llu\n", sum);
	return 0;
}
