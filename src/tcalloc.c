#include<malloc.h>
#include<assert.h>
#include <stdlib.h>
#include <string.h>


void* tcalloc(int size) {
	assert(size > 0);
	void* buf = malloc(size);
	if (buf == NULL) {
		printf("error for malloc");
		exit(1);
	}
	memset(buf, 0, size);
	return buf;
}

void* tcrealloc(void* buf, int size) {
	assert(buf != NULL);
	assert(size > 0);
	void* buf2 = realloc(buf, size);
	return buf2;
}
