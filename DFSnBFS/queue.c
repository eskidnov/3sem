#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10000

struct Queue {
    int head;
    int tail;
    int data[MAX_QUEUE_SIZE];
};

int isEmpty(struct Queue queue) {
    return queue.head == queue.tail ? 1 : 0;
}
void push(struct Queue* queue, int element) {
    if ((queue->tail + 1) % MAX_QUEUE_SIZE == queue->head) {
        printf("Queue is full!\n");
        exit(-1);
    }
    else {
        queue->tail %= MAX_QUEUE_SIZE;
        queue->data[queue->tail ++] = element;
    }
}
int pop(struct Queue* queue) {
    int temp;

    if (isEmpty(*queue)) {
        printf("Queue is empty!\n");
        exit(-1);
    } else {
        temp = queue->data[queue->head];
        if (MAX_QUEUE_SIZE == queue->head)
            queue->head = 0;
        else
            queue->head ++;
        return temp;
    }   
}
int front(struct Queue queue) {
    return queue.data[queue.head];
}
int back(struct Queue queue) {
    return queue.data[queue.tail - 1];
}
