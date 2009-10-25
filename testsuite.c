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
		sprintf(orig, "%lu", num);
		memset(copy, 0, 21); // Zero the copy, since the algorithm below doesn't NULL terminate
		for (uint8_t curdig=1; curdig <= (uint8_t)log10(num)+1; curdig++)  {
			*(copy+curdig-1) = get_digit(num, curdig) + 0x30;
		}

		if (strcmp(orig,copy)) {
			printf("get_digit() error: orig = %s, copy = %s\n", orig, copy);
			errcount++;
		}
	}
	printf("Done testing get_digit(), %lu errors\n", errcount);
}

// Tests that get_digit_rev() returns the correct value
void test_get_digit_rev() {
	uint64_t errcount = 0;
	char orig[21] = {0}, 
		 copy[21] = {0};
	char *rev; /* pointer to the reversed string */
	
	  for (uint64_t num = 1000000; num >= 1; num--) {
		sprintf(orig, "%lu", num);
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
	printf("Done testing get_digit_rev(), %lu errors\n", errcount);
}

// Tests that get_length() returns the correct value
void test_get_length() {
	uint64_t errcount = 0;
	char buf[21];
	for (uint32_t i = 0; i <= 10000000; i++) {
		sprintf(buf, "%u", i);
		if (get_length(i) != strlen(buf)) {
			printf("get_length() error at %u (get_length() says %hhu, actual length %zu)\n", i, get_length(i), strlen(buf));
			errcount++;
		}
	}
	printf("Done testing get_length(), %lu errors\n", errcount);
}

void test_is_anagram() {
	printf("Implement test_is_anagram()!\n");
}

void test_is_pandigital() {
//	uint64_t errcount = 0;
	printf("Implement test_is_pandigital()!\n");
//	printf("Done testing is_pandigital, %lu errors\n", errcount);
}

uint8_t /* num_errors */ test_substr(const char *str, int start, int length, const char *expect) {
	char *sub = substr(str, start, length);
	if (sub == NULL) {
		fprintf(stderr, "*FAIL* in substr(\"%s\", %d, %d): got NULL, expected \"%s\"!\n", str, start, length, expect);
		return 1;
	}

	if (strcmp(sub, expect) != 0) {
		fprintf(stderr, "*FAIL* in substr(\"%s\", %d, %d): got \"%s\", expected \"%s\"\n", str, start, length, sub, expect);
		free(sub);
		return 1;
	}
	else {
		fprintf(stderr, "PASS in substr(\"%s\", %d, %d): got \"%s\", expected \"%s\"\n", str, start, length, sub, expect);
		free(sub);
		return 0;
	}
}

void test_substr_all(uint8_t quiet) {
	uint64_t errcount = 0;
	char *str = "ABCDEF";

	if (!quiet)
		printf("Positive start tests:\n");
	errcount += test_substr(str, 0, 6, "ABCDEF");
	errcount += test_substr(str, 1, 5, "BCDEF");
	errcount += test_substr(str, 0, 3, "ABC");
	errcount += test_substr(str, 4, 2, "EF");
	errcount += test_substr(str, 5, 1, "F");
	errcount += test_substr(str, 3, 2, "DE");
	errcount += test_substr("Hello, world!", 1, 4, "ello");
	errcount += test_substr("1 2 3, anyone there?", 2, 1, "2");
	if (!quiet && errcount == 0)
		printf("All OK\n");

	if (!quiet) {
		printf("\n");
		printf("Negative start tests:\n");
	}
	errcount += test_substr(str, -3, 1, "D");
	errcount += test_substr(str, -4, 3, "CDE");
	errcount += test_substr(str, -4, 1, "C");
	errcount += test_substr(str, -5, 1, "B");
	errcount += test_substr(str, -6, 6, "ABCDEF");
	errcount += test_substr("Testing, testing", -7, 4, "test");
	if (!quiet && errcount == 0)
		printf("All OK\n");

	if (!quiet) {
		printf("\n");
		printf("Zero length tests:\n");
	}
	errcount += test_substr(str, 0, 0, "ABCDEF");
	errcount += test_substr(str, 1, 0, "BCDEF");
	errcount += test_substr(str, 4, 0, "EF");
	errcount += test_substr(str, 5, 0, "F");
	errcount += test_substr("", 0, 0, "");
	if (!quiet && errcount == 0)
		printf("All OK\n");

	if (!quiet) {
		printf("\n");
		printf("Zero length AND negative start tests:\n");
	}
	errcount += test_substr(str, -1, 0, "F");
	errcount += test_substr(str, -4, 0, "CDEF");
	errcount += test_substr(str, -2, 0, "EF");
	if (!quiet && errcount == 0)
		printf("All OK\n");

	if (!quiet) {
		printf("\n");
		printf("Negative length (and also start) tests:\n");
	}
	errcount += test_substr(str, 0, -1, "ABCDE");
	errcount += test_substr(str, 0, -3, "ABC");
	errcount += test_substr(str, 0, -4, "AB");
	errcount += test_substr(str, 2, -1, "CDE");
	errcount += test_substr(str, -3, -1, "DE");
	errcount += test_substr(str, 4, -1, "E");
	errcount += test_substr(str, 0, -6, "");
	if (!quiet && errcount == 0)
		printf("All OK\n");

	if (!quiet) {
		printf("\n");
		printf("The following should fail:\n");
		test_substr(str, 6, 2, "(null)");
		test_substr(str, 1, 10, "(null)");
		test_substr(str, -10, 0, "(null)");
		test_substr(str, -10, 12, "(null)");
		test_substr(str, -7, 3, "(null)");
		test_substr(str, 0, -7, "(null)");
		test_substr(str, -3, -4, "(null)");
		test_substr(str, 4, -4, "(null)"); /* this would return "" in PHP, but screw that. */
	}

	// NOTE: length is unsigned and can never be less than 0, so don't test for it
	
	printf("Done testing substr(), %lu errors\n", errcount);
}

int main() {
	test_get_digit();
	test_get_digit_rev();
	test_get_length();
	test_is_pandigital();
	test_is_anagram();
	test_substr_all(0); // 1 = quiet mode on

	return 0;
}
