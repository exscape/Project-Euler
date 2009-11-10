#include <iostream>
#include <algorithm>

int main() {
	char num[] = "0123456789";
	for (int i=0; i < 999999; i++)
		std::next_permutation(num, num+10);

	std::cout << num << std::endl;

	return 0;
}
