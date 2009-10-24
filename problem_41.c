#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-24 */

int main() {
// NOTE: Unfortunately, I didn't figure the starting number out myself;
// I used 987654321 (which takes A LOT longer, about 4.5 minutes).
// Apparently, if the digital sum of a number is divisible by 3, the number isn't prime.
#define START 7654321
	for (uint32_t i = START; i > 0 && i <= START; i-=2) { /* detect underflow w/ i <= START */
		if (is_pandigital(i) && isprime(i)) {
			printf("Answer: %llu\n", i);
			break;
		}
	}
	return 0;
}
