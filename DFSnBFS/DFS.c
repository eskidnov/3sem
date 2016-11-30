#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include "getGraphFromFile.c"

void DFS(int** graph, int n);

int main() {
    int elem;
    int** graph;
    int n;
    FILE *file = fopen("graph.txt", "r");
    getGraphFromFile(file, &graph, &n);    
    fclose(file);
    DFS(graph, n);
    return 0;
}

void DFS(int** graph, int n) {
    int j;
    int visited[10000];
    struct Stack *sp;
    
    visited[0] = 1;
    push(&sp, 0);
    printf("0 ");
    while (!isEmpty(sp)) {
        j = 0;        
        while ((!graph[top(sp)][j] || visited[j]) && j < n) j++;
        if (j != n && !visited[j]) {
            visited[j] = 1;
            push(&sp, j); 
            printf("%d ", j);
        } else {
            pop(&sp);
        }
    }
    printf("\n");
}
