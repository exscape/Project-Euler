#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>

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
uint8_t get_length(uint64_t num) {
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
		fprintf(stderr, "Error: Tried to get digit %hhu out of the number %llu!\n", digit, num);
		exit(1);
	}
	return ( (num % int_pow(10,digit)) / (int_pow(10,digit)/10) );
}

/*
 * num: the number.
 * digit: the number, where 1 = the LEFTMOST digit, 2 = the second-to-leftmost etc.
 * return value: the digit.
 */
inline uint8_t get_digit(uint64_t num, uint8_t digit) {
	assert(digit != 0);
	uint8_t log_value = (uint8_t)log10(num);

	// Check that the digit exists
	if (log_value+1 < digit) {
		fprintf(stderr, "Error: Tried to get digit #%hhu out of the number %llu!\n", digit, num);
		exit(1);
	}
	digit = log_value - digit + 2; // Black magic. XXX: Understand your own creation!
	assert (digit <= 19); /* 10^20 > 2^64! Overflow which causes incorrect results! */
	return ( (num % int_pow(10,digit)) / (int_pow(10,digit)/10) );
}
