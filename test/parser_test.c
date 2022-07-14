#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"../src/main.h"
#include"../src/lexer.h"
#include"../src/parser.h"


void testParser1() {

	printf("testParser1\n");

	Token* tokenList = NULL;

	tokenList = lexer("..\\..\\..\\test\\test1.ci");

	ASTFunction* ast = parse(tokenList);

	assert(ast != NULL);

	printAst(ast);

	assert(strcmp(ast->name, "main") == 0);
	assert(ast->instr != NULL);
	assert(ast->returnType != NULL);
	assert(ast->next == NULL);

	ASTInstr* instr = ast->instr;
	assert(strcmp(instr->var, "x") == 0);
	assert(instr->declare != NULL);
	assert(instr->declare->code == TYPE_INT);
	assert(strcmp(instr->declare->name, "int") == 0);
	assert(instr->expr != NULL);
	assert(instr->expr->code == EXPR_INT);
	assert(instr->expr->u.value == 5);
	assert(instr->next == NULL);
}

void test_all_parser(void) {
	printf("test_all_parser\n");
	testParser1();

}