#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-17, + a lot of more days spent working on various memory allocation/dynamic array stuff for list.c */

#define NUM 600851475143

int main() {
	uint64_list *list = get_prime_factors(NUM);
	if (list == NULL) {
		fprintf(stderr, "Failed to get a list of prime factors!\n");
		exit(1);
	}

	printf("Answer: %lu\n", list->arr[list->used-1]);

	list_free(&list);

	return 0;
}

