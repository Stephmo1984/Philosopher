/* times: use gettimeofday() to get the elapsed time */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>		/* used for casting clock_t to uintmax_t for printf */
#include <sys/time.h>		/* needed for the gettimeofday() system call */

int
main(int argc, char **argv) {
	struct timeval start;	/* starting time */
	struct timeval end;	/* ending time */
	unsigned long diff_usec;	/* elapsed microseconds */

	gettimeofday(&start, 0);	/* mark the start time */
	printf("start: %li seconds\n", start.tv_sec);
	printf("start: %li microseconds\n", start.tv_usec);

	printf("---------\n");

	usleep(2000000);		/* sleep for 2 seconds */

	gettimeofday(&end, 0);		/* mark the end time */
	
	printf("end: %li seconds\n", end.tv_sec);
	printf("end: %li microseconds\n", end.tv_usec);

	printf("---------\n");

	diff_usec = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);

	printf("diff time: %lu microseconds\n", diff_usec);
	printf("diff time: %lu milliseconds\n", diff_usec / 1000);
	printf("diff time: %lu seconds\n", diff_usec / 1000000);

	exit(0);
}