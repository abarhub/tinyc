#include<stdio.h>
#include <errno.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BUFFER (500)

enum TokenCode{IDENTIFIER,SEPARATOR,NUMBER};

typedef struct TokenStruct{
    enum TokenCode code;
	char *text;
    struct TokenStruct* next;
} Token;

char *copyStr(char * p) {
    if (p == NULL) {
        return NULL;
    }
    else {
        int len = strlen(p);
        char* buf = malloc(len);
        int i;
        for (i = 0; i < len; i++) {
            buf[i] = p[i];
        }
        buf[i] = '\0';
        return buf;
    }
}

Token* parse(char fichier[]) {

	printf("fichier: %s\n",fichier);

	FILE* file;
	int display;
    char str[MAX_BUFFER];
    Token *tokenList=NULL;

    file = fopen(fichier, "r");

    if (file == NULL) {
        printf("Cannot open file %s (errno=%d)\n", fichier, errno);
        exit(1);
    }

    while (fgets(str, MAX_BUFFER, file) != NULL) {

        for (int i = 0; i < MAX_BUFFER && str[i] != '\0'; i++) {
            char c = str[i];
            if (isalpha(c)) {
                char buf[MAX_BUFFER+1];
                int debut = i;
                buf[0] = c;
                //debut++;
                while (isalnum(str[i])&& i < MAX_BUFFER && str[i] != '\0') {
                    buf[i-debut] = str[i];
                    buf[i - debut+1] = '\0';
                    i++;
                }
                buf[i - debut] = '\0';
                printf("ident=%s!\n",buf);
                Token* tmp = NULL;
                tmp=calloc(1, sizeof(Token));
                if (tmp == NULL) {
                    printf("Erreur pour allouer de la mémoire\n");
                    exit(1);
                }
                tmp->code = IDENTIFIER;
                tmp->text = strdup(buf);
                tmp->next = tokenList;
                tokenList = tmp;
                printf("tmp->text:%s!\n", buf);
                printf("tmp->text2:%s!\n", tmp->text);
            }
            else if (isdigit(c)) {
                char buf[MAX_BUFFER + 1];
                int debut = i;
                buf[0] = c;
                while (isdigit(str[i]) && i < MAX_BUFFER && str[i] != '\0') {
                    buf[i - debut] = str[i];
                    buf[i - debut + 1] = '\0';
                    i++;
                }
                buf[i - debut] = '\0';
                Token* tmp = NULL;
                tmp = calloc(1, sizeof(Token));
                if (tmp == NULL) {
                    printf("Erreur pour allouer de la mémoire\n");
                    exit(1);
                }
                tmp->code = NUMBER;
                tmp->text = strdup(buf);
                tmp->next = tokenList;
                tokenList = tmp;
            }
            else if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                // on ignore
            } else {
                Token* tmp = NULL;
                char buf[2];
                buf[0] = c;
                buf[1] = '\0';
                tmp = calloc(1, sizeof(Token));
                if (tmp == NULL) {
                    printf("Erreur pour allouer de la mémoire\n");
                    exit(1);
                }
                tmp->code = SEPARATOR;
                tmp->text = strdup(buf);
                tmp->next = tokenList;
                tokenList = tmp;

                
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
        char* s = tokenList->text;
        //s = "toto";
        //if (s) {
        //    s[1] = '\0';
        //}
        printf("code:%d,str:%s!\n",tokenList->code,tokenList->text);
        tokenList = tokenList->next;
    }

}

void start(int argc, char* argv[]) {

	printf("Coucou\n");

    Token* tokenList = NULL;

    tokenList=parse("..\\..\\..\\exemples\\test1.ci");

    printToken(tokenList);

}