#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17, + a lot of more days spent working on various memory allocation/dynamic array stuff for list.c */

#define NUM 600851475143
//#define NUM 26
//#define NUM 13195 /* Correct answer: 29 */

/*
 * Returns a list of (non-unique) prime factors, i.e. {2, 2, 2, 5} if the input number is 40
 * orig_n: The number to calculate the factors for.
 * return value: A preallocated list containing all the prime factors. The caller is resonsible for freeing this.
 */
uint64_list *get_prime_factors(const uint64_t orig_n) {
	uint64_list *list = list_create(10);
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
		printf("Prime factor: %lu\n", list->arr[i]);
	}

	printf("Answer: %lu\n", list->arr[list->used-1]);

	list_free(&list);

	return 0;
}

