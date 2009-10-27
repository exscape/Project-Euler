#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-27, XXX */

uint32_t fac[] = {
	0,
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
	for (uint64_t i = 3;; i++) {
		sum = 0;
		for (uint8_t j = 1; j <= get_length(i); j++) {
			sum += fac[get_digit(i, j)];
		}
		if (sum > 2 && sum == i) {
			grand_sum += sum;
			printf("Found %lu, grand sum = %lu\n", sum, grand_sum);
		}
	if (i % 1000000 == 0)
		printf("i = %lu\n", i);
	}
	return 0;
}
