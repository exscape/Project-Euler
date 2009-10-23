#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-16 */

//#define NUM 10
#define NUM 2000000

int main() {
	uint64_t sum = 2;
	for (uint32_t i = 3; i < NUM; i += 2) {
		if (isprime(i))
			sum += i;
	}

	printf("Answer: %llu\n", sum);
	return 0;
}
