#include<string.h>
#include<assert.h>
#include<malloc.h>
#include"tcstring.h"
#include"tcalloc.h"


TCString* newstr(char const* s) {
	assert(s != NULL);
	TCString* buf = tcalloc(sizeof(TCString));
	int len = strlen(s);
	assert(len >= 0);
	char* str = tcalloc(len + 1);
	strncat(str, s, len);
	buf->buf = str;
	buf->len = len;
	return buf;
}

void tcstrcat(TCString* src, TCString* append) {
	assert(src != NULL);
	assert(append != NULL);
	if (append->len > 0) {
		char* buf = tcrealloc(src->buf, src->len + append->len + 1);
		src->buf = buf;
		strcat(src->buf, append->buf);
		src->len += append->len;
	}
}

void tcstrcatc(TCString* src, const char* append) {
	assert(src != NULL);
	assert(append != NULL);
	int len = strlen(append);
	if (len > 0) {
		char* buf = tcrealloc(src->buf, src->len + len + 1);
		src->buf = buf;
		strcat(src->buf, append);
		src->len += len;
	}
}

char* tctoC(TCString* src) {
	return strdup(src->buf);
}

void freestr(TCString* src) {
	assert(src != NULL);
	if (src->buf != NULL) {
		free(src->buf);
		src->buf[0] = '\0';
		src->len = 0;
	}
	free(src);
}
