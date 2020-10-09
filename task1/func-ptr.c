#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 0			//change this to 1 to enable verbose output

/**
 * Signature for an function pointer that can compare
 * You need to cast the input into its actual 
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer) (const void *a, const void *b);

/**
 * compares 2 processes by priority
 * You can assume: 
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 */
int my_comparer_p(const void *this, const void *that) {
	int first = *(((int*)this + 2) );
	int second = *(((int*)that + 2) );
	return (second - first);
}

/**
 * compares 2 processes by arrival time
 * You can assume: 
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 */
int my_comparer_at(const void *this, const void *that) {
	int first = *(((int*)this + 1) );
	int second = *(((int*)that + 1) );
	return (first - second);
}

int main(int argc, char *argv[]) {
	// Flag to determine which sort to run.
	int ran = 0;
	for (int i = 0; i < 2; i++) {
		if (argc < 2) {
				 fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
				 fflush(stdout);
				 return 1;
		}

		/*******************/
		/* Parse the input */
		/*******************/
		FILE *input_file = fopen(argv[1], "r");
		if (!input_file) {
				 fprintf(stderr, "Error: Invalid filepath\n");
				 fflush(stdout);
				 return 1;
		}

		Process *processes = parse_file(input_file);

		/*******************/
		/* sort the input  */
		/*******************/
		Comparer process_comparer;
		if (ran == 0) {
			printf("Sorting by priority\n");
			process_comparer = &my_comparer_p;
		} else {
			printf("Sorting by arrival time\n");
			process_comparer = &my_comparer_at;
		}
		
	#if DEBUG
		for (int i = 0; i < P_SIZE; i++) {
					printf("%d (%d, %d) ",
					processes[i].pid,
					processes[i].priority, processes[i].arrival_time);
		}
		printf("\n");
	#endif

		qsort(processes, P_SIZE, sizeof(Process), process_comparer);

		/**************************/
		/* print the sorted data  */
		/**************************/

		for (int i = 0; i < P_SIZE; i++) {
					printf("%d (%d, %d)\n",
					processes[i].pid,
					processes[i].priority, processes[i].arrival_time);
		}
		fflush(stdout);
		fflush(stderr);

		/************/
		/* clean up */
		/************/
		free(processes);
		fclose(input_file);
		ran++;
	}

	return 0;
}
