#include <stdio.h>

#define MAX_SIZE 5 // Define the maximum size of the stack

int stack[MAX_SIZE];
int top = -1; // Initialize top to -1 to indicate an empty stack

// Function to check if the stack is empty
int isEmpty() {
    return top == -1;
}

// Function to check if the stack is full
int isFull() {
    return top == MAX_SIZE - 1;
}

// Function to add an element to the stack
void push(int data) {
    if (isFull()) {
        printf("Stack Overflow! Cannot push %d\n", data);
    } else {
        stack[++top] = data;
        printf("%d pushed to stack\n", data);  
    }
}

// Function to remove an element from the stack
int pop() {
    if (isEmpty()) {
        printf("Stack Underflow! Cannot pop from an empty stack\n");
        return -1; // Return a default error value
    } else {
        int data = stack[top--];
        return data;
    }
}

// Function to view the top element
int peek() {
    if (isEmpty()) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        return stack[top];
    }
}

int main() {
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60); // This will cause a Stack Overflow message

    printf("\nTop element is %d\n", peek());

    printf("\nElements popped from stack: \n");
    while (!isEmpty()) {
        printf("%d\n", pop());
    }

    return 0;
}
