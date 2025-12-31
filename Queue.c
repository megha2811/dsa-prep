#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5 // Define the maximum size of the queue

int queue_array[MAX_SIZE];
int front = -1; //outside the queue
int rear = -1; //outside the queue


int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    printf("Dequeued element: %d\n", dequeue());
    display();
    enqueue(40);
    enqueue(50);
    enqueue(60); // This will show a Queue Overflow message
    display();
    return 0;
}

// Check if the queue is empty
int isEmpty() {
    return (front == -1 && rear == -1);
}

// Check if the queue is full (for linear array)
int isFull() {
    return (rear == MAX_SIZE - 1);
}

// Add an element to the queue
void enqueue(int item) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0; // Set front to 0 for the first element
    }
    rear++; 
    queue_array[rear] = item; 
    printf("Enqueued %d\n", item);
}

// Remove an element from the queue
int dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return -1; // Return -1 or handle error appropriately
    }
    int item = queue_array[front];
    if (front == rear) {
        front = -1; // Reset queue if it becomes empty after dequeue
        rear = -1;
    } else {
        front++;
    }
    return item;
}

// Display elements in the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue_array[i]);
    }
    printf("\n");
}

