#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define N 10

/*
 * 1) realloc'и для размера на 1 больше - это жестко, т.к. всё, что связано с выделением памяти на куче - это долго.
 * обычно в подобных случаях увеличивают заправшиваемый размер экспоненциально (например, в 2 раза): считываете, пока строку не забили ...
 * реаллокнули в 2 раза ... снова считываете ...
 * 2) родительский процесс после запуска новой задачи ждёт её завершения и только потом запускает следующую ... то есть времена запусков точно неправильные. 
 */

int Split(char* string, char*** tokens, int* sleepTime);
int GetNumberOfPrograms(FILE* stream);
void Fgetstr(FILE* stream, char** string); 
char** Commands(FILE* stream);

int main() {
	int status;
	FILE* file = fopen("inp.txt", "r");
	int i;	
	int n = GetNumberOfPrograms(file);
	char* command;
	char** commands;
	int sleepTime;
	int size;
	
	fgetc(file);
	for (i = 0; i < n; i++) {
		Fgetstr(file, &command);
		pid_t pid = fork();
		if (pid == 0) {
			Split(command, &commands, &sleepTime); 
			sleep(sleepTime);
			execvp(commands[1], commands + 1);
			exit(-1);
		}
		else {
			wait(&status);
		}
	}
	fclose(file);
	free(command);
	return 0;
}

int GetNumberOfPrograms(FILE* file) {
	int n;
	fscanf(file, "%d", &n);
	return n;
}

void Fgetstr(FILE* stream, char** string) {
	int c;
	
	*string = (char*) malloc(1);	
	*string[0] = '\0';
	while (c = fgetc(stream), c != 10 && c != EOF) {
		*string = (char*) realloc(*string, 2 + strlen(*string));		
		strcat(*string, (char*) &c);
	}
}

int Split(char* string, char*** tokens, int* sleepTime) {
	int j;
	char* token;

	*tokens = (char**) malloc(sizeof(char*));
	for (j = 0; ; j++, string = NULL) {
        if ((token = strtok(string, " ")) == NULL)        
			break;
		*tokens = (char**) realloc(*tokens, (j + 1)*sizeof(char*));
		(*tokens)[j] = (char*) realloc((*tokens)[j], strlen(token) + 1);
		strcpy((*tokens)[j], token);
	}
	*sleepTime = atoi((*tokens)[0]);
	return j;
}
