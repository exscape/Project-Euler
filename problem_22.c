#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>

/* Written: 2009-10-26, XXX */

#define DATAFILE "data/problem_22"

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
//		printf("read %u bytes\n", chunk_read);
		chunk[chunk_read] = 0;
		total_read += chunk_read;
		if (total_read >= bufsize) {
			buf = realloc(buf, bufsize * 2);
//			printf("total_read = %u, bufsize = %d, resizing to %d bytes\n", total_read, bufsize, bufsize * 2);
			if (buf == NULL) {
				exit(1);
			}
			bufsize *= 2;
		}

		strncat(buf, chunk, bufsize-1);
	}
	fclose(f); f = NULL;
	free(chunk);

//	printf("bufsize: %u, strlen(buf) = %zu\n", bufsize, strlen(buf));

	uint16_t num_elements = 1; /* count the first one, too */
	for (char *p = buf; *p != 0; p++) {
		if (*p == ',')
			num_elements++;
	}
	printf("%hu names in file\n", num_elements);

	char **arr = malloc(num_elements * sizeof(char *));

	for (uint32_t i = 0; i < num_elements; i++) {
		arr[i] = malloc(33); // XXX: Don't just make up a number!
		if (arr[i] == NULL) {
			fprintf(stderr, "malloc() loop failed at element %u!\n", i);
			exit(1);
		}
	}

	// XXX: read in the names into the array

	for (uint32_t i = 0; i < num_elements; i++) {
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr); arr = NULL;
	free(buf); buf = NULL;
	return 0;
}
