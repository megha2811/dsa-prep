#include <stdio.h>
#include <stdlib.h>

// Add an element to the rear of queue
#define MAX_SIZE 5;
int queue_array[MAX_SIZE];
int rear = -1;
int front = -1;

// Check if the queue is empty
int isEmpty() {
    return (front == -1 && rear == -1);
}

// Check if the queue is full (for linear array)
int isFull() {
    return (rear == MAX_SIZE - 1);
}

void enqueueRear(int item){
    if (rear = MAX_SIZE - 1){
        printf("New element cannot be added at rear end of the queue!");
    }
    if (rear == -1){
        front = 0;
        rear = 0;
        queue_array[rear] = item
    }
    else{
        rear++;
        queue_array[rear] = item;
    }
    
}

void enqueueFront(int item){
    if (front == 0){
        printf("New element cannot be added at front of the queue!");
    }
    if(front == -1){
        front = 0;
        rear = 0;
        queue_array[front] = item;
    }
    else{
        front--;
        queue_array[front] = item;
    }   

}

int dequeueRear(){
    if (front == -1 && rear == -1){
        printf("Queue is empty");
        return -1;
    }
    if (front == 0 && rear == 0){
        int value = queue_array[rear]; 
        front = -1;
        rear = -1;
        return value;
    }
    else {
        int value = queue_array[rear];
        rear--;
        return value;
    } 
}

int dequeueFront(){
    if (front == -1 && rear == -1){
        printf("Queue is empty");
        return -1;
    }
    if (front == 0 && rear == 0){
        int value = queue_array[front];
        front = -1;
        rear = -1;
        return value;
    }
    else {
        int value = queue_array[front];
        front--;
        return value;
    }
}

int peekFront() {
    if (front == -1) {
        printf("Deque is empty\n");
        return -1;
    }
    return queue_array[front];
}

int peekRear() {
    if (rear == -1) {
        printf("Deque is empty\n");
        return -1;
    }
    return queue_array[rear];
}

int size() {
    if (isEmpty()) return 0;
    return (rear - front + 1);
}

void display() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue_array[i]);
    }
    printf("\n");
}