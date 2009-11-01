#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-11-01 */

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
	uint64_t answer = 0;
	for (uint64_t i = 1; i < 1000000; i++) {
		uint64_t n = i;
		uint64_list *list = list_create(60);
		while (list_find(&list, n) == -1) {
			list_add(&list, n);
			uint64_t tmp;
			for (tmp = n; tmp != 0; tmp /= 10) {
				if (tmp == n) // reset n in the first loop, to not use another temporary variable
					n = 0;
				n += fac[tmp % 10];
			}
		}
		if (list_length(&list) == 60)
			answer++;
		list_free(&list);
	}

	printf("Answer: %lu\n", answer);

	return 0;
}
