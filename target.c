#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



int read_int(char* input) {

	char buf[100];
	fprintf(stderr, "buffer address: %p\n", buf);

	strcpy(buf, input);

	int i = atoi(buf);
	return i;
}

void main(int argc, char *argv[]) {
	assert(argc == 2);

	int x = read_int(argv[1]);
	printf("x=%d\n", x);
}
