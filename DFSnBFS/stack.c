/*
    sp - Stack pointer
    psp - Pointer on stack pointer
*/
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int num;
    struct Stack *next;
};

int isEmpty(struct Stack *sp) {
    return sp == NULL ? 1 : 0;
}

void push(struct Stack **psp, int data) {
    struct Stack *temp;

    temp = (struct Stack *) malloc(sizeof(struct Stack));
    if (temp == NULL) {
        printf("Stack is full!\n");
        exit(-1);
    } else {
        temp->num = data;
        temp->next = *psp;
        *psp = temp;
    }
}

int pop(struct Stack **psp) {
    struct Stack *temp;
    int data;
    
    if (isEmpty(*psp)) {
        printf("Stack is empty!\n");
        exit(-1);
    } else {
        temp = *psp;
        data = temp->num;
        *psp = temp->next;
        free(temp);
        return data;
    }
}

int top(struct Stack *sp) {
    if (!isEmpty(sp))
        return sp->num;
    else {
        printf("Stack is empty!\n");
        exit(-1);
    }
}
