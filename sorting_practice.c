#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Prints the contents of an int array
void int_print_array(int arr[], int len, int loops) {
	for (int i=0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	if (loops > 0)
		printf("(%d loops)", loops);
	printf("\n");
}

// Swaps two integers
void int_swap (int *n1, int *n2) {
	int tmp = *n2;
	*n2 = *n1;
	*n1 = tmp;
}

// My naive bubble sort implementation
void stupid_int_sort(int arr[], int num_elements) {
	uint16_t loops = 0;
	for (int16_t i = 0; i < num_elements-1; i++) {
		loops++;
		if (arr[i+1] < arr[i]) {
			int_swap(&arr[i+1], &arr[i]);
			i = -1; // restart loop
			continue;
		}
	}
	printf("stupid_int_sort done, %hu loops\n", loops);
}

// A proper(?) bubble sort implementation, after reading the pseudocode for it
void int_bubble_sort(int arr[], const int num_elements) {
	uint16_t loops = 0;
	int n = num_elements;
	uint8_t swapped;
	do {
		int_print_array(arr, num_elements, -1); // NEW LOOP
		swapped = 0;
		for (uint16_t i = 0; i < n-1; i++, loops++) {
			if (arr[i+1] < arr[i]) {
				int_swap(&arr[i+1], &arr[i]);
				swapped = 1;
			}
		}
		n--;
	} while (swapped);

	printf("int_bubble_sort done, %hu loops\n", loops);
}

// Prints the contents of an array of strings
void char_print_array(char **arr, int num_elements) {
	for (int i=0; i<num_elements; i++) {
		printf("arr[%d]: %s\n", i, arr[i]);
	}
	printf("\n");
}

// Sorts an array of strings using bubble sort
void char_sort_array(char **arr, const int num_elements) {
	uint16_t loops = 0;
	uint32_t n = num_elements;
	uint8_t swapped;
	do {
		char_print_array(arr, num_elements); // NEW LOOP
		swapped = 0;
		for (uint16_t i=0; i < n-1; i++, loops++) {
			if (strcmp(arr[i], arr[i+1]) > 0) {
				char *tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
				swapped = 1;
			}
		}
		n -= 1;
	} while (swapped);
	
	printf("char_sort_array done, %hu loops\n", loops);
}

int main() {
	char **strings = malloc(4 * sizeof(char *));
	for (int i=0; i < 4; i++) {
		strings[i] = malloc(32);
		switch (i) {
			case 0: strcpy(strings[i], "Omega"); break;
			case 1: strcpy(strings[i], "Gamma"); break;
			case 2: strcpy(strings[i], "Alpha"); break;
			case 3: strcpy(strings[i], "Beta"); break;
		}
	}

	printf("Before:\n"); char_print_array(strings, 4);
	char_sort_array(strings, 4);
	printf("After:\n"); char_print_array(strings, 4);

	for (int i=0; i < 4; i++) {
		free(strings[i]);
	}
	free(strings);

/*
//	int arr[] = {4, 10, 61, 2, 9, 0, -6, 5, -1, -2, 10, 4, 342, -33, 40};
	int arr[] = {3, 1, 4, 2};
	int num_elements = sizeof(arr)/sizeof(int);

	printf("Before bubble sort: "); int_print_array(arr, num_elements, -1);
	int_bubble_sort(arr, num_elements);
	printf("After bubble sort: "); int_print_array(arr, num_elements, -1);
*/
	return 0;
}
