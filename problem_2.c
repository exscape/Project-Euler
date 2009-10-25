#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-10-16 */

int main() {
	uint64_t sum = 0, tmp;
	for (int i=1;; i++) {
		tmp = fib(i);
		if (tmp <= 4000000 && tmp % 2 == 0)
			sum += tmp;
		else if (tmp > 4000000)
			break;
	}
	printf("Answer: %lu\n", sum);
	return 0;
}
