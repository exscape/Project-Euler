#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-16 */

#define NUM 100
int main() {
	uint64_t sum_sq = 0, sq_sum = 0;

	for (uint64_t i = 1; i <= NUM; i++) {
		sum_sq += i*i;
	}

	for (uint64_t i = 1; i <= NUM; i++) {
		sq_sum += i;
	}
	sq_sum *= sq_sum;

	printf("Answer: %llu\n", sq_sum-sum_sq);
	return 0;
}
