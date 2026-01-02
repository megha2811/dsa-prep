#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Global head pointer
struct Node* head = NULL;

// ==================== UTILITY FUNCTIONS ====================

// Check if list is empty
int isEmpty() {
    return head == NULL;
}

// Get size of list
int size() {
    int count = 0;
    struct Node* temp = head;
    
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    return count;
}

// ==================== INSERTION FUNCTIONS ====================

// Insert at the beginning
void insertAtBeginning(int value) {
    // Create new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Set data and pointers
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    
    // If list is not empty, update old head's prev
    if (head != NULL) {
        head->prev = newNode;
    }
    
    // Update head
    head = newNode;
    
    printf("%d inserted at beginning\n", value);
}

// Insert at the end
void insertAtEnd(int value) {
    // Create new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    newNode->data = value;
    newNode->next = NULL;
    
    // If list is empty, make new node the head
    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
        printf("%d inserted at end (first node)\n", value);
        return;
    }
    
    // Traverse to the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Link last node to new node
    temp->next = newNode;
    newNode->prev = temp;
    
    printf("%d inserted at end\n", value);
}

// Insert at specific position (0-indexed)
void insertAtPosition(int value, int position) {
    // Check if position is valid
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }
    
    // If position is 0, insert at beginning
    if (position == 0) {
        insertAtBeginning(value);
        return;
    }
    
    // Create new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    newNode->data = value;
    
    // Traverse to position
    struct Node* temp = head;
    for (int i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Check if position is beyond list length
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }
    
    // Insert new node BEFORE temp
    newNode->next = temp;
    newNode->prev = temp->prev;
    
    // Update previous node's next (if exists)
    if (temp->prev != NULL) {
        temp->prev->next = newNode;
    } else {
        // If temp was head, update head
        head = newNode;
    }
    
    // Update temp's prev
    temp->prev = newNode;
    
    printf("%d inserted at position %d\n", value, position);
}

// Insert after a given node (given node pointer)
void insertAfter(struct Node* prevNode, int value) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }
    
    // Create new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    newNode->data = value;
    
    // Set new node's pointers
    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    
    // Update previous node's next
    prevNode->next = newNode;
    
    // Update next node's prev (if exists)
    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
    
    printf("%d inserted after given node\n", value);
}

// ==================== DELETION FUNCTIONS ====================

// Delete from beginning
void deleteAtBeginning() {
    if (isEmpty()) {
        printf("List is empty, nothing to delete\n");
        return;
    }
    
    // Save current head
    struct Node* temp = head;
    int value = temp->data;
    
    // Move head to next node
    head = head->next;
    
    // If new head exists, set its prev to NULL
    if (head != NULL) {
        head->prev = NULL;
    }
    
    // Free old head
    free(temp);
    
    printf("%d deleted from beginning\n", value);
}

// Delete from end
void deleteAtEnd() {
    if (isEmpty()) {
        printf("List is empty, nothing to delete\n");
        return;
    }
    
    // If only one node
    if (head->next == NULL) {
        int value = head->data;
        free(head);
        head = NULL;
        printf("%d deleted from end\n", value);
        return;
    }
    
    // Traverse to the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    int value = temp->data;
    
    // Update second-last node's next to NULL
    temp->prev->next = NULL;
    
    // Free last node
    free(temp);
    
    printf("%d deleted from end\n", value);
}

// Delete at specific position (0-indexed)
void deleteAtPosition(int position) {
    if (isEmpty()) {
        printf("List is empty, nothing to delete\n");
        return;
    }
    
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }
    
    // If deleting first node
    if (position == 0) {
        deleteAtBeginning();
        return;
    }
    
    // Traverse to position
    struct Node* temp = head;
    for (int i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Check if position is valid
    if (temp == NULL) {
        printf("Position out of bounds\n");
        return;
    }
    
    int value = temp->data;
    
    // Update previous node's next
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    
    // Update next node's prev
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    // Free the node
    free(temp);
    
    printf("%d deleted from position %d\n", value, position);
}

// Delete by value (first occurrence)
void deleteByValue(int value) {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    // Search for the node
    struct Node* temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    
    // If value not found
    if (temp == NULL) {
        printf("%d not found in list\n", value);
        return;
    }
    
    // If it's the first node
    if (temp == head) {
        deleteAtBeginning();
        return;
    }
    
    // Update previous node's next
    temp->prev->next = temp->next;
    
    // Update next node's prev (if exists)
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    // Free the node
    free(temp);
    
    printf("%d deleted from list\n", value);
}

// ==================== SEARCH & ACCESS FUNCTIONS ====================

// Search for a value (returns position or -1)
int search(int value) {
    struct Node* temp = head;
    int position = 0;
    
    while (temp != NULL) {
        if (temp->data == value) {
            printf("%d found at position %d\n", value, position);
            return position;
        }
        temp = temp->next;
        position++;
    }
    
    printf("%d not found in list\n", value);
    return -1;
}

// Get value at specific position
int getValueAt(int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return -1;
    }
    
    struct Node* temp = head;
    int index = 0;
    
    while (temp != NULL && index < position) {
        temp = temp->next;
        index++;
    }
    
    if (temp == NULL) {
        printf("Position out of bounds\n");
        return -1;
    }
    
    return temp->data;
}

// ==================== DISPLAY & OTHER FUNCTIONS ====================

// Display the entire list (forward)
void display() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    printf("List (Forward): NULL ← ");
    struct Node* temp = head;
    
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ↔ ");
        }
        temp = temp->next;
    }
    printf(" → NULL\n");
}

// Display the list backward
void displayBackward() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    // First, go to the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    printf("List (Backward): NULL ← ");
    
    // Now traverse backward
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf(" ↔ ");
        }
        temp = temp->prev;
    }
    printf(" → NULL\n");
}

// Reverse the list
void reverse() {
    struct Node* temp = NULL;
    struct Node* current = head;
    
    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    // Update head (temp will be at the last node processed)
    if (temp != NULL) {
        head = temp->prev;
    }
    
    printf("List reversed\n");
}

// Clear the entire list
void clear() {
    struct Node* current = head;
    struct Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    head = NULL;
    printf("List cleared\n");
}

// Get first node data
int getFirst() {
    if (isEmpty()) {
        printf("List is empty\n");
        return -1;
    }
    return head->data;
}

// Get last node data
int getLast() {
    if (isEmpty()) {
        printf("List is empty\n");
        return -1;
    }
    
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    return temp->data;
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("=== Doubly Linked List Operations ===\n\n");
    
    // Insert operations
    insertAtBeginning(10);
    insertAtBeginning(20);
    insertAtBeginning(30);
    display();
    displayBackward();
    
    printf("\n");
    insertAtEnd(40);
    insertAtEnd(50);
    display();
    displayBackward();
    
    printf("\n");
    insertAtPosition(25, 2);
    display();
    displayBackward();
    
    printf("\nSize: %d\n", size());
    printf("First element: %d\n", getFirst());
    printf("Last element: %d\n", getLast());
    
    // Search operations
    printf("\n");
    search(25);
    search(100);
    
    // Delete operations
    printf("\n");
    deleteAtBeginning();
    display();
    
    printf("\n");
    deleteAtEnd();
    display();
    
    printf("\n");
    deleteAtPosition(1);
    display();
    
    printf("\n");
    deleteByValue(10);
    display();
    
    // Reverse
    printf("\n");
    reverse();
    display();
    displayBackward();
    
    // Get value at position
    printf("\nValue at position 1: %d\n", getValueAt(1));
    
    // Clear list
    printf("\n");
    clear();
    display();
    
    return 0;
}