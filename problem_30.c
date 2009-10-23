#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c" /* int_pow(base, exp) */

/* Written: 2009-10-19 */

#define POWER 5

int main() {
	uint64_t grand_total = 0;
	uint64_t digitalsum = 0;
	uint64_t num = 0; /* We need a copy of i since we do num /= 10 in each loop */
	uint16_t current_digit = 0;
	for (uint64_t i = 1; i<=(int_pow(9,POWER)*POWER); i++) { /* The highest possible number is 9^5 * 5 */
		digitalsum = 0;

		for (num = i; num > 0; num /= 10) {
			current_digit = num % 10;
			digitalsum += int_pow(current_digit, POWER);
		}

		if (digitalsum == i && digitalsum > 9) { // One-digit numbers aren't sums
			printf("Found %llu\n", digitalsum);
			grand_total += digitalsum;
		}
	}

	printf("Answer: %llu\n", grand_total);
	
	return 0;
}
