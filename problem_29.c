#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include <string.h>

/* Written: 2009-10-28 (working solution), 2009-10-29 (extra work on gmp_int_set) */

//
// XXX: TODO: Split the set functions into a "library"; add removal of elements(?), and possibly also memory
// deallocation when removing enough elements.
//

/* Holds a set (an array of unique elements) of mpz_t variables */
typedef struct {
	mpz_t *arr; // The data storage itself
	size_t size; // The currently allocated size (in elements)
	size_t num_elements; // The number of elements used
} gmp_int_set;

/* 
 * Initialize a set (i.e. allocate memory and set variables)
 * set: the set to initialize
 * size: the number of elements to initally allocate memory for (will be resized as needed)
 */
void gmp_int_set_alloc(gmp_int_set *set, size_t size) {
	set->arr = malloc(size * sizeof(mpz_t));
	set->size = size;
	set->num_elements = 0;
}

/*
 * Free the allocated memory for a set
 * set: the set to free
 * return value: none
 */
void gmp_int_set_free(gmp_int_set *set) {
	for (size_t i = 0; i < set->num_elements; i++)
		mpz_clear(set->arr[i]);
	free(set->arr);
	free(set);
}

static int mpz_cmpfunc(const void *in1, const void *in2) {
        mpz_t *m1 = (mpz_t *)in1;
        mpz_t *m2 = (mpz_t *)in2;
        return mpz_cmp(*m1, *m2);
}

/*
 * Check whether a number is in the set or not.
 * haystack: the set to look in
 * needle: the GMP integer to look for
 * return value: 1 if found, 0 otherwise
 * XXX: The performance is HORRIBLE - the runtime is reduced from 183ms to 1ms with a return 0; at the start here!
 */
uint8_t in_set(const gmp_int_set *haystack, const mpz_t needle) {
//	qsort(haystack->arr, haystack->num_elements, sizeof(mpz_t), mpz_cmpfunc);
//	XXX: qsort + bsearch won't work, it's much too slow to sort the set this way. Linear search is 40 times faster.
	for (size_t i = 0; i < haystack->num_elements; i++) {
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
//		printf("num_elements = %zu, size = %zu\n", set->num_elements, set->size);
	if (!in_set(set, n)) {
		/* make sure that we don't step over our boundaries */
		if (set->num_elements + 1 > set->size) { // XXX: Does + 1 work now that set_elements isn't incremented prematurely? Seems so.
			size_t new_size = set->size * 2;
			if (new_size < 10)
				new_size = 10;
			set->arr = realloc(set->arr, new_size * sizeof(mpz_t));
			set->size = new_size;
			if (set->arr == NULL) {
				fprintf(stderr, "Failed to add to set: realloc() failed\n");
				exit(1);
			}
		}
		mpz_init(set->arr[set->num_elements]);
		mpz_set(set->arr[set->num_elements], n);
		set->num_elements++;
	}
}

/* inline */ size_t set_length(gmp_int_set *set) {
	return set->num_elements;
} 

int main() {
	gmp_int_set *set = malloc(sizeof(*set));
	gmp_int_set_alloc(set, 0); /* initial storage for 200 numbers, which is less than enough, to test realloc */

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
