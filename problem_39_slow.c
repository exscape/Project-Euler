#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Written: 2009-10-17+(?) */
// FIXME: Date + SPEED (3 minutes on a 3 GHz Core 2)

int main() {
	uint16_t max_count = 0, max_p = 0;
	printf("This takes a while (about 1m 30s on a 3 GHz Core 2).\n");

	for (uint16_t p = 1; p <= 1000; p++) {
		uint16_t count = 0;
		uint16_t i = p;
		for (uint16_t a = 1; a<i; a++) {
			for (uint16_t b = 1; b<i; b++) {
				for (uint16_t c = 1; c<i/2; c++) { /* After hints, a^2+b^2==c^2 so a+b > c, therefore c < 500 */
					if (a+b+c == i && (a*a + b*b) == c*c) {
//						printf("{%hu,%hu,%hu} = %hu\n", a, b, c, i);
						count++;
					}
				}
			}
		}
		if (count > max_count) {
			max_count = count;
			max_p = p;
		}
	}

	printf("Answer: %hu solutions for p = %hu\n", max_count, max_p);

	return 0;
}
