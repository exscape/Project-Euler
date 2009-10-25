#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c" /* bin(), is_palindrome{,_str} */

/* Written: 2009-10-19 */

int main() {
	uint64_t sum = 0;
	char *b = NULL; // pointer to the string containing the binary number
	for (uint32_t i = 0; i<1000000; i++) {
		if (is_palindrome(i)) {
			b = bin(i);
			if (b == NULL) {
				fprintf(stderr, "Unable to run bin(): most likely a malloc error\n");
				exit(1);
			}

			if (is_palindrome_str(b)) {
				sum += i;
			}

			free(b);
		}
	}

	printf("Answer: %lu\n", sum);
	return 0;
}
