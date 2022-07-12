#include<stdio.h>


void parse(char fichier[]) {

	printf("fichier: %s\n",fichier);

}


void start(int argc, char* argv[]) {

	printf("Coucou\n");

	parse("exemples\\test1.ci");

}