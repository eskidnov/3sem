#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
#include "getGraphFromFile.c"

void BFS(int** graph, int n);

int main() {
    int elem;
    int** graph;
    int n;
    FILE *file = fopen("graph.txt", "r");
    getGraphFromFile(file, &graph, &n);    
    fclose(file);
    BFS(graph, n);
    return 0;
}

//НЕ РАБОТАЕТ
void BFS(int** graph, int n) {
    int j;
    int visited[10000];
    struct Queue q;
    
    //visited[0] = 1;
    push(&q, 0);
    printf("0\n");
    while (!isEmpty(q)) {
        j = 0;        
        if (!visited[front(q)]) {
            visited[front(q)] = 1;
            /*
             * у вас неправильная логика программы, поэтому и не работает.
             * давайте на семинаре обсудим.
             */
            while ((!graph[front(q)][j] || visited[j]) && j < n) {
                pop(&q);
                push(&q, j); 
                printf("%d\n", front(q));
                j++;
            }
        }
    }
    printf("\n");
}
