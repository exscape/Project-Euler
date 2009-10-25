#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-17 */
/* Had to cheat a tiny bit and look at my old solution :( */

uint32_t d(uint32_t n) {
	uint32_t sum = 0;
	for (uint32_t i = 1; i<=(n/2); i++) {
		if (n % i == 0)
			sum += i;
	}
	return sum;
}

int main() {
	uint32_t sum = 0;
	for (uint32_t a = 1, b; a<10000; a++) {
		b = d(a);
		if (a != b && a == d(b)) {
//			printf("%lu <-> %lu\n", a, b);
			sum += b;
		}
	}

	printf("Answer: %u\n", sum);
	return 0;
}
