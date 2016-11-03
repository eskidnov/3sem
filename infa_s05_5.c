#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 100
#define N 2

struct Segment {
    int begin;
    int end;
    int index;
};

/*
 * По возможности стоит обходиться без глобальных переменных.
 */
int a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];

void* my_thread(void* arg) 
{
    struct Segment segment = *((struct Segment*)arg);
    int i, k, j; 
    for(i = segment.begin; i < segment.end; i++)
        for(k = 0; k < SIZE; k++)
            for(j = 0; j < SIZE; j++)
                c[i][j] += a[i][k] * b[k][j];
    return NULL;
}

int main()
{	
    pthread_t thread_id[N];
    int result;
    int i, j, k;
    FILE* file;
    struct Segment segments[N];

    srand(time(NULL));

    file = fopen("matrixA.txt", "w");
    for (i = 0; i < SIZE; i++) { 
        for (j = 0; j < SIZE; j++)
            fprintf(file,"%d ", rand() % 10);
        fprintf(file,"\n");
    }
    fclose(file);

    file = fopen("matrixB.txt", "w");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
            fprintf(file,"%d ", rand() % 10);
        fprintf(file,"\n");
    }
    fclose(file);
    
    for (i = 0; i < N; i++) {
        segments[i].index = i;
        segments[i].begin = i * SIZE / N;
        segments[i].end = segments[i].begin + SIZE / N;
    }

    file = fopen("matrixA.txt", "r");
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            fscanf(file,"%d", &a[i][j]);
    fclose(file);
	
    file = fopen("matrixB.txt", "r");		
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            fscanf(file ,"%d", &b[i][j]);
    fclose(file);

    clock_t begin = clock();
    for (i = 0; i < N - 1; i++) {
        result = pthread_create(&thread_id[i], (pthread_attr_t *)NULL, my_thread, &(segments[i]));
        if (result) {
            printf("Can`t create thread, returned value = %d\n" , result);
            exit(-1);
        }
    }

    /*
     * FIXIT: ничего страшного, что главная нить будет "бездельничать". Вполне нормально, если она
     * только join'ом будет заниматься. На производительность это почти нисколько не повлияет.
     * Зато код будет короче и без дублирования. Дублирование плохо, например, тем, что если вы в первом участке кода
     * допустили ошибку, потом его скопиравали ... потом вы найдете ошибку и нужно не забыть поправить ещё и во всех копиях
     * эту проблему.
     */
    for(i = segments[N - 1].begin; i < segments[N - 1].end; i++)
        for(k = 0; k < N; k++)
            for(j = 0; j < N; j++)
                c[i][j] += a[i][k] * b[k][j];
    for(i = 0; i < N; i++)
        pthread_join(thread_id[i], (void **) NULL);
    clock_t end = clock();
	
    file = fopen("matrixC.txt", "w");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
            fprintf(file,"%d ", c[i][j]);
        fprintf(file,"\n");
    }
    fclose(file);

    double time_spent = (double)(end - begin);
    printf("%d time = %f\n",N, time_spent);
	
    return 0;
}

