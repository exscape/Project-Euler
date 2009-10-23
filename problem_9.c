#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-16 */

int main() {
	uint32_t a, b, c;
	for (a=1; a<1000; a++) {
		for (b=a; b<1000; b++) {
//			for (c=b; c<1000; c++) { /* NOTE: Despite the nested loops, this runs in FAR less than 1 second. */
			c = 1000-a-b; /* Copied from an old solution */
				if (a+b+c == 1000 && (a*a + b*b) == c*c) {
					printf("Answer: %lu\n", a*b*c);
					return 0;
				}
//			}
		}
	}
}
