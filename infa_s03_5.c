#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define N 10

void Split(char* string, char*** tokens, int* sleepTime);

/*
 * Некоторые стараются всегда добавлять глагол в название ф-й: GetNumberOfPrograms, GetCommands ...
 * Но в данное случае это вопрос дискуссионный и строгих правил нет.
 * Сами для себя решите, какой вариант вам кажется более понятным (вам дали чужой год, и вам надо в нем разобраться. в каком случае вы бы потратили меньше времени).
 */
int NumberOfPrograms(FILE* stream);

/*
 * Старайтесь называть ф-и единообразно. Если пишете каждое слово с заглавной буквы, то делайте это везде.
 */
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
			execvp(commands[1], commands + 1);
/*
 * FIXIT:
 * Представьте, что произойдет, если execvp не запустится (вернет ошибку) ...
 * Видимо, у вас дочерний процесс будет также участвовать в запуске задач. Надо как-то избежать такой ситуации.
 */
		}
	}
	fclose(file);

  /*
   * FIXIT:
   * Память нужно освобождать. В следующем семестре мы познакомся с "умными" указателями, которые позволяют не думать
   * про освобождение памяти, но сейчас это надо делать самим "вручную".
   */
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
		*tokens = (char**) realloc(*tokens, (j + 1)*sizeof(char*));
    /*
     * Зачем этот malloc(1) вам понадобился?
     */
		(*tokens)[j] = (char*) malloc(1);
    /*
     * FIXIT:
     * Ставьте пробеды вокруг бинарных операторов: strlen(token) + 1
     */
		(*tokens)[j] = (char*) realloc((*tokens)[j], strlen(token)+1);
		strcpy((*tokens)[j], token);
	}
	*sleepTime = atoi((*tokens)[0]);
}
