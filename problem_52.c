#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-24 (includes is_anagram()) */

#define ia(n1,n2) is_anagram(n1,n2)

int main() {
	for (uint64_t i = 1;; i++) {
		if (ia(i, i*2) && ia(i, i*3) && ia(i, i*4) && ia(i, i*5) && ia(i, i*6)) {
			printf("Answer: %lu\n", i);
			break;
		}
	}
	return 0;
}
