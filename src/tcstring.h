#ifndef TCSTRING_H
#define TCSTRING_H

typedef struct TCString {
	int len;
	char* buf;
} TCString;

TCString* newstr(const char* s);

void tcstrcat(TCString* src, TCString* append);

void tcstrcatc(TCString* src, char const* append);

char* tctoC(TCString* src);

void freestr(TCString* src);

#endif