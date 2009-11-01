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
// * list_copy(list, list) - copy elements up to ->used, or to ->size?
// * ...
//

/*
 * Returns the index of the (first) value "n" in the list
 * list: the list to search
 * n: the item to search for
 * return value: the index of the item, or -1 if nothing it found.
 */
int64_t list_find(uint64_list **list, uint64_t n) {
	for (size_t i = 0; i < (*list)->used; i++) {
		if ((*list)->arr[i] == n)
			return i;
	}
	return -1;
}

/* 
 * Helper functions for the list_sort* functions
 */

int list_cmpfunc(const void *i1, const void *i2) {
	uint64_t *n1 = (uint64_t *)i1;
	uint64_t *n2 = (uint64_t *)i2;
	if (*n1 < *n2)
		return -1;
	else if (*n1 > *n2)
		return 1;
	else
		return 0;
}

int list_cmpfunc_reverse(const void *i1, const void *i2) {
	uint64_t *n1 = (uint64_t *)i1;
	uint64_t *n2 = (uint64_t *)i2;
	if (*n1 < *n2)
		return 1;
	else if (*n1 > *n2)
		return -1;
	else
		return 0;
}

/*
 * Sorts the given list in numerical order
 * list: the list to be sorted (in-place)
 * return value: none
 */
void list_sort(uint64_list **list) {
	qsort((*list)->arr, (*list)->used, sizeof(uint64_t), list_cmpfunc);
}

/*
 * Sorts the given list in reverse numerical order
 * list: the list to be sorted (in-place)
 * return value: none
 */
void list_sort_reverse(uint64_list **list) {
	qsort((*list)->arr, (*list)->used, sizeof(uint64_t), list_cmpfunc_reverse);
}

/*
 * Create a dynamically allocated list of uint64_ts
 * return value: A preallocated list, or NULL if calloc fails.
 */
uint64_list *list_create(void) {
	// Allocate the list itself
	uint64_list *list = calloc(1, sizeof(*list));
	if (list == NULL)
		return NULL;
	list->used = 0;
	list->size = 10;
	// Allocate the storage array
	list->arr = calloc(list->size, sizeof(uint64_t));
	if (list->arr == NULL) {
		return NULL;
	}
	// Set the current element-pointer
	list->p = list->arr;

	return list;
}

/*
 * Free a list.
 * list: The list to free; the pointer will also be set to NULL
 * return value: none
 */
void list_free(uint64_list **list) {
	// Free the storage array
	free((*list)->arr);
	// Free the list itself
	free(*list);
	*list = NULL;
}

/*
 * Compresses the list down to the bare minimum of elements, virtually freeing unused memory
 * list: the list to work with
 * return value: 1 on success, 0 on failure
 */
uint8_t list_compress(uint64_list **list) {
	if ((*list)->size == (*list)->used)
		return 1;
	// Valgrind forces us to do this; I'm not sure if the array CAN even be moved by a downsizing, but it stops the complaining,
	// and better safe than sorry.
	size_t p_offset = (*list)->p - (*list)->arr;

	uint64_t *new_ptr = realloc((*list)->arr, (*list)->used * sizeof(uint64_t));
	if (new_ptr == NULL) {
		list_free(list);
		return 0;
	}
	(*list)->arr = new_ptr;
	(*list)->p = new_ptr + p_offset;
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
	if ((*list)->used + 1 > (*list)->size) {
		size_t new_size = (*list)->used + 10;
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

	*(*list)->p++ = n;
	(*list)->used++;

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
		printf("Element: %lu\n", list->arr[i]);
	}

	printf("List stats in main(): used=%zu, size=%zu\n", list->used, list->size);

	list_compress(&list);

	printf("List stats in main() post-compress: used=%zu, size=%zu\n", list->used, list->size);

	list_free(&list);

	return 0;
}

