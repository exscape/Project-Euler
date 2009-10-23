#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-16, using num_divisors written around 2004-12-28 with slight modifications */

int main() {
	uint64_t n = 0;
	for (uint64_t i=1;; i++) {
		n += i;
		if (num_divisors(n) > 500) {
			printf("Answer: %llu\n", n);
			return 0;
		}
	}

}
