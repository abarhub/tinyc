#include<stdio.h>
#include <errno.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"main.h"

#define MAX_BUFFER (2000)

Token* newToken(enum TokenCode code, char* text, int pos, int line, int column, Token* next) {
	assert(text != NULL);
	Token* tmp = calloc(1, sizeof(Token));
	if (tmp == NULL) {
		printf("Erreur pour allouer de la mémoire\n");
		exit(1);
	}
	tmp->code = code;
	tmp->text = strdup(text);
	tmp->next = next;
	tmp->pos = pos;
	tmp->line = line;
	tmp->column = column;
	return tmp;
}

Token* parse(char fichier[]) {

	printf("fichier: %s\n", fichier);

	FILE* file;
	int display;
	char str[MAX_BUFFER];
	Token* tokenList = NULL, * end = NULL;
	int pos = 0;
	int line = 1;
	int column = 1;

	file = fopen(fichier, "r");

	if (file == NULL) {
		printf("Cannot open file %s (errno=%d)\n", fichier, errno);
		exit(1);
	}

	while (fgets(str, MAX_BUFFER, file) != NULL) {

		for (int i = 0; i < MAX_BUFFER && str[i] != '\0'; i++) {
			char c = str[i];
			if (isalpha(c)) {
				char buf[MAX_BUFFER + 1];
				int debut = i;
				int len = 1;
				buf[0] = c;
				//debut++;
				while (i < MAX_BUFFER && str[i] != '\0' && isalnum(str[i])) {
					buf[i - debut] = str[i];
					buf[i - debut + 1] = '\0';
					i++;
					len++;
				}
				buf[i - debut] = '\0';
				printf("ident=%s!\n", buf);
				Token* tmp = newToken(IDENTIFIER, buf, pos, line, column, NULL);
				if (tokenList == NULL) {
					tokenList = tmp;
				}
				if (end == NULL) {
					end = tmp;
				}
				else {
					end->next = tmp;
					end = tmp;
				}
				printf("tmp->text:%s!\n", buf);
				printf("tmp->text2:%s!\n", tmp->text);
				pos += len - 1;
				column += len - 1;
				if (i < MAX_BUFFER && str[i] != '\0' && !isalnum(str[i])) {
					i--;
				}
			}
			else if (isdigit(c)) {
				char buf[MAX_BUFFER + 1];
				int debut = i;
				int len = 1;
				buf[0] = c;
				while (i < MAX_BUFFER && str[i] != '\0' && isdigit(str[i])) {
					buf[i - debut] = str[i];
					buf[i - debut + 1] = '\0';
					i++;
					len++;
				}
				buf[i - debut] = '\0';
				Token* tmp = newToken(NUMBER, buf, pos, line, column, NULL);
				if (tokenList == NULL) {
					tokenList = tmp;
				}
				if (end == NULL) {
					end = tmp;
				}
				else {
					end->next = tmp;
					end = tmp;
				}
				pos += len - 1;
				column += len - 1;
				if (i < MAX_BUFFER && str[i] != '\0' && !isdigit(str[i])) {
					i--;
				}
			}
			else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
				// on ignore
				if (c == '\n' || c == '\r') {
					if (c == '\n') {
						column = 1;
						line++;
					}
					pos++;
				}
				else {
					column++;
					pos++;
				}
			}
			else {
				Token* tmp = NULL;
				char buf[2];
				buf[0] = c;
				buf[1] = '\0';
				tmp = newToken(SEPARATOR, buf, pos, line, column, NULL);
				switch (c) {
				case ';':
					tmp->subCode = SC_SEMICOLON;
					break;
				case '(':
					tmp->subCode = SC_OPEN_PARENTHESIS;
					break;
				case ')':
					tmp->subCode = SC_CLOSE_PARENTHESIS;
					break;
				case '{':
					tmp->subCode = SC_OPEN_EMBRACE;
					break;
				case '}':
					tmp->subCode = SC_CLOSE_EMBRACE;
					break;
				case '=':
					tmp->subCode = SC_ASSIGNEMENT;
					break;

				}
				if (tokenList == NULL) {
					tokenList = tmp;
				}
				if (end == NULL) {
					end = tmp;
				}
				else {
					end->next = tmp;
					end = tmp;
				}

				pos++;
				column++;
			}

		}

		printf("%s", str);
	}

	// closes the file pointed by demo
	fclose(file);

	return tokenList;
}


void printToken(Token* tokenList) {
	while (tokenList != NULL) {
		printf("code:%d,str:%s,pos=%d,line:%d,col:%d,subcode:%d\n",
			tokenList->code, tokenList->text, tokenList->pos,
			tokenList->line, tokenList->column,
			tokenList->subCode);
		tokenList = tokenList->next;
	}
}

void start(int argc, char* argv[]) {

	printf("Coucou\n");

	Token* tokenList = NULL;

	tokenList = parse("..\\..\\..\\exemples\\test1.ci");

	printToken(tokenList);

}