#include <stdio.h>
#include <stdlib.h>
#include "split.c"

void getGraphFromFile(FILE *f, int*** graph, int* n) {
    int i, j = 0;
    char** tokens;
    char s[1000];

    fgets(s, 1000, f);
    split(s, " ", &tokens, n);
    *graph = (int**) malloc(*n * sizeof(int*));
    for (i = 0; i < *n; i++) {
        (*graph)[i] = (int*) malloc(*n * sizeof(int));
        (*graph)[j][i] = atoi(tokens[i]);
    }
    while (fgets(s, 1000, f)) {
        j++;
        split(s, " ", &tokens, n);
        for (i = 0; i < *n; i++) {
            (*graph)[j][i] = atoi(tokens[i]);
        }
    } 
}
