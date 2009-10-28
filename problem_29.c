#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>

/* Written: 2009-10-28, XXX */

uint8_t in_set(mpz_t haystack[] , const uint32_t num_elements, const mpz_t needle) {
	for (int32_t i = 0; i < num_elements; i++) {
		if (!mpz_cmp(haystack[i], needle)) {
			comparisons++;
			return 1;
		}
	}
	return 0;
}

/*
static int mpz_cmpfunc(const void *in1, const void *in2) {
	mpz_t *m1 = (mpz_t *)in1;
	mpz_t *m2 = (mpz_t *)in2;
	return mpz_cmp(*m1, *m2);
}
*/

// XXX: How do we implement add_to_set()? static variables - which would (??) make it MP-unsafe? Caller handles
// all? Since the memory management must be dynamic, someone has to keep track of the current allocation size.

// Temporary ONLY!
static mpz_t set[10000];
static size_t i = 0;
static uint32_t comparisons = 0;

void add_to_set(mpz_t n) {
	if (!in_set(set, i, n))
		mpz_set(set[i++], n);
}

#define MAX 100

int main() {
	mpz_t result;
	mpz_init(result);
	for (uint64_t a = 2; a <= MAX; a++) {
		for (uint64_t b = 2; b <= MAX; b++) {
			mpz_ui_pow_ui(result, a, b);
			add_to_set(result);
		}
	}
	mpz_clear(result);

/*
	for (int j=0; j<i; j++) {
		gmp_printf("%Zd\n", set[j]);
	}
*/

	printf("Answer: %zu (%u comparisons)\n", i, comparisons);

	return 0;
}
