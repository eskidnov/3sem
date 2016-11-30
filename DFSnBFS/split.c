#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split(char* string, char* delimiters, char*** tokens, int* tokensCount) {
	int j;
	char* token;

	*tokens = (char**) malloc(sizeof(char*));
	for (j = 0; ; j++, string = NULL) {
        if ((token = strtok(string, delimiters)) == NULL)        
			break;
		*tokens = (char**) realloc(*tokens, (j + 1) * sizeof(char*));
		(*tokens)[j] = (char*) realloc((*tokens)[j], strlen(token) + 1);
		strcpy((*tokens)[j], token);
	}
	*tokensCount = j;
}
