#include<stdio.h>
#include <stdarg.h>
#include <errno.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include"main.h"
#include"lexer.h"
#include"parser.h"
#include"run.h"

SymbolTable* find(SymbolTable* symbolTable, char* name) {
	if (symbolTable == NULL) {
		return NULL;
	}
	else {
		while (symbolTable == NULL) {
			if (strcmp(symbolTable->name, name) == 0) {
				return symbolTable;
			}
			symbolTable = symbolTable->next;
		}
	}
}

void runFunct(ASTFunction* funct) {


	ASTInstr* instr = funct->instr;
	SymbolTable* symbolTable = NULL;
	while (instr != NULL) {

		if (instr->declare != NULL) {
			SymbolTable* tmp;
			SymbolTable* found = find(symbolTable, instr->var);
			if (found == NULL) {
				tmp = malloc(sizeof(SymbolTable));
				tmp->next = symbolTable;
				symbolTable = tmp;
			}
			else {
				tmp = found;
			}

			tmp->name = instr->var;
			tmp->type = instr->declare;
			tmp->value.code = EXPR_INT;
			tmp->value.u.value = 0;
		}

		if (instr->var != NULL) {
			SymbolTable* found = find(symbolTable, instr->var);
			if (found == NULL) {
				error(NULL, "can't find variable '%s'", instr->expr->u.var);
			}
		}

		if (instr->expr != NULL) {
			switch (instr->expr->code) {
			case EXPR_INT:
			{
				int n = instr->expr->u.value;
				printf("var %s=%d\n", instr->var, n);
			}
			break;
			case EXPR_VAR:
			{
				SymbolTable* found = find(symbolTable, instr->expr->u.var);
				if (found == NULL) {
					error(NULL, "can't find variable '%s'", instr->expr->u.var);
				}
			}
			break;
			}
		}

		instr = instr->next;
	}

}

void run(ASTFunction* ast) {
	assert(ast != NULL);


	while (ast != NULL) {
		printf("function: %s %s()\n", ast->returnType->name, ast->name);
		if (strcmp(ast->name, "main") == 0) {
			runFunct(ast);
		}

		/*ASTInstr* instr = funct->instr;
		while (instr != NULL) {

			if (instr->declare != NULL) {
				printf("%s ", instr->declare->name);
			}
			printf("%s=", instr->var);
			switch (instr->expr->code) {
			case EXPR_INT:
				printf("%d", instr->expr->u.value);
				break;
			case EXPR_VAR:
				printf("%s", instr->expr->u.var);
				break;
			}
			printf(";\n");

			instr = instr->next;
		}

		printf("}\n");*/
		ast = ast->next;

	}
}
