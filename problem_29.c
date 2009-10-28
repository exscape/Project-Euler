#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>

/* Written: 2009-10-28 */

static int mpz_cmpfunc(const void *in1, const void *in2) {
	mpz_t *m1 = (mpz_t *)in1;
	mpz_t *m2 = (mpz_t *)in2;
	return mpz_cmp(*m1, *m2);
}

// XXX: How do we implement add_to_set()? static variables - which would (??) make it MP-unsafe? Caller handles
// all? Since the memory management must be dynamic, someone has to keep track of the current allocation size.

// Temporary ONLY!
static mpz_t set[10000];
static uint32_t i = 0;

uint8_t in_set(mpz_t n) {
	qsort(set, i, sizeof(mpz_t), mpz_cmpfunc);
	return (bsearch(&n, set, i, sizeof(mpz_t), mpz_cmpfunc) != NULL);
}

void add_to_set(mpz_t n) {
	if (!in_set(n))
		mpz_set(set[i++], n);
}

int main() {
	mpz_t result;
	mpz_init(result);
	for (uint64_t a = 2; a <= 100; a++) {
		for (uint64_t b = 2; b <= 100; b++) {
			mpz_ui_pow_ui(result, a, b);
			add_to_set(result);
		}
	}
	mpz_clear(result);

	printf("Answer: %u\n", i);

	return 0;
}
