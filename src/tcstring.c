#include<string.h>
#include<assert.h>
#include"tcstring.h"
#include"tcalloc.h"


TCString* newstr(char* s) {
	assert(s != NULL);
	TCString* buf = tcalloc(sizeof(TCString));
	int len = strlen(s);
	assert(len >= 0);
	char* str= tcalloc(len+1);
	strncat(str, s,len);
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
		src->len += append->len;
	}
}

char* tctoC(TCString* src) {
	return src->buf;
}

