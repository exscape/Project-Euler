#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	std::vector<short> v;
	for (short i=0; i<=9; i++)
		v.push_back(i);

	long cnt = 1;
	while (next_permutation(v.begin(), v.end())) {
		cnt++;
		if (cnt == 1000000) {
			for (short i=0; i<=9; i++)
				std::cout << v[i]; 
			std::cout << std::endl;
			break;
		}
	}

	return 0;
}
