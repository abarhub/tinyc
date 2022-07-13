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

void error(Token* token, char* messageError, ...) {
	va_list args;

	char* str = "Error: ";
	if (token == NULL) {
		strcat(str, messageError);
	}
	else {
		str = messageError;
		char* buf = malloc(100);
		sprintf(buf, " (pos:%d,line:%d,column:%d)", token->pos, token->line, token->column);
		strcat(str, buf);
	}

	va_start(args, messageError);
	vfprintf(stderr, str, args);
	va_end(args);

	exit(1);
}

bool isType(Token* tokenList) {
	if (tokenList != NULL && tokenList->code == IDENTIFIER) {
		if (strcmp(tokenList->text, "void") == 0 ||
			strcmp(tokenList->text, "int") == 0 ||
			strcmp(tokenList->text, "string") == 0) {
			return true;
		}
	}
	return false;
}

bool isSeparator(Token* tokenList, enum TokenSubCode separator) {
	if (tokenList != NULL && tokenList->code == SEPARATOR &&
		tokenList->subCode == separator) {
		return true;
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
		expr->code = EXPR_INT;
		expr->u.value = n;
		instr->expr = expr;
		current = next(current);
	}
	else if (current->code == IDENTIFIER) {
		ASTExpr* expr = malloc(sizeof(ASTExpr));
		expr->code = EXPR_VAR;
		expr->u.var = current->text;
		instr->expr = expr;
		current = next(current);
	}
	else {
		error(tokenList, "invalid token (expression expected): '%d'", current->code);
	}
	return current;
}

ASTType* parseType(Token** tokenList) {
	assert(tokenList != NULL);
	if (isType(*tokenList)) {
		char* name = (*tokenList)->text;
		enum TypeCode code;
		if (strcmp(name, "int") == 0) {
			code = TYPE_INT;
		}
		else if (strcmp(name, "string") == 0) {
			code = TYPE_STRING;
		}
		else if (strcmp(name, "void") == 0) {
			code = TYPE_VOID;
		}
		else {
			error(*tokenList, "invalid type: '%s'", name);
		}
		ASTType* res = malloc(sizeof(ASTType));
		res->code = code;
		res->name = name;
		*tokenList = next(*tokenList);
		return res;
	}
	else {
		error(*tokenList, "type attendu");
	}
	return NULL;
}

Token* parseInstr(Token* tokenList, ASTFunction* funct) {
	assert(tokenList != NULL);
	Token* current = tokenList;
	ASTType* declare = NULL;
	if (current->code == IDENTIFIER) {
		if (isType(current)) {
			declare = parseType(&current);
		}
	}
	if (current->code == IDENTIFIER) {
		char* name = current->text;
		ASTInstr* instr = malloc(sizeof(ASTInstr));
		if (instr == NULL) {
			error(current, "error for malloc");
		}
		instr->var = name;
		instr->declare = declare;
		instr->expr = NULL;
		instr->next = NULL;
		if (funct->instr == NULL) {
			funct->instr = instr;
		}
		else {
			ASTInstr* lastInstr = funct->instr;
			assert(lastInstr != NULL);
			while (lastInstr->next != NULL) {
				lastInstr = lastInstr->next;
			}
			assert(lastInstr != NULL);
			assert(lastInstr->next == NULL);
			lastInstr->next = instr;
		}
		current = next(current);
		if (current->code == SEPARATOR && current->subCode == SC_ASSIGNEMENT) {
			current = next(current);
			current = parseExpr(current, instr);
		}
		if (current && current->code == SEPARATOR && current->subCode == SC_SEMICOLON) {
			current = next(current);
		}
		else {
			error(current, "invalid token (';' expected): '%d'", current->code);
		}
	}
	else {
		error(current, "invalid token (instruction): '%d'", current->code);
	}

	return current;
}

ASTFunction* parse(Token* tokenList) {
	assert(tokenList != NULL);
	Token* current = tokenList;
	ASTFunction* firstFunct = NULL;

	if (isType(current)) {
		ASTType* returnType = parseType(&current);
		if (current->code == IDENTIFIER) {
			char* name = current->text;
			ASTFunction* funct = malloc(sizeof(ASTFunction));
			funct->name = name;
			funct->returnType = returnType;
			funct->next = NULL;
			funct->instr = NULL;
			firstFunct = funct;
			current = next(current);
			if (current->code == SEPARATOR && current->subCode == SC_OPEN_PARENTHESIS) {
				current = next(current);
				if (current->code == SEPARATOR && current->subCode == SC_CLOSE_PARENTHESIS) {
					current = next(current);
					if (current->code == SEPARATOR && current->subCode == SC_OPEN_EMBRACE) {
						current = next(current);
						while (current != NULL && !isSeparator(current, SC_CLOSE_EMBRACE)) {
							current = parseInstr(current, funct);
						}
					}
				}
			}
		}
		else {
			error(current, "erreur: identifieur attendu");
		}
	}
	else {
		error(current, "erreur: type attendu");
	}

	return firstFunct;
}

void printAst(ASTFunction* funct) {
	assert(funct != NULL);

	while (funct != NULL) {
		printf("function: %s %s(){\n", funct->returnType->name, funct->name);

		ASTInstr* instr = funct->instr;
		while (instr != NULL) {

			if (instr->declare != NULL) {
				printf("%s ", instr->declare->name);
			}
			printf("%s", instr->var);
			if (instr->expr != NULL) {
				printf("=");
				switch (instr->expr->code) {
				case EXPR_INT:
					printf("%d", instr->expr->u.value);
					break;
				case EXPR_VAR:
					printf("%s", instr->expr->u.var);
					break;
				}
			}
			printf(";\n");

			instr = instr->next;
		}

		printf("}\n");
		funct = funct->next;

	}
}
