#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount);
char* InputString(char** string);


int main() {
	char* s = "\0";
	char delimiters[] = " ;";
	char** tokens;
	int num;
	int i;
	
	printf("%s", InputString(&s));
	/*Split(s, delimiters, &tokens, &num);
	for(i = 0; i < num; i++) {
		printf("%s\n", *(tokens+i));
	}*/

	return 0;
}


char* InputString(char** string) {
	/*int stringSize = 0;
	char c;
	
	do {
		*string = (char*) realloc(*string, stringSize+1);
		c = getchar();		
		(*string)[stringSize] = c;
		stringSize++;
	}
	while (c != '\n');
	(*string)[stringSize] = '\0';*/
	
	char s[256];
	char* p = s;
	int n = 0;
	
	while ((*p++=getchar ()) != '\n')
		if (++n == 255) {
			n = 0;
			*p = '\0';
			strcat(*string, s);
			p = s;
		}
	if (*p != 'v') {
		*p = '\0';
		*string = (char*) malloc(strlen(s));
		strcat(*string, s);
	}

	return *string;
}


void Split(char* string, char* delimiters, char*** tokens, int* tokensCount) {
	int j;
	char* token;
	char* saveptr;
	
	for (j = 0; ; j++, string = NULL) {
    	token = strtok_r(string, delimiters, &saveptr);
        if (token == NULL)
        	break;
		//*tokens = (char**) realloc(*tokens, sizeof(char*));
		//strcpy(*(*tokens+j), token);
		printf("%d", j);
	}
	//*tokensCount = j;
}
