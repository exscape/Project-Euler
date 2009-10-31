#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17? */

#define NUM 600851475143
//#define NUM 13195 /* Correct answer: 29 */

//
// XXX: INCOMPLETE FUNCTION!
//
uint64_t *get_prime_factors(const uint64_t n) {
	if (n < 2) {
		/* handle this edge case early; malloc() due to the fact that the caller
		 * should be able to free() any return value */
		uint64_t *i = malloc(sizeof(uint64_t));
		if (i == NULL)
			return NULL;
		*i = 0;
		return i;
	}

	uint32_t size = 2; /* start off with a fair guess; XXX: raise this to minimize reallocations */
	uint64_t *arr = calloc(size, sizeof(uint64_t));
	if (arr == NULL)
		return NULL;
	uint64_t *ptr = arr;
	uint32_t used_factors = 1; /* count the terminating NUL */
	if (n % 2 == 0) {
		*ptr++ = 2; /* add 2 to the list of prime factors */
		used_factors++;
	}

	uint64_t sqrt_n = (uint64_t)sqrt(n);
    for (uint64_t i=3; i <= sqrt_n; i += 2) {  
        if (n % i== 0 && isprime(i)) { 
			if (used_factors + 1 > size) {
				/* we need more memory to hold this factor */
				uint32_t new_size = size + 2; // XXX: *2!! +2 is testing only! XXX: ALWAYS +2, due to the NULL termination below!!!
//				if (new_size < 10)
//					new_size = 10;
				printf("Reallocating; size = %u, needed = %u; new size = %u\n", size, used_factors + 1, new_size);
				arr = realloc(arr, new_size * sizeof(uint64_t));
				if (arr == NULL)
					return NULL;
				size = new_size;
			}
            used_factors++;

			printf("arr = %p to %p, ptr = %p, adding %lu\n", (void *)arr, (void *)(arr+size), (void *)ptr, i);
			*ptr++ = i; /* add this factor to the array */
        }
    }
	printf("NULL terminating: arr = %p to %p, ptr = %p\n", (void *)arr, (void *)(arr+size), (void *)ptr);
	*ptr++ = 0; /* NULL terminate the array */

	return arr;
}

int main() {
	uint64_t *arr = get_prime_factors(NUM);
	uint64_t i;
	for (i = 0; arr[i] != 0; i++) 
		printf("prime factor: %lu\n", arr[i]);

	// The last element of the array is the largest and thus the answer;
	// -1 is needed due to the above loop setting i to the NULL terminating element.
	printf("Answer: %lu\n", arr[i-1]);

	printf("Move get_divisors to util.c\n");

	free(arr);
	return 0;
}
