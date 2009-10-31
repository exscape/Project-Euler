#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17, + a lot of more days spent working on various memory allocation/dynamic array stuff for util.c */

#define NUM 600851475143
//#define NUM 26
//#define NUM 13195 /* Correct answer: 29 */

typedef struct {
	size_t used; // The number of elements used
	size_t size; // The size of the array in elements
	uint64_t *arr; // The storage array itself
	uint64_t *p; // A pointer to the current item in the array (XXX: (arr+used) instead?)
} uint64_list;

/*
 * Create a dynamically allocated list of uint64_ts
 * return value: A preallocated list, or NULL if calloc fails.
 */
uint64_list *list_create(void) {
	uint64_list *list = calloc(1, sizeof(*list));
	if (list == NULL)
		return NULL;
	list->used = 0;
	list->size = 200; // XXX: FIXME when memory management is working
	list->arr = calloc(list->size, sizeof(uint64_t));
	if (list->arr == NULL) {
		return NULL;
	}
	list->p = list->arr;

	return list;
}

/*
 * Compresses the list down to the bare minimum of elements, virtually freeing unused memory
 * list: the list to work with
 * return value: 1 on success, 0 on failure
 */
uint8_t list_compress(uint64_list **list) {
	*list = realloc(*list, (*list)->used * sizeof(uint64_t));
	if (*list == NULL)
		return 0;
	else
		return 1;
}

/*
 * Free a list.
 * list: The list to free; the pointer will also be set to NULL
 * return value: none
 */
void list_free(uint64_list **list) {
	free((*list)->arr);
	free(*list);
	*list = NULL;
}

/*
 * Add a number to a list, allocating more memory if necessary
 * list: the list to work with
 * n: the number to add to the list
 * return value: none
 */
void list_add(uint64_list **list, uint64_t n) {
	// XXX: memory management!!
	*(*list)->p++ = n;
	(*list)->used++;

	/*
		if (used_factors + 2 > size) { // XXX: +2 needed for NULL, or is that an OBOE?
			// we need more memory to hold this factor
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
		*ptr++ = i; // add this factor to the array
	*/
}

// XXX: This needs work - it's hardly obvious that the usage is
// list_foreach_element(list) { do_something_with(list->arr[i]) } ...
#define list_foreach_element(list) \
	for (size_t i = 0; i < (list)->used; i++)

/*
 * Returns a list of (non-unique) prime factors, i.e. {2, 2, 2, 5} if the input number is 40
 * orig_n: The number to calculate the factors for.
 * return value: A preallocated list containing all the prime factors. The caller is resonsible for freeing this.
 */
uint64_list *get_prime_factors(const uint64_t orig_n) {
	uint64_list *list = list_create();
	if (list == NULL)
		return NULL;
	if (orig_n < 2) {
		return list;
	}

	uint64_t n = orig_n;
	uint64_t i = 2;
	uint64_t sq_i = i*i;
	for (; sq_i <= n; i++) {  
		while (n % i == 0) {
			list_add(&list, i);
			n /= i;
		}
		sq_i += 2 * i + 1; // XXX: Why does this work?
	}
	if (n != 1 && n != orig_n)
		list_add(&list, n); // XXX: Or this?

	return list;
}

int main() {
	uint64_list *list = get_prime_factors(NUM);
	list_foreach_element(list) {
		printf("prime factor: %lu\n", list->arr[i]);
	}
	
	list_compress(&list);

	// The last element of the array is the largest and thus the answer; XXX: helper function!
	printf("Answer: %lu\n", list->arr[list->used-1]);

	printf("Move get_divisors to util.c\n");

	list_free(&list);

	return 0;
}
