#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <gmp.h>

/*
 * n: the fibonacci number
 * return value: the nth fibonacci number (although there seems to be two or more ways to count)
 */
uint64_t fib(uint64_t n) {
	assert(n < 50); /* no point in trying, this way is too slow for these numbers */
	if (n == 0 || n == 1)
		return 1;
	return fib(n-1) + fib(n-2);
}

/*
 * n: the number to check for primality
 * return value: 1 if prime, 0 if composite (nonprime)
 */
uint8_t isprime(register uint64_t n)
{
	if (n == 2)
		return 1;
	if ((n & 1) == 0)
		return 0;

	register uint64_t sqrt_n = ((uint64_t)sqrt(n)) + 1;
	for (register uint64_t i=3; i<= sqrt_n; i+=2) {
		if (n % i == 0)
			return 0;
	}
	return 1;
}

/*
 * n: the number for which to count the number of divisors
 * return value: the number of divisors, including 1 and the number itself
 */
uint64_t num_divisors(uint64_t n) {
    if (n == 1)
        return 1;

    uint64_t factors = 2; /* 1 and the number itself */
    uint64_t sqrt_n = (uint64_t)sqrt(n);

    for (uint64_t i=2; i <= sqrt_n; i++) {  
        if (n % i== 0) {  
            factors++;
            if (n/i != sqrt_n)
                factors++;
        }
    }

	return factors;
}

/*
 * n: the number to work with
 * return value: a malloc()ed string containing the number in binary form, without leading zeroes
 */
char *bin(uint64_t n) {
	/* UGLY workaround to the no-leading-zeroes problem! (Which only exists for n = 0...) */
	if (n == 0) {
		char *str = malloc(2);
		str[0] = '0'; str[1] = 0;
		return str;
	}

	char *str = malloc(65); /* 64 bits + NUL */
	if (str == NULL)
		return NULL;
	char *p = str;
	memset(str, 0, 65);

	uint8_t leading_zero = 1;
	for (uint64_t i = (1ULL << ((sizeof(n)*8)-1)); i !=0; i >>= 1) {
		if (n & i) {
			*p++ = '1';
			leading_zero = 0; /* We've found our first nonzero digit, start printing out zeroes! */
		}
		else if (!leading_zero)
			*p++ = '0';
	}

	return str;
}

/*
 * str: the string to check for palindromity(!)
 * return value: 1 if a palindrome, otherwise 0
 */
uint8_t is_palindrome_str(const char *str) {
	/* Optimized version (no malloc/copying/strcmp/free) written 2009-10-20, with no help */
	char *start = (char *)str; /* first character */
	char *end = (char *)(str + strlen(str) - 1); /* last character (-1 for the NUL) */
	while (start < end) {
		if (*start++ != *end--)
			return 0;
	}
	return 1;
}

char *reverse(const char *str) {
	int len = strlen(str);
	char *rev = malloc(len+1); /* +1 for NUL */
	if (rev == NULL)
		return NULL;
	memset(rev, 0, len+1);

	for (uint32_t i=0; i<len; i++) {
		rev[len-i-1] = str[i];
	}

	return rev;
}

/* 
 * I would really have preferred to work with NUMBERS, but couldn't figure out how to
 * get one digit at a time in the forward direction... ... reliably for numbers that have 20 digits.
 */
uint8_t is_palindrome(uint64_t n) {
	char buf[21]; /* len(2^64) = 20, + NUL */
	sprintf(buf, "%lu", n);

	return is_palindrome_str(buf);
}

/*
 * base: the base
 * exp: the exponent
 * return value: base^exp
 */
uint64_t int_pow(const uint64_t base, uint64_t exp) {
	if (base == 1 || exp == 0) /* 1^x is always 1, even for x = 0; 0^0 = 1 but all other 0^x = 0 (handled below) */
		return 1;
	else if (base == 0)
		return 0;
	// 10^20 > 2^64 (not sure how to check for other cases, like 9^1000, though...)
	assert ( ! (base == 10 && exp >= 20) ); /* XXX: is this correct? (NOT makes my head hurt) */
	uint64_t result = base;
	for (; exp>1; exp--) {
		result *= base;
	}
	return result;
}

/*
 * NOTE: This is actually faster than log10(num)+1, by ~40%.
 * num: the number to check
 * return value: the number of digits in the number
 */
/*inline*/ uint8_t get_length(uint64_t num) {
	if (num == 0) 
		return 1;
	uint8_t digits = 0;
	for (uint64_t i = 1; i <= num; i *= 10)
		digits++;

	return digits;
}

// The new function is actually ~40%+ faster.
/*
uint8_t get_length_old(uint64_t num) {
	return ( ((int)log10(num)) + 1);
}
*/

/*
 * num: the number.
 * digit: the number, where 1 = the RIGHTMOST digit, 2 = the second-to-rightmost etc.
 * return value: the digit.
 */
uint8_t get_digit_rev(uint64_t num, uint8_t digit) {
	assert(digit <= 19 && digit != 0);
	if (digit > get_length(num)) {
		fprintf(stderr, "Error: Tried to get digit %hhu out of the number %lu!\n", digit, num);
		exit(1);
	}
	return ( (num % int_pow(10,digit)) / (int_pow(10,digit)/10) );
}

/*
 * num: the number.
 * digit: the number, where 1 = the LEFTMOST digit, 2 = the second-to-leftmost etc.
 * return value: the digit.
 */
/*inline*/ uint8_t get_digit(uint64_t num, uint8_t digit) {
	assert(digit != 0);
	uint8_t log_value = (uint8_t)log10(num);

	// Check that the digit exists
	if (log_value+1 < digit) {
		fprintf(stderr, "Error: Tried to get digit #%hhu out of the number %lu!\n", digit, num);
		exit(1);
	}
	digit = log_value - digit + 2; // Black magic. XXX: Understand your own creation!
	assert (digit <= 19); /* 10^20 > 2^64! Overflow which causes incorrect results! */
	return ( (num % int_pow(10,digit)) / (int_pow(10,digit)/10) );
}

/*
 * num: the number to check for "pandigitality"
 * return value: 1 if it's pandigital, 0 otherwise
 */
uint8_t is_pandigital(uint64_t num) {
	if (num < 10)
		return 1;

	if (num % 10 == 0)
		return 0; // These numbers contain (end with) a 0 and thus cannot be pandigital

	uint8_t len = get_length(num);
	if (len > 9)
		return 0;

	uint8_t seen[9] = {0}; /* tracks the use count for each digit */

	uint8_t d = 0;
	for (uint8_t digit = 1; digit <= len; digit++) {
		d = get_digit(num, digit);
		if (d == 0)
			return 0; // A pandiginal number is only 1 to n where n is the length; a 0 cannot exist in it
		if (++seen[d-1] != 1) {
			return 0; // This digit is seen more than once; the result cannot be true
		}
	}

	for (uint8_t i = len; i < 9; i++) { /* +1 to ignore 0, which is never in a pandigital number */
		if (seen[i] != 0)
			return 0;
	}

	return 1;
}
		
/*
 * num1: first number to compare, with...
 * num2: the second number
 * return value: 1 if they're anagrams, otherwise 0
 */
uint8_t is_anagram(uint64_t num1, uint64_t num2) {
	if (num1 == num2)
		return 1;

	uint8_t len1 = get_length(num1);
	uint8_t len2 = get_length(num2);

	if (len1 != len2)
		return 0;

	uint8_t seen1[10] = {0}; /* tracks the use count for each digit */
	uint8_t seen2[10] = {0}; /* tracks the use count for each digit */

	/*
	 * These loops are simple, really. We loop through each digit, and increase the 
	 * number at seenX[n] by one for each occurrence. seenX[0] is then the number of times
	 * the digit 0 was encountered, etc.
	 */
	for (uint8_t digit = 1; digit <= len1; digit++)
		seen1[get_digit(num1, digit)]++;
	for (uint8_t digit = 1; digit <= len2; digit++) 
		seen2[get_digit(num2, digit)]++;
		
	/* Also simple: Compare the arrays byte for byte. The sizeof is really unnecessary, but is done
	 * at compile time, so it doesn't matter. */
	return (memcmp(seen1, seen2, (sizeof(uint8_t) * 10)) == 0);
}

/*
 * num: the GMP integer to work with
 * return value: a regular uint64_t with the digital sum
 */
uint64_t gmp_digital_sum(const mpz_t in_num) {
	uint64_t sum = 0;
	mpz_t num;
	mpz_init_set(num, in_num);

	while (mpz_cmp_ui(num, 0) != 0) { // Works like strcmp, 0 == equal, so loop while num isn't 0
		sum += mpz_fdiv_ui(num, 10);  // sum += num % 10
		mpz_tdiv_q_ui(num, num, 10);  // num /= 10;
	}

	mpz_clear(num);
	return sum;
}

/*
 * str: the string to work on
 * start: the starting offset (0 for the first position, 1 for the second etc.; negative offsets count from the end of the string, -1 being the last)
 * length: the length to extract. 0 extracts the remainder of the string; negative lengths stop at n characters from the end.
 */
char *substr(const char *str, int start, int length) {
	if (str == NULL)
		return NULL;
	const uint32_t str_length = strlen(str);

	// Calculate the starting position for negative start values
	if (start < 0) {
		if (-start > str_length) { // for a 5-char string, -5 <= start <= 5 must be true; the second part is checked below
			return NULL;
		}
		start = str_length - (-start); /* describes itself. we start at str_length minus the negated start value.
										  start = str_length + start should do the same, but is less clear. */
	}

	if (length == 0) {
		length = str_length - start; /* simple enough, the length is from the staring point to the end */
	}
	else if (length < 0) {
		length = str_length - (-length) - start; /* a bit more complicated; we need to subtract (the negated) length here, too */
	}

	/* If length is less than 0 even after the changes, call it quits. */
	if (length < 0) { /* length == 0 returns "" */
		return NULL;
	}

	// Make sure we stay within the bounds of "str"
	if (start+length > str_length || 
		str <= ( (char *) ( (unsigned long)start + (unsigned long)length ) )) { // XXX: OBOE?
		return NULL;
	}

	char *out = malloc(length + 1);
	if (out == NULL)
		return NULL;
	memset(out, 0, length + 1);

	char *p = out;
	for (uint32_t i = start; i < start+length; i++) {
		*p++ = str[i];
	}

	return out;
}

/*
 * n: the fibonacci number
 * return value: a pointer to a GMP integer containing the value
 * notes: This is UGLY CODE, and I have to admit I didn't create the algorithm
 * itself, only the GMP implementation. I'm also not sure whether the malloc
 * and returning a pointer are really necessary.
 */
mpz_t *gmp_fib(uint64_t n) {
	mpz_t f, f_2; /* represents the current number, and f-2 */
	mpz_t *f_1 = malloc(sizeof(mpz_t)); /* represents f-1 (and the answer) */

	mpz_init_set_ui(*f_1, 1);
	mpz_init_set_ui(f_2, 2);
	mpz_init(f);

	for (uint64_t i = 3; i <= n; i++) {
		mpz_add(f, *f_1, f_2);
		mpz_set(*f_1, f_2);
		mpz_set(f_2, f);
	}
	mpz_clear(f_2);
	mpz_clear(f);

	return f_1;
}

/*
 * num: the GMP integer to check
 * return value: the number of digits in the number
 */
uint64_t gmp_get_length(mpz_t num) {
	if (mpz_cmp_ui(num, 0) == 0)  // Number equals 0; 1 digit
		return 1;
	uint64_t digits = 0;
	mpz_t i;
	mpz_init_set_ui(i, 1);

	while (mpz_cmp(i, num) <= 0) {
		mpz_mul_ui(i, i, 10);
		digits++;
	}

	mpz_clear(i);

	return digits;
}

// TODO: gmp_get_digit()?
