#ifndef TCSTRING_H
#define TCSTRING_H

typedef struct TCString {
	int len;
	char* buf;
} TCString;

TCString* newstr(char* s);

void tcstrcat(TCString* src, TCString* append);

char* tctoC(TCString* src);

#endif