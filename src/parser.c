#include<stdio.h>
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

void error(char* messageError) {
	printf("Erreur: %s\n", messageError);
	exit(1);
}

bool isType(Token* tokenList) {
	if (tokenList != NULL && tokenList->code == IDENTIFIER) {
		if (strcmp(tokenList->text, "void") == 0 ||
			strcmp(tokenList->text, "int") == 0) {
			return true;
		}
	}
	return false;
}

Token* next(Token* tokenList) {
	if (tokenList != NULL) {
		return tokenList->next;
	}
	else {
		return NULL;
	}
}

Token* parseExpr(Token* tokenList, ASTInstr* instr) {
	assert(tokenList != NULL);
	Token* current = tokenList;

	if (current->code == NUMBER) {
		int n = atoi(current->text);
		ASTExpr* expr = malloc(sizeof(ASTExpr));
		expr->value = n;
		instr->expr;
		current = next(current);
	}
	return current;
}

Token* parseInstr(Token* tokenList, ASTFunction* funct) {
	assert(tokenList != NULL);
	Token* current = tokenList;
	if (current->code == IDENTIFIER) {
		if (isType(current)) {
			current = next(current);
		}
	}
	if (current->code == IDENTIFIER) {
		char* name = current->text;
		ASTInstr* instr = malloc(sizeof(ASTInstr));
		instr->var = name;
		instr->expr = NULL;
		instr->next = NULL;
		current = next(current);
		current = parseExpr(instr, current);
	}

	return current;
}

ASTFunction* parse(Token* tokenList) {
	assert(tokenList != NULL);
	Token* current = tokenList;

	if (isType(current)) {
		current = next(current);
		if (current->code == IDENTIFIER) {
			char* name = current->text;
			ASTFunction* funct = malloc(sizeof(ASTFunction));
			funct->name = name;
			funct->next = NULL;
			funct->instr = NULL;
			current = next(current);
			if (current->code == SEPARATOR && current->subCode == SC_OPEN_PARENTHESIS) {
				current = next(current);
				if (current->code == SEPARATOR && current->subCode == SC_CLOSE_PARENTHESIS) {
					current = next(current);
					if (current->code == SEPARATOR && current->subCode == SC_OPEN_EMBRACE) {
						current = next(current);
						current = parseInstr(current, funct);
					}
				}
			}
		}
		else {
			error("erreur");
		}
	}
	else {
		error("erreur");
	}

}

void printAst(ASTFunction* funct) {
	assert(funct != NULL);

	printf("function: %s\n", funct->name);
}
