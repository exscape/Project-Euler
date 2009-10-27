#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-27 */

uint32_t fac[] = {
	1,
	1,
	2,
	2*3,
	2*3*4,
	2*3*4*5,
	2*3*4*5*6,
	2*3*4*5*6*7,
	2*3*4*5*6*7*8,
	2*3*4*5*6*7*8*9
};

int main() {
	uint64_t grand_sum = 0, sum = 0;
	uint64_t n;
	for (uint64_t i = 3; i < 10000000; i++) { // XXX: Learn about the reason for this upper bound
		sum = 0;
		n = i;
		while (n != 0) {
			sum += fac[n % 10];
			n /= 10;
		}

		if (sum > 2 && sum == i) {
			grand_sum += sum;
		}
	}

	printf("Answer: %lu\n", grand_sum);
	return 0;
}
