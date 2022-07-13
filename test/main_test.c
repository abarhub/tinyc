#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"../src/main.h"


#define assert_eq(x, y) assert(x==y)
#define assert_ne(x, y) assert(x!=y)


void testNewToken() {
	Token* tmp = newToken(IDENTIFIER, "abc", 5, 6, 7, NULL);
	assert(tmp != NULL);
	assert(tmp->code == IDENTIFIER);
	assert(strcmp(tmp->text, "abc") == 0);
	assert(tmp->pos == 5);
	assert(tmp->line == 6);
	assert(tmp->column == 7);
	assert(tmp->next == NULL);

	Token* tmp2 = newToken(NUMBER, "123456", 14, 38, 75, tmp);
	assert(tmp2 != NULL);
	assert(tmp2->code == NUMBER);
	assert(strcmp(tmp2->text, "123456") == 0);
	assert(tmp2->pos == 14);
	assert(tmp2->line == 38);
	assert(tmp2->column == 75);
	assert(tmp2->next == tmp);
	free(tmp);
	free(tmp2);
}

#define  assert_compare( tokenList, codeText,  text2,  pos2,  line2,  column2)  \
				assert(tokenList != NULL); \
				assert(tokenList->code == codeText); 	\
				assert(strcmp(tokenList->text, text2) == 0); \
				assert(tokenList->pos == pos2); \
				assert(tokenList->line == line2); \
				assert(tokenList->column == column2); 

void testParse1() {

	Token* tokenList = NULL;

	tokenList = parse("..\\..\\..\\test\\test1.ci");

	printToken(tokenList);

	assert_compare(tokenList, IDENTIFIER, "void", 0, 1, 1);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, IDENTIFIER, "main", 5, 1, 6);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, "(", 9, 1, 10);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, ")", 10, 1, 11);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, "{", 11, 1, 12);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, IDENTIFIER, "int", 16, 2, 4);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, IDENTIFIER, "x", 20, 2, 8);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, "=", 21, 2, 9);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, NUMBER, "5", 22, 2, 10);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, ";", 23, 2, 11);
	assert(tokenList->next != NULL);

	tokenList = tokenList->next;
	assert_compare(tokenList, SEPARATOR, "}", 26, 4, 1);
	assert(tokenList->next == NULL);

}

void testParse() {

	testParse1();

}

void test_all(void) {
	printf("Tests ...\n");

	testNewToken();

	testParse();

	printf("\n\nTests OK\n");
}

