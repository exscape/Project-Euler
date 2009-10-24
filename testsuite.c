#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>
#include "util.c"

// Tests that get_digit() returns the correct value
void test_get_digit() {
	uint64_t errcount = 0;
	char orig[21] = {0}, 
		 copy[21] = {0};
	
	  for (uint64_t num = 1000000; num >= 1; num--) {
	//for (uint64_t num = 1; num <= 100000; num++) {
		sprintf(orig, "%llu", num);
		memset(copy, 0, 21); // Zero the copy, since the algorithm below doesn't NULL terminate
		for (uint8_t curdig=1; curdig <= (uint8_t)log10(num)+1; curdig++)  {
			*(copy+curdig-1) = get_digit(num, curdig) + 0x30;
		}

		if (strcmp(orig,copy)) {
			printf("get_digit() error: orig = %s, copy = %s\n", orig, copy);
			errcount++;
		}
	}
	printf("Done testing get_digit(), %llu errors\n", errcount);
}

// Tests that get_digit_rev() returns the correct value
void test_get_digit_rev() {
	uint64_t errcount = 0;
	char orig[21] = {0}, 
		 copy[21] = {0};
	char *rev; /* pointer to the reversed string */
	
	  for (uint64_t num = 1000000; num >= 1; num--) {
		sprintf(orig, "%llu", num);
		memset(copy, 0, 21); // Zero the copy, since the algorithm below doesn't NULL terminate
		for (uint8_t curdig=1; curdig <= (uint8_t)log10(num)+1; curdig++)  {
			*(copy+curdig-1) = get_digit_rev(num, curdig) + 0x30;
		}
		rev = reverse(copy);
		assert (rev != NULL);

		if (strcmp(orig,rev)) {
			printf("get_digit_rev() error: orig = %s, revcopy = %s\n", orig, rev);
			errcount++;
		}
		free(rev);
	}
	printf("Done testing get_digit_rev(), %llu errors\n", errcount);
}

// Tests that get_length() returns the correct value
void test_get_length() {
	uint64_t errcount = 0;
	char buf[21];
	for (uint32_t i = 0; i <= 10000000; i++) {
		sprintf(buf, "%lu", i);
		if (get_length(i) != strlen(buf)) {
			printf("get_length() error at %lu (get_length() says %hhu, actual length %zu)\n", i, get_length(i), strlen(buf));
			errcount++;
		}
	}
	printf("Done testing get_length(), %llu errors\n", errcount);
}

void test_is_anagram() {
	printf("Implement test_fix_anagram()!\n");
}

void test_is_pandigital() {
	for (uint32_t i = 0; i<=1000000; i++) {
		if (is_pandigital(i)) {
			printf("pandigital: %lu\n", i);
		}
	}
}

int main() {
//	test_get_digit();
//	test_get_digit_rev();
//	test_get_length();
	test_is_pandigital();
	test_is_anagram();

	return 0;
}
