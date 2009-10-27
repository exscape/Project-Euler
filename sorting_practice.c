#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void int_print_array(int arr[], int len) {
	for (int i=0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

inline void int_swap (int *n1, int *n2) {
	int tmp = *n2;
	*n2 = *n1;
	*n1 = tmp;
}

// Idea #1:
// Keep looping through the list from the start until it's sorted; if an out-of-place element is found,
// swap it with the current one.
// 3 1 4 2 -> 1 3 4 2 -> 1 3 2 4 -> 1 2 3 4
// Bubble sort, right?
//
// Idea #2:
// Bubble sort sucks.

/* This can't be bubble sort - it's even less efficient! */
void int_sort(int arr[], int num_elements) {
	for (int16_t i = 0; i < num_elements-1; i++) {
		int_print_array(arr, num_elements);
		if (arr[i+1] < arr[i]) {
			int_swap(&arr[i+1], &arr[i]);
			i = -1; // restart loop
			continue;
		}
	}
}

int main() {
//	int arr[] = {4, 10, 61, 2, 9, 0, -6, 5, -1, -2};
	int arr[] = {3, 1, 4, 2};
	int num_elements = sizeof(arr)/sizeof(int);


	// XXX: At LEAST imprement bubble sort properly!
	
	printf("Before: "); int_print_array(arr, num_elements);
	int_sort(arr, num_elements);
	printf("After: "); int_print_array(arr, num_elements);

	return 0;
}
