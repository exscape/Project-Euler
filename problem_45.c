#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>

/* Written: 2009-10-27 */

int main() {
	for (uint64_t i=286;; i++) {
		uint64_t tri = (i*(i+1))/2;
		if (is_pentagonal(tri) && is_hexagonal(tri)) {
			printf("Answer: tri(%lu) = %lu", i, tri);
			exit(0);
		}
	}

	return 0;
}
