#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"../src/main.h"
#include"../src/lexer.h"
#include"../src/parser.h"

void testInterpreter1() {

	printf("testInterpreter1\n");

	Token* tokenList = NULL;

	tokenList = lexer("..\\..\\..\\test\\test1.ci");

	assert(tokenList != NULL);

	ASTFunction* ast = parse(tokenList);

	assert(ast != NULL);

	run(ast);
}

void test_all_interpreter(void) {
	printf("test_all_interpreter\n");
	testInterpreter1();

}