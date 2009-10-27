#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>

/* Written: 2009-10-26, 2009-10-27, XXX */

#define DATAFILE "data/problem_22"

// "Improved" bubble sort, but better than NO sort
void char_sort_array(char **arr, const uint32_t num_elements) {
	uint32_t loops = 0;
	uint32_t n = num_elements;
	uint8_t swapped;
	char *tmp;
	do {
		swapped = 0;
		for (uint32_t i=0; i < n-1; i++, loops++) {
			if (strcmp(arr[i], arr[i+1]) > 0) {
				/* swap the elements */
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
				swapped = 1;
			}
		}
		n -= 1; /* for each iteration, one more element is guaranteed to be at its correct, near-the-end place */
	} while (swapped);
}

int main() {
	FILE *f = fopen(DATAFILE, "r");
	if (!f) {
		fprintf(stderr, "Failed to open datafile (%s)\n", DATAFILE);
		exit(1);
	}

	uint32_t bufsize = 2048; /* A size we know is too small, to practice using realloc() */
	char *chunk = malloc(1024);
	char *buf = malloc(bufsize);
	if (chunk == NULL || buf == NULL)
		exit(1);

	uint32_t total_read = 0;
	uint32_t chunk_read = 0;
	while (!feof(f)) {
		chunk_read = fread(chunk, 1, 1023, f);
		chunk[chunk_read] = 0;
		total_read += chunk_read;
		if (total_read >= bufsize) {
			/* total data is too large to fit, we need to resize our buffer */
			buf = realloc(buf, bufsize * 2);
			if (buf == NULL) {
				exit(1);
			}
			bufsize *= 2;
		}

		/* append the newly read data to the buffer */
		strncat(buf, chunk, bufsize-1);
	}
	fclose(f); f = NULL;
	free(chunk);

	uint16_t num_elements = 1; /* count the first one, too (since there's no preceding comma, we start at 1) */
	for (char *p = buf; *p != 0; p++) {
		if (*p == ',')
			num_elements++;
	}
	printf("%hu names in file\n", num_elements);

	/* allocate space for num_elements char pointers */
	char **arr = malloc((num_elements) * sizeof(char *));

	/* allocate and set to zero memory for all the strings */
	for (uint32_t i = 0; i < num_elements; i++) {
		arr[i] = malloc(16); // XXX: Don't just make up a number!
		if (arr[i] == NULL) {
			fprintf(stderr, "malloc() loop failed at element %u!\n", i);
			exit(1);
		}
		memset(arr[i], 0, 16);
	}

	/* read the strings from the linear buffer into the array */
	uint32_t i = 0;
	uint8_t in_string = 0;
	char *buf_p = buf;
	for (char *cur_str = arr[0]; i < num_elements; cur_str = arr[++i]) {
		for (char *p = cur_str; buf_p <= buf+strlen(buf); buf_p++ /* [sic!] */) {
			if (*buf_p == '"') {
				in_string = 1;
				continue;
			}
			if (*buf_p == ',') {
				*p = 0;
				in_string = 0;
				buf_p++; // skip to the next name
				break;
			}
			if (in_string)
				*p++ = *buf_p;
		}
	}
		
	/* we're done with the buffer now */
	free(buf); buf = NULL; buf_p = NULL;

	/* sort the array */
	char_sort_array(arr, num_elements);


	// XXX: Do the actual work


	/* Cleanup */
	for (uint32_t i = 0; i < num_elements; i++) {
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr); arr = NULL;
	return 0;
}
