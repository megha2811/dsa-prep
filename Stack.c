#include <stdio.h>

#define MAX_SIZE 5 // Define the maximum size of the stack

int stack[MAX_SIZE];
int top = -1; // Initialize top to -1 to indicate an empty stack

// Function to check if the stack is empty
int isEmpty() {
    return top == -1; // it is checking the condition top == -1, if true, it will return 1, if false, it will return 0
}

// Function to check if the stack is full
int isFull() {
    return top == MAX_SIZE - 1; // checking if top == MAX_SIZE - 1, if true, it will return 1, if false, it will return 0
}

// Function to add an element to the stack
void push(int data) {
    if (isFull()) {
        printf("Stack Overflow! Cannot push %d\n", data);
    } else {
        top++;
        stack[top] = data; // top pointer increments and then the value gets updated on top with the data we add
        printf("%d pushed to stack\n", data);  
    }
}

// Function to remove an element from the stack
int pop() { // we need to return the top most element, so we use int pop()
    if (isEmpty()) {
        printf("Stack Underflow! Cannot pop from an empty stack\n");
        return -1; // Return a default error value
    } else {
        int data = stack[top]; // removes the top element first, then it decrements to the next top element
        top--;
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


