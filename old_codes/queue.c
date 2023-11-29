#include <stdio.h>
#define MAX 10000

struct Point {
    int x;
    int y;
};

int front = -1;
int rear = -1;
struct Point queue[MAX];

int IsEmpty(void) {
    return (front == rear);
}

int IsFull(void) {
    int tmp = (rear + 1) % MAX;
    return (tmp == front);
}

void addq(int x, int y) {
    if (IsFull())
        printf("Queue is Full.\n");
    else {
        rear = (rear + 1) % MAX;
        queue[rear].x = x;
        queue[rear].y = y;
    }
}

struct Point deleteq() {
    struct Point emptyPoint = {0, 0}; // Default values if the queue is empty

    if (IsEmpty()) {
        printf("Queue is Empty.\n");
        return emptyPoint;
    } else {
        front = (front + 1) % MAX;
        return queue[front];
    }
}

