#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "main.h"
#include "lexer.h"
#include "parser.h"
#include "run.h"

#if defined(_MSC_VER)
#include <direct.h>
#define getcwd _getcwd
#elif defined(__GNUC__)
#include <unistd.h>
#endif

bool file_exists(char *filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

char *findFile(char *filename)
{
	for (int j = 0; j < 5; j++)
	{
		char buf[2000] = "";
		for (int i = 0; i < j; i++)
		{
			strcat(buf, "../");
		}
		strcat(buf, "exemples/");
		strcat(buf, filename);
		if (file_exists(buf))
		{
			printf("find file: %s\n",buf);
			return strdup(buf);
		}
	}

	return NULL;
}

void getCurrentDirectory(){
	char cwd[500];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
}

void start(int argc, char *argv[])
{

	printf("Coucou\n");

	Token *tokenList = NULL;

	getCurrentDirectory();

	char *filename;
	char *file;
	filename = "test1.ci";
	filename = "test2.ci";

	//filename = "../../exemples/test2.ci";

	// file= "..\\..\\..\\exemples\\test1.ci";
	// file = "..\\..\\..\\exemples\\test2.ci";
	file = findFile(filename);
	assert(file != NULL);

	tokenList = lexer(file);

	printToken(tokenList);

	ASTFunction *ast = parse(tokenList);

	printAst(ast);

	run(ast);
}