#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17? */

//
// COMPLETELY UNACCEPTABLE: 31 minutes on a 3 GHz Core 2
//

#define NUM 600851475143
//#define NUM 13195 /* Correct answer: 29 */

//
// INCOMPLETE FUNCTION!
//
uint64_t *get_prime_factors(uint64_t n) {
	uint32_t size = 10000; /* start off with a fair guess; XXX: make this ~10, fix realloc */
//	uint32_t old_size = size; /* might be needed later */
	uint64_t *arr = malloc(size * sizeof(uint64_t));
	uint64_t *ptr = arr;
	if (arr == NULL)
		return NULL;
	memset(arr, 0, size * sizeof(uint64_t));

	if (n < 2)
		return arr; /* No prime factors */
	if (n % 2 == 0)
		*ptr++ = 2;
   uint64_t used_factors = 1; // 2, so far

/*    uint64_t sqrt_n = (uint64_t)sqrt(n); */

    for (uint64_t i=3; i <= (n/2)+3; i+=2) {  
        if (n % i== 0 && isprime(i)) { 
            used_factors++;
			*ptr++ = i;
            // if (n/i != sqrt_n) {
				// factors++;
			// }
        }
/*		if (i % 10000001 == 0) 
			printf("%.3f%%\n", ((float)i/(n/2))*100);
*/
    }

	return arr;
}

int main() {
	uint64_t *arr = get_prime_factors(NUM);;
	for (uint64_t i = 0; arr[i] != 0; i++) {
		printf("Prime factor: %llu\n", arr[i]);
	}

	printf("Move get_divisors to util.c\n");
	return 0;
}
