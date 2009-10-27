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
	/*
	 * Here's how you can argue to find the upper bound.
	 * 1) Suppose x has n digits. Then 10^{n-1} <= x < 10^n.
	 * 2) If x is the sum of the factorials of its digits, x <= n*9!
	 *
	 * Thus, we must have 10^{n-1} <= n*9!. The left hand side grows exponentially with n, 
	 * whereas the right hand side grows linearly. When n=1, the exponential is lower than the line. 
	 * A little trial and error shows that for n=7, the exponential is still lower than the line.
	 * However, for n=8, the exponential has crossed above the line, and for greater n will stay above.
	 * Thus, the only possible x are those with 7 or fewer digits.
	 *
	 * The maximal possible sum of factorials of a 7 digit number is 7*9! = 2540160.
	 * Thus, no number larger than this can be expressed as the sum of factorials of its digits.
	 * - mtl2002 @ Project Euler
	 */
	for (uint64_t i = 3; i <= 7*fac[9]; i++) {
		sum = 0;
		for (n = i; n != 0; n /= 10) {
			sum += fac[n % 10];
		}

		if (sum == i && sum > 2) {
			grand_sum += sum;
		}
	}

	printf("Answer: %lu\n", grand_sum);
	return 0;
}
