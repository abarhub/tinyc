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

void runFunct(ASTFunction* funct) {

	//printf("function: %s %s(){\n", funct->returnType->name, funct->name);

	ASTInstr* instr = funct->instr;
	while (instr != NULL) {

		if (instr->declare != NULL) {
			//printf("%s ", instr->declare->name);
		}

		//printf("%s=", instr->var);
		switch (instr->expr->code) {
		case EXPR_INT:
			//printf("%d", instr->expr->u.value);
			{	
				int n = instr->expr->u.value;
				printf("n=%d\n", n);
			}
			break;
		case EXPR_VAR:
			//printf("%s", instr->expr->u.var);
			break;
		}
		//printf(";\n");

		instr = instr->next;
	}

	//printf("}\n");
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
