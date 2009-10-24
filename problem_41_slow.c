#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

/* Written: 2009-10-24(, ?) */

int main() {
	for (uint32_t i = 987654321; i != 0; i-=2) { // XXX: can we do more than i -= 2 here?
		if (is_pandigital(i) && isprime(i)) {
			printf("Answer: %llu\n", i);
			break;
		}
	}
	return 0;
}
