#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define N 10

void Split(char* string, char*** tokens, int* sleepTime);
int NumberOfPrograms(FILE* stream);
void fgetstr(FILE* stream, char** string); 
char** Commands(FILE* stream);

int main() {
	int status;	
	FILE* file = fopen("inp.txt", "r");
	int i;	
	int n = NumberOfPrograms(file);
	char* command;
	char** commands;
	int sleepTime;
	
	fgetc(file);
	for (i = 0; i < n; i++) {
		fgetstr(file, &command);
		pid_t pid = fork();
		if (pid == 0) {
			Split(command, &commands, &sleepTime); 
			sleep(sleepTime);
			execvp(commands[1], commands+1);
		}
	}
	fclose(file);

	return 0;
}

int NumberOfPrograms(FILE* file) {
	int n;
	fscanf(file, "%d", &n);
	return n;
}

void fgetstr(FILE* stream, char** string) {
	int c;
	
	*string = (char*) malloc(1);	
	*string[0] = '\0';
	while (c = fgetc(stream), c != 10 && c != EOF) {
		*string = (char*) realloc(*string, 2 + strlen(*string));		
		strcat(*string, (char*) &c);
	}
}

void Split(char* string, char*** tokens, int* sleepTime) {
	int j;
	char* token;

	*tokens = (char**) malloc(sizeof(char*));
	for (j = 0; ; j++, string = NULL) {
        if ((token = strtok(string, " ")) == NULL)        
			break;
		*tokens = (char**) realloc(*tokens, (j+1)*sizeof(char*));
		(*tokens)[j] = (char*) malloc(1);
		(*tokens)[j] = (char*) realloc((*tokens)[j], strlen(token)+1);
		strcpy((*tokens)[j], token);
	}
	*sleepTime = atoi((*tokens)[0]);
}
