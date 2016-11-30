#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

struct node {
    int num;
    struct node *lson, *rson;
};

void insert(struct node **ptp, int data);
int search(struct node **ptp, int data);
void inOrder(struct node **ptp);

int main() {
    struct node *tp = NULL;
    int elem;
    int i;

    srand((unsigned int)time(NULL));
    for(i = 0; i < N; i++) {
        insert(&tp, rand() % 100 + 1);
    }
    scanf("%d", &elem);
    printf("%d\n", search(&tp, elem));
    inOrder(&tp);

    return 0;
}

void insert(struct node **ptp, int data) {
    struct node *temp;
    if (*ptp == NULL) {
        temp = (struct node *) malloc(sizeof(struct node));
        temp->num = data;
        temp->lson = NULL;
        temp->rson = NULL;
        *ptp = temp;
    }
    else if ((*ptp)->num < data) insert(&((*ptp)->lson), data);
    else insert(&((*ptp)->rson), data);
}

int search(struct node **ptp, int data) {
    if (*ptp == NULL) return 0;
    if (*ptp != NULL)
        if ((*ptp)->num == data) return 1;
        else if ((*ptp)->num < data) search(&((*ptp)->lson), data);
        else search(&((*ptp)->rson), data);
}

void inOrder(struct node **ptp) {
    if (*ptp != NULL) {
        if (&((*ptp)->rson) != NULL) inOrder(&((*ptp)->rson));
        printf("%d ", (*ptp)->num);
        if (&((*ptp)->lson) != NULL) inOrder(&((*ptp)->lson));
    }
}
