#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17? */

#define NUM 600851475143
//#define NUM 26
//#define NUM 13195 /* Correct answer: 29 */


typedef struct {
	size_t length;
	uint64_t *arr;
} uint64_list;

//
// XXX: INCOMPLETE FUNCTION!
// XXX: Perhaps even a whole array_*/list_* set of functions, with automatic memory management?
//
uint64_t *get_prime_factors(const uint64_t orig_n) {
//	uint64list *list = calloc(1, sizeof(*list));
	if (orig_n < 2) {
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
	// XXX: To sieve or not to sieve? Might be too slow since we need to create a list of primes,
	// might be faster since we don't need to check every 2nd number here.
/*
def factorize(orig_n):
	factors = [] # done
	n = orig_n # done
	i = 2 # done
	sq_i = i*i # done
	while sq_i <= n: # done
		while n % i == 0:
			n /= i
			factors.append(i)
		sq_i += 2 * i + 1
		i += 1
	if (n != 1) and (n != orig_n):
		factors.append(n)
	
	return factors
*/
	uint64_t n = orig_n;
	uint64_t i = 2;
	uint64_t sq_i = i*i;
    for (; sq_i <= n; i += 1) {  
		while (n % i == 0) {
			n /= i;
			if (used_factors + 2 > size) { // XXX: +2 needed for NULL, or is that an OBOE?
				/* we need more memory to hold this factor */
				uint32_t new_size = size * 5; // XXX: +2 is testing only! XXX: ALWAYS +2 or more, due to the NULL termination below!!! *2 is a bad idea - it's too much. +10?
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
		sq_i += 2 * i + 1; // ?? XXX: memory bounds checking
    }
	if (n != 1 && n != orig_n)
		*ptr++ = n; // XXX: bounds checking
	printf("NULL terminating: arr = %p to %p, ptr = %p\n", (void *)arr, (void *)(arr+size), (void *)ptr);
	*ptr++ = 0; /* NULL terminate the array XXX: bounds checking */

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
