#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	size_t used; // The number of elements used
	size_t size; // The size of the array in elements
	uint64_t *arr; // The storage array itself
	uint64_t *p; // A pointer to the first free item in the array (XXX: (arr+used) instead?)
} uint64_list;

//
// XXX: TODO:
// * Removing elements? That could be a real pain, though; are there choices except leaving holes (wasted memory,
//   that needs another array tracking it) or compacting it at every removal (slow!)?
// * Fix list_foreach_elements; the current approach isn't exactly a black box one.
//

/*
 * Create a dynamically allocated list of uint64_ts
 * return value: A preallocated list, or NULL if calloc fails.
 */
uint64_list *list_create(size_t orig_size) {
	// Allocate the list itself
	uint64_list *list = calloc(1, sizeof(*list));
	if (list == NULL)
		return NULL;
	list->used = 0;
	list->size = orig_size;
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
 * Copies a list, up to the last used element, that is, the copy may be of smaller capacity than the original.
 * orig: the list to copy
 * return value: a pointer to the newly allocated and populated list
 */
uint64_list *list_copy(uint64_list **orig) {
	uint64_list *copy;
	if (orig == NULL)
		return NULL;

	copy = list_create((*orig)->used); /* make sure it's big enough */
	if (copy == NULL)
		return NULL;
	
	/* Do the copy */
	/*
	for (size_t i = 0; i < (*orig)->used; i++) {
		copy->arr[i] = (*orig)->arr[i];
	}
	*/
	memcpy(copy->arr, (*orig)->arr, (*orig)->used * sizeof(uint64_t));

	copy->used = (*orig)->used;

	return copy;
}

/*
 * Returns the index of the (first) value "n" in the list
 * list: the list to search
 * n: the item to search for
 * return value: the index of the item, or -1 if nothing is found.
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
