#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_LIMIT 10

struct work {
    char type[20];     // Type of dishes
    float time;       // Time to work
};

struct dirty {
    char type[20];     // Type of dishes
    int amount;     // Amount of dirty dishes
};

void sem(int a, int b);
void split(char* string, char* delimiters, char*** tokens, int* count);

struct sembuf mybuf;
int semid;

int main() {
    const char pathname[] = "wiper.txt"; 
    key_t key;
    int fd[2];
    char buffer[1000];
    int i, j;   
    char** tokens = (char **)malloc(50 * sizeof(char*));
	for (i = 0; i < 50; i++)
		tokens[i] = (char *)malloc(20 * sizeof(char));

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key, 2, 0666 | IPC_CREAT)) < 0) {
        printf("Can`t get semid\n");
        exit(-1);
    }
	
    sem(0, TABLE_LIMIT - 1);
    
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {     // washer     
        int dirt = open("dirty.txt", O_RDONLY);
        int wash = open("washer.txt", O_RDONLY);
        int washerAbilities, taskNum;
        struct work washer[20];
        struct dirty task[20];
        int n;        
        char** tokens2 = (char **)malloc(50 * sizeof(char*));
        for (i = 0; i < 50; i++)
	        tokens2[i] = (char *)malloc(20 * sizeof(char));

		close(fd[0]);
        read(wash, (char*)buffer, 1000);
        close(wash); 
        split(buffer, ":\n", &tokens, &washerAbilities);
        washerAbilities /= 2;
        for (i = 0; i < washerAbilities; i++) {
            strcpy(washer[i].type, tokens[2 * i]);
            washer[i].time = atof(tokens[2 * i + 1]);
        }   
        read(dirt, (char*)buffer, 1000);
        close(dirt);
        split(buffer, ":\n", &tokens2, &taskNum);
        taskNum /= 2;
        for (i = 0; i < taskNum; i++) {
            strcpy(task[i].type, tokens2[2 * i]);
            task[i].amount = atoi(tokens2[2 * i + 1]);
        }
        for (i = 0; i < taskNum; i++) {
            for (j = 0; j < washerAbilities; j++)
                if (strcmp(task[i].type, washer[j].type) == 0) {
                    n = j;
                    break;
                }
            for (j = 0; j < task[i].amount; j++) {
                sleep(washer[n].time);
                write(fd[1], (char*)task[i].type, strlen(task[i].type));
                printf("%s is washed for %f sec\n",
                       task[i].type, washer[n].time);
                sem(1, 1);                
                sem(0, -1);
            }
        }
	} else {            // wiper
        int wipe = open("wiper.txt", O_RDONLY);
        struct work wiper[20];
        int wiperAbilities;
        char task[20];
        int n;

		close(fd[1]);
        read(wipe, (char*)buffer, 1000);
        close(wipe); 
        split(buffer, ":\n", &tokens, &wiperAbilities);
        wiperAbilities /= 2;
        for (i = 0; i < wiperAbilities; i++) {
            strcpy(wiper[i].type, tokens[2 * i]);
            wiper[i].time = atof(tokens[2 * i + 1]);
        }
        sem(1, -1);
        while (1) {
            read(fd[0],	(char*)task, 20);
            for (j = 0; j < wiperAbilities; j++)
                if (strcmp(task, wiper[j].type) == 0) {
                    n = j;
                    break;
                }
            sem(0, 1);                
            sleep(wiper[n].time);
            printf("%s is wiped for %f sec\n", task, wiper[n].time);
            sem(1, -1);
        }
	}

    return 0;    
}

void sem(int a, int b) {
    mybuf.sem_op = b;
    mybuf.sem_flg = 0;
    mybuf.sem_num = a;
    if (semop(semid, &mybuf, 1) < 0)
        printf("plok\n");
}

/*void split(char* string, char* delimiters, char*** tokens, int* tokensAmount) {
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
    *tokensAmount = j;
}*/
void split(char* string, char* delimiters, char*** tokens, int* count)
{
	char* tmp = (char *)malloc(20 * sizeof(char));
	int i;
	tmp = strtok(string, delimiters);
	strcpy((*tokens)[0], tmp);
	i = 1;
	while (tmp != NULL) 
	{
		tmp = strtok(NULL, delimiters);
		if (tmp != NULL)
			strcpy((*tokens)[i], tmp);
		i++;
	}
	*count = i - 1;
	free(tmp);
}
