#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-16 */

#define NUM 10001

int main() {
	uint16_t num = 1; // 2 is a prime which the for loop doesn't cover
	uint64_t i;
	for (i = 3;; i += 2) {
		if (isprime(i))
			num++;
		if (num == NUM)
			break;
	}

	printf("Answer: %llu\n", i);
	return 0;
}
