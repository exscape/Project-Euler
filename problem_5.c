#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-16 */

int main() {
	uint64_t num, i;
	for (num = 20;; num += 20) {
		for (i=19; i>1; i--) {
			if (num % i != 0) {
				break;
			}
		}
		if (i == 1)
			break;
	}

	printf("Answer: %lu\n", num);
	return 0;
}
