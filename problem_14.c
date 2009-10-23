#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-17 */

uint32_t chain_len(uint32_t start) {
	uint32_t count = 0;
	for (uint32_t num = start; num != 1; count++) {
		if ((num & 1) == 0)
			num /= 2;
		else
			num = (num*3)+1;
	}
	return count+1; // Add 1 for the last number (1)
}

int main() {
	uint32_t max_num = 0, max_len = 0, curr_len;
	for (uint32_t i=1; i<1000000; i++) {
		curr_len = chain_len(i);
		if (curr_len > max_len) {
			max_len = curr_len;
			max_num = i;
		}
	}

	printf("Answer: %lu (len %lu)\n", max_num, max_len);
	return 0;
}
