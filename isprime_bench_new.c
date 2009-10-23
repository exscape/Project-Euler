#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.c"

int main() {
	uint64_t primes = 0;
	for (uint64_t i=3; i < (1ULL << 24ULL); i += 2)
		primes += isprime(i);
	
	return 0;
}
