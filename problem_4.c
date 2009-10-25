#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17 */

int main() {
	uint32_t max = 0, num;
	for (uint16_t i = 0; i < 1000; i++) {
		for (uint16_t j = 0; j < 1000; j++) {
			num = i*j;
			if (is_palindrome(num)) {
				if (num > max)
					max = num;
			}
		}
	}

	printf("Answer: %u\n", max);

	return 0;
}
