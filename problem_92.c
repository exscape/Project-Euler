#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "list.c"

/* Written: 2009-11-02 */

uint8_t sq[] = {
	0*0,
	1*1,
	2*2,
	3*3,
	4*4,
	5*5,
	6*6,
	7*7,
	8*8,
	9*9
};

uint32_t sq_digits(uint32_t n) {
	uint32_t sum = 0;
	for (; n != 0; n /= 10)
		sum += sq[n % 10];

	return sum;
}

int main() {
	uint64_t answer = 0;
	for (uint64_t i = 1; i < 10000000; i++) {
		uint64_list *list = list_create(20);
		uint64_t next = i;
		while (list_find(&list, next) == -1) {
			list_add(&list, next);
			next = sq_digits(next);
			if (next == 89)
				break;
		} 
		list_add(&list, next);
		if (list->arr[list->used-1] == 89)
			answer++;
		list_free(&list);
	}

	printf("Answer: %lu\n", answer);

	return 0;
}
