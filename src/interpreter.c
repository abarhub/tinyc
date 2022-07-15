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
#include"interpreter.h"

SymbolTable* find(SymbolTable* symbolTable, char* name) {
	assert(name != NULL);
	if (symbolTable == NULL) {
		return NULL;
	}
	else {
		while (symbolTable != NULL) {
			if (strcmp(symbolTable->name, name) == 0) {
				return symbolTable;
			}
			symbolTable = symbolTable->next;
		}
		return NULL;
	}
}

int getIntValue(ASTExpr* expr, SymbolTable* symbolTable) {
	assert(expr != NULL);
	assert(symbolTable != NULL);
	int n;
	if (expr->code == EXPR_INT) {
		n = expr->u.value;
	}
	else if (expr->code == EXPR_VAR) {
		SymbolTable* found = find(symbolTable, expr->u.var);
		if (found == NULL) {
			error(NULL, "can't find variable '%s'", expr->u.var);
		}
		n = found->value.u.value;
	}
	else {
		error(NULL, "expression not implemented");
	}
	return n;
}

SymbolTable* declareVar(SymbolTable** symbolTable, char* var, ASTType* type) {
	assert(symbolTable != NULL);
	assert(var != NULL);
	assert(type != NULL);
	SymbolTable* tmp;
	SymbolTable* found = find(*symbolTable, var);
	if (found == NULL) {
		tmp = malloc(sizeof(SymbolTable));
		tmp->next = *symbolTable;
		*symbolTable = tmp;
	}
	else {
		error(NULL, "var '%s' already declared", var);
	}

	tmp->name = var;
	tmp->type = type;
	switch (type->code) {
	case TYPE_INT:
		tmp->value.code = EXPR_INT;
		tmp->value.u.value = 0;
		break;
	case TYPE_STRING:
		tmp->value.code = EXPR_STRING;
		tmp->value.u.str = strdup("");
		break;
	default:
		error(NULL, "invalide type '%s' (%d)",
			type->name, type->code);
	}

}

void runFunct(ASTFunction* funct) {


	ASTInstr* instr = funct->instr;
	SymbolTable* symbolTable = NULL;
	SymbolTable* foundVar = NULL;
	while (instr != NULL) {

		if (instr->code == INSTR_DECLARE) {
			if (instr->declare != NULL) {
				declareVar(&symbolTable, instr->var, instr->declare);
			}
		}
		else if (instr->code == INSTR_AFFECT) {
			if (instr->declare != NULL) {
				declareVar(&symbolTable, instr->var, instr->declare);
			}

			if (instr->var != NULL) {
				foundVar = find(symbolTable, instr->var);
				if (foundVar == NULL) {
					error(NULL, "can't find variable '%s'", instr->expr->u.var);
				}

				if (instr->expr != NULL) {
					switch (instr->expr->code) {
					case EXPR_INT:
					{
						int n = instr->expr->u.value;
						printf("var %s=%d\n", instr->var, n);
						if (foundVar != NULL) {
							foundVar->value.code = RUN_EXPR_INT;
							foundVar->value.u.value = n;
						}
					}
					break;
					case EXPR_VAR:
					{
						SymbolTable* found = find(symbolTable, instr->expr->u.var);
						if (found == NULL) {
							error(NULL, "can't find variable '%s'", instr->expr->u.var);
						}
						if (foundVar != NULL) {
							foundVar->value.code = found->value.code;
							foundVar->value.u.value = found->value.u.value;
						}
						printf("var %s=%d\n", instr->var, found->value.u.value);
					}
					break;
					case EXPR_ADDI:
					{
						int n1 = 0, n2 = 0;
						n1 = getIntValue(instr->expr->u.left, symbolTable);
						n2 = getIntValue(instr->expr->u.right, symbolTable);
						int res = n1 + n2;
						printf("var %s=%d\n", instr->var, res);
						foundVar->value.code = RUN_EXPR_INT;
						foundVar->value.u.value = res;
					}
					break;
					case EXPR_STRING:
					{
						char * str = instr->expr->u.str;
						printf("var %s=\"%s\"\n", instr->var, str);
						if (foundVar != NULL) {
							foundVar->value.code = RUN_EXPR_STR;
							foundVar->value.u.str= str;
						}
					}
					break;
					default:
						error(NULL, "invalide expression (%d)", instr->expr->code);
					}
				}
			}

		}
		else if (instr->code == INSTR_CALL) {
			printf("call %s\n", instr->var);
			if (strcmp(instr->var, "print") == 0) {
				int n = getIntValue(instr->expr, symbolTable);
				printf("value: %d\n", n);
			}
			else {
				error(NULL, "invalid methode '%s'", instr->var);
			}
		}
		else {
			error(NULL, "invalid instruction '%s'", instr->code);
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

		ast = ast->next;

	}
}
