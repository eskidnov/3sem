#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount);
char* InputString(char** string);


int main() {
	char* s;
	char* delimiters;
	char** tokens;
	int num;
	int i;
	
	printf("> Write delimiter(s):\n");
	InputString(&delimiters);
	printf("> Write a string:\n");
	Split(InputString(&s), delimiters, &tokens, &num);
	printf("> All words from the string:\n");
	for(i = 0; i < num; i++)
		printf("> %d: %s\n", i+1, tokens[i]);

	return 0;
}


char* InputString(char** string) {
	char c;
	
	*string = (char*) malloc(1);
	(*string)[0] = '\0';
	while ((c = getchar()) != '\n') {
		*string = (char*) realloc(*string, 2+strlen(*string));
		strcat(*string, &c);
		(*string)[strlen(*string)] = '\0';		
	}	

	return *string;
}


void Split(char* string, char* delimiters, char*** tokens, int* tokensCount) {
	int j;
	char* token;

	*tokens = (char**) malloc(sizeof(char*));
	for (j = 0; ; j++, string = NULL) {
        if ((token = strtok(string, delimiters)) == NULL)        
			break;
		*tokens = (char**) realloc(*tokens, (j+1)*sizeof(char*));
		(*tokens)[j] = (char*) malloc(1);
		(*tokens)[j] = (char*) realloc((*tokens)[j], strlen(token)+1);
		strcpy((*tokens)[j], token);
	}
	*tokensCount = j;
}
