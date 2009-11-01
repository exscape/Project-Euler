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
	uint64_t *p; // A pointer to the first free item in the array (XXX: (arr+used) instead?)
} uint64_list;

//
// XXX: TODO:
// * list_sort(uint64_list **list), using qsort
// * list_find(uint64_list **list, uint64_t n) - linear search? qsort would reorder the array, which
//                                               the caller may not want. return value = index, or -1 if not found.
// * list_copy(list, list) - copy elements up to ->used, or to ->size?
// * ...
//

/*
 * Create a dynamically allocated list of uint64_ts
 * return value: A preallocated list, or NULL if calloc fails.
 */
uint64_list *list_create(void) {
	uint64_list *list = calloc(1, sizeof(*list));
	if (list == NULL)
		return NULL;
	list->used = 0;
	list->size = 1; // XXX: Change to a more sensible value (10?) when memory allocation works
	list->arr = calloc(list->size, sizeof(uint64_t));
	if (list->arr == NULL) {
		return NULL;
	}
	list->p = list->arr;

	return list;
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
 * Compresses the list down to the bare minimum of elements, virtually freeing unused memory
 * list: the list to work with
 * return value: 1 on success, 0 on failure
 */
uint8_t list_compress(uint64_list **list) {
	uint64_t *new_ptr = realloc((*list)->arr, (*list)->used * sizeof(uint64_t));
	if (new_ptr == NULL) {
		list_free(list);
		return 0;
	}
	(*list)->arr = new_ptr;
	(*list)->size = (*list)->used;

	return 1;
}

/*
 * Add a number to a list, allocating more memory if necessary
 * list: the list to work with
 * n: the number to add to the list
 * return value: 1 for success, 0 for failure
 */
uint8_t list_add(uint64_list **list, uint64_t n) {
	printf("Adding element \"%lu\"; stats before: used=%zu, size=%zu ...", n, (*list)->used, (*list)->size);

	if ((*list)->used + 1 > (*list)->size) {
		size_t new_size = (*list)->used + 2; // XXX: Add more than 1; 10, perhaps?
		printf(" so we need to realloc the array to %zu elements\n", new_size);
		size_t p_offset = (*list)->p - (*list)->arr; // Needed to point p correctly in case realloc() moves our data
		uint64_t *new_ptr = realloc((*list)->arr, new_size * sizeof(uint64_t));
		if (new_ptr == NULL) {
			list_free(list);
			return 0;
		}
		(*list)->arr = new_ptr;
		(*list)->size = new_size;
		(*list)->p = (*list)->arr + p_offset;
	}
	else
		printf(" so NO realloc will be necessary\n");

	printf("list = %p to %p, p = %p, adding %lu\n", (void *)(*list)->arr, (void *)((*list)->arr+(*list)->size), (void *)(*list)->p, n);

	*(*list)->p++ = n;
	(*list)->used++;

	printf("Added element \"%lu\"; stats after: used=%zu, size=%zu\n", n, (*list)->used, (*list)->size);

	return 1;
}

// XXX: This needs work - it's hardly obvious that the usage is
// list_foreach_element(list) { do_something_with(list->arr[i]) } ... nor should it be that way!
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
	if (list == NULL) {
		fprintf(stderr, "Failed to get a list of prime factors!\n");
		exit(1);
	}

	list_foreach_element(list) {
		printf("prime factor: %lu\n", list->arr[i]);
	}

	printf("List stats in main(): used=%zu, size=%zu\n", list->used, list->size);

	list_compress(&list);

	printf("List stats in main() post-compress: used=%zu, size=%zu\n", list->used, list->size);

	list_foreach_element(list) {
		printf("prime factor: %lu\n", list->arr[i]);
	}

	// The last element of the array is the largest and thus the answer; XXX: helper function!
	printf("Answer: %lu\n", list->arr[list->used-1]);
	list_free(&list);

	return 0;
}
