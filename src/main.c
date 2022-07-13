#include<stdio.h>
#include <errno.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"main.h"
#include"lexer.h"
#include"parser.h"


void start(int argc, char* argv[]) {

	printf("Coucou\n");

	Token* tokenList = NULL;

	tokenList = lexer("..\\..\\..\\exemples\\test1.ci");

	printToken(tokenList);

	ASTFunction* ast = parse(tokenList);

	printAst(ast);

}