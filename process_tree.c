#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void InputTree(int** tree);
void MakeSpace(int width);

int main() {
	int* tree;
	int size;
	int i = 0;
	int status;
	int p = 0, pCopy = 0;
	int depth = 1;
	//Программа не работает! Есть подозрения, что ошибка
	printf("> Write process tree: ");
	InputTree(&tree);
	printf("> Your process tree:\n");
	printf("pid: %d\n", getpid());	
	while (i < tree[p]) {
		pid_t pid = fork();
		if (pid == 0) {
			MakeSpace(2*depth);
			printf("ppid: %d\n", getppid());
			MakeSpace(2*depth);
			printf("pid: %d\n", getpid());
			pCopy = p;			
			if (p != 0)
				p += tree[pCopy]; //здесь.
			else
				p = 1; 
			depth++;		
		}
		else { 
			i++;
			wait(&status);
			p = pCopy;
		}
	} 	
	return 0;
}

void InputTree(int** tree) {
	char n;
	int size = 0;
	int sum = 1;
	int i;
	
	*tree = (int*) malloc(1);
	while ((n = getchar()) != '\n') {
		*tree = (int*) realloc(*tree, (++size) * sizeof(int));
		(*tree)[size-1] = atoi(&n);
		sum += (*tree)[size-1];		
	}	
	*tree = realloc(*tree, sum * sizeof(int));
	for (i = size; i < sum; i++)
		(*tree)[size] = 0;
}

void MakeSpace(int width) {
	int i;
	for (i = 0; i < width; i++)
		printf(" ");
}
