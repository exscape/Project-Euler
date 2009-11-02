#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "util.c"

/* Written: 2009-11-01 (late evening), 2009-11-02, XXX */
// XXX: Uses slightly more than 700MB(!!!) of RAM (in practice). Obviously not acceptable.

uint16_t divisor_sum(uint16_t n) {
	uint16_t sum = 0;
	for (uint16_t i = 1; i <= n/2; i++)
		if (n % i == 0)
			sum += i;
		
	return sum;
}

#define is_abundant(x) (divisor_sum(x) > x)

int main() {
	uint64_list *ab_nums = list_create(7000);
	for (uint16_t i = 1; i <= 28123; i++) {
		if (is_abundant(i))
			list_add(&ab_nums, i);
	}
	uint64_list *sums = list_create(7000*7000);

	list_foreach_element(ab_nums, i) {
		list_foreach_element(ab_nums, j) {
			uint32_t sum = ab_nums->arr[i] + ab_nums->arr[j];
//			if (list_find(&sums, sum) == -1) { // A uniqueness search takes too long...
				list_add(&sums, sum);
//			}
		}
	}

	list_sort(&sums);

	uint64_t answer = 0;
	for (uint64_t i = 1; i <= 28183; i++) {
		if (list_bsearch(&sums, i) == -1)
			answer += i;
	}

	printf("Answer: %lu\n", answer);
	printf("List sizes: %lu + %lu elements * 8 bytes = ~%lu bytes total, plus overhead\n", list_length(&ab_nums), list_length(&sums), (list_length(&ab_nums) + list_length(&sums)) * 8);

	list_free(&ab_nums);
	list_free(&sums);

	return 0;
}
