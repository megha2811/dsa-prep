#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

// (rear + 1) % SIZE creates circular wraparound. When rear reaches the end, it wraps to 0.
void enqueue(int value) {
    // Check if full
    if ((rear + 1) % SIZE == front) {
        printf("Queue is full\n");
        return;
    }
    
    // If empty, initialize front
    if (front == -1) {
        front = 0;
    }
    
    // Move rear circularly and insert
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("%d enqueued\n", value);
}

// Removes from front and moves front pointer forward circularly. 
// Resets both pointers if queue becomes empty.
int dequeue() {
    // Check if empty
    if (front == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    
    int value = queue[front];
    
    // If last element
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        // Move front circularly
        front = (front + 1) % SIZE;
    }
    
    return value;
}

// Returns front element without removing it.
int peek() {
    if (front == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue[front];
}

// Returns rear element without removing it.
int getRear() {
    if (rear == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue[rear];
}

int isEmpty() {
    return (front == -1);
}

// Queue is full when next position after rear equals front (circularly).
int isFull() {
    return ((rear + 1) % SIZE == front);
}

// If rear >= front: simple subtraction
// If rear < front: queue wraps around, so count from front to end + start to rear
int size() {
    if (isEmpty()) {
        return 0;
    }
    
    // Handle circular wraparound
    if (rear >= front) {
        return rear - front + 1;
    } else {
        return (SIZE - front) + (rear + 1);
    }
}

// Traverses circularly from front to rear, handling wraparound with modulo.
void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Queue elements: ");
    int i = front;
    
    // Traverse circularly from front to rear
    while (i != rear) {
        printf("%d ", queue[i]);
        i = (i + 1) % SIZE;
    }
    printf("%d\n", queue[rear]);  // Print last element
}

// Resets the queue to empty state.
void clear() {
    front = -1;
    rear = -1;
    printf("Queue cleared\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();  // 10 20 30
    
    printf("Size: %d\n", size());  // 3
    printf("Front: %d\n", peek()); // 10
    printf("Rear: %d\n", getRear()); // 30
    
    dequeue();
    display();  // 20 30
    
    enqueue(40);
    enqueue(50);
    enqueue(60);  // Now it wraps around!
    display();  // 20 30 40 50 60
    
    printf("Is Full: %d\n", isFull());  // 1 (true)
    
    return 0;
}