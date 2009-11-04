#include <iostream>
#include <set>
#include <vector>
#include <stdint.h>

/* Written: 2009-11-01 (late evening), 2009-11-02 */
/* Converted to C++ 2009-11-04 */

uint16_t divisor_sum(uint16_t n) {
	uint16_t sum = 0;
	for (uint16_t i = 1; i <= n/2; i++)
		if (n % i == 0)
			sum += i;
		
	return sum;
}

#define is_abundant(x) (divisor_sum(x) > x)

int main() {
	std::vector<uint16_t> ab_nums;
	for (uint16_t i = 1; i <= 28123; i++) {
		if (is_abundant(i))
			ab_nums.push_back(i);
	}

	std::set<uint16_t> sums;

	for (std::vector<uint16_t>::iterator i = ab_nums.begin(); i != ab_nums.end(); i++) {
		for (std::vector<uint16_t>::iterator j = ab_nums.begin(); j != ab_nums.end(); j++) {
			sums.insert( *i + *j );
		}
	}

	uint64_t answer = 0;
	for (uint16_t i = 1; i <= 28183; i++) {
		if (sums.count(i) == 0) 
			answer += i;
	}

	std::cout << "Answer: " << answer << std::endl;

	return 0;
}
