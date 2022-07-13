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
#include"run.h"


void start(int argc, char* argv[]) {

	printf("Coucou\n");

	Token* tokenList = NULL;

	char* file;
	file= "..\\..\\..\\exemples\\test1.ci";
	file = "..\\..\\..\\exemples\\test2.ci";

	tokenList = lexer(file);

	printToken(tokenList);

	ASTFunction* ast = parse(tokenList);

	printAst(ast);

	run(ast);

}