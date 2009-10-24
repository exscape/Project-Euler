#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-24(, more?) */

int main() {
	uint64_t i;
#define ia(n1,n2) is_anagram(n1,n2)
	for (i = 1;; i++) {
		if (ia(i, i*2) && ia(i, i*3) && ia(i, i*4) && ia(i, i*5) && ia(i, i*6)) {
			printf("Answer: %llu\n", i);
			break;
		}
	}
	return 0;
}
