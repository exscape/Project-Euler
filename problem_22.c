#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "util.c"

/* Written: 2009-10-26, 2009-10-27 */

#define DATAFILE "data/problem_22"

int main() {
	FILE *f = fopen(DATAFILE, "r");
	if (!f) {
		fprintf(stderr, "Failed to open datafile (%s)\n", DATAFILE);
		exit(1);
	}

	fseek(f, 0, SEEK_END);
	uint32_t bufsize = ftell(f);
	rewind(f);
	if (bufsize == 1)
		exit(1);

	char *buf = malloc(bufsize + 1);
	if (buf == NULL)
		exit(1);

	if (fread(buf, 1, bufsize, f) != bufsize) {
		fprintf(stderr, "fread() failed!\n");
		exit(1);
	}

	fclose(f); f = NULL;

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
	uint32_t i = 0; /* counts the current name index */
	uint8_t in_string = 0; /* BOOL, really; whether we are within quotes */
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
	sort_char_array(arr, num_elements);

	/* Calculate the "name value */
	uint64_t sum = 0;
	for (int i=0; i < num_elements; i++) {
		uint32_t value = 0;
		char *p = arr[i];
		for (; *p != 0; p++) {
			value += (*p - 'A' + 1);
		}
		value *= (i+1); /* value is sum of letter positions times index in list */
		sum += value;
	}

	printf("Answer: %lu\n", sum);

	/* Cleanup */
	for (uint32_t i = 0; i < num_elements; i++) {
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr); arr = NULL;
	return 0;
}
