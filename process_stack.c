#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void MakeSpace(int width);

int main() {
	int i = 0;
	int status;
	int n;
	scanf("%d", &n);
	printf("Process created: %d\n", getpid());	
	for (i = 0; i < n; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			MakeSpace(2 * (i+1));
			printf("Process created: %d\n", getpid());
			MakeSpace(2 * (i+1));			
			printf("My parent: %d\n", getppid());	
		}
		else { 
			wait(&status);
			MakeSpace(2 * i);
			printf("Child died\n");
			exit(-1); 
		}
	} 	
	return 0;
}

void MakeSpace(int width) {
	int i;
	for (i = 0; i < width; i++)
		printf(" ");
}
