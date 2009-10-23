#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-16 */

int main() {
	uint32_t sum = 0;
	for (int i=3; i<1000; i++) {
		if (i % 3 == 0 || i % 5 == 0)
			sum += i;
	}
	printf("Answer: %u\n", sum);
	return 0;
}
