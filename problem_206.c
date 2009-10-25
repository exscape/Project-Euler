#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "util.c"

/* Written: 2009-10-22, 2009-10-23 */

// Shorthand since it's used a lot of times on the same line
#define gd(num, dig) get_digit(num, dig)

int main() {
register uint64_t n, sq;
	// NOTE: The last TWO digits must be 0 (1_2_3_4_5_6_7_8_900), because no number produces a square that ends with
	// a SINGLE zero; they all end with none, or at least two. (16, 25, 36, ..., 100, 400, 900, 1600, 2500, ..., 10000))
	for (n=((uint64_t)sqrt(1020304050607080900)-1);; n ++) {
		sq = n*n;
		if (sq % 100 != 0) // This is the single change made on 2009-10-23 (I finished the rest just before bed.)
			continue; 	   // It cuts execution time from 1m 48.5s to 10.5s.
		if (gd(sq, 1) == 1 && gd(sq, 3) == 2 && gd(sq, 5) == 3 && gd(sq, 7) == 4 && gd(sq, 9) == 5 && gd(sq, 11) == 6 && gd(sq, 13) == 7 && gd(sq, 15) == 8 && gd(sq, 17) == 9)
		{
			printf("Answer: %lu (square: %lu)\n", n, sq);
			return 0;
		}
	}

	return 0;
}
