#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include <string.h>

/* Written: 2009-10-28 */

//
// XXX: TODO: Split the set functions into a "library"; add removal of elements, and possibly also memory
// deallocation when removing enough elements.
//

/* Holds a set (an array of unique elements) of mpz_t variables */
typedef struct {
	mpz_t *arr; // The data storage itself
	size_t size; // The currently allocated size (in elements)
	size_t num_elements; // The number of elements used
} gmp_int_set;

/* 
 * Initialize a set (i.e. allocate memory and set variables)/
 * set: the set to initialize
 * size: the number of elements to initally allocate memory for (will be resized as needed)
 */
void gmp_int_set_alloc(gmp_int_set *set, size_t size) {
	set->arr = malloc(size * sizeof(mpz_t));
	set->size = size;
	set->num_elements = 0;
}

void gmp_int_set_free(gmp_int_set *set) {
	for (size_t i = 0; i < set->num_elements; i++)
		mpz_clear(set->arr[i]);
	free(set->arr);
	free(set);
}

/*
 * Check whether a number is in the set or not.
 * haystack: the set to look in
 * needle: the GMP integer to look for
 * return value: 1 if found, 0 otherwise
 * XXX: Linear search in unsorted set, better than sorting and using a binary search, or not?
 */
uint8_t in_set(const gmp_int_set *haystack, const mpz_t needle) {
	for (int32_t i = 0; i < haystack->num_elements; i++) {
		if (!mpz_cmp(haystack->arr[i], needle)) {
			return 1;
		}
	}
	return 0;
}

/*
 * set: the set to work with
 * n: the number to add to the set; duplicates will not be added, or it wouldn't be a set!
 */
void add_to_set(gmp_int_set *set, mpz_t n) {
	if (!in_set(set, n)) {
		/* make sure that we don't step over our boundaries */
		if (set->num_elements + 1 > set->size) {
			set->arr = realloc(set->arr, 2 * set->size * sizeof(mpz_t)); // XXX: 2* ?
			set->size *= 2;
			if (set->arr == NULL) {
				fprintf(stderr, "Failed to add to set: realloc() failed\n");
				exit(1);
			}
		}
		mpz_set(set->arr[set->num_elements++], n);
	}
}

/*
inline size_t set_length(gmp_int_set *set) {
	return set->num_elements;
} 
*/
// for GDB...
#define set_length(set) ((set->num_elements))

int main() {
	gmp_int_set *set = malloc(sizeof(*set));
	gmp_int_set_alloc(set, 200); /* initial storage for 200 numbers, which is less than enough, to test realloc */

	mpz_t result;
	mpz_init(result);

#define MAX 100 /* 2 <= a <= MAX, same for b */
	for (uint64_t a = 2; a <= MAX; a++) {
		for (uint64_t b = 2; b <= MAX; b++) {
			mpz_ui_pow_ui(result, a, b); /* result = a^b */
			add_to_set(set, result);
		}
	}

	printf("Answer: %zu\n", set_length(set));

	mpz_clear(result);
	gmp_int_set_free(set);

	return 0;
}
