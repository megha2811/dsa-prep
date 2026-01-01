#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
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
    
    // Set data and next pointer
    newNode->data = value;
    newNode->next = head;
    
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
    
    // Traverse to position-1
    struct Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Check if position is beyond list length
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }
    
    // Insert new node
    newNode->next = temp->next;
    temp->next = newNode;
    
    printf("%d inserted at position %d\n", value, position);
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
    
    // Traverse to second-last node
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    // Save and delete last node
    int value = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    
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
    
    // Traverse to position-1
    struct Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Check if position is valid
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }
    
    // Delete node at position
    struct Node* nodeToDelete = temp->next;
    int value = nodeToDelete->data;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    
    printf("%d deleted from position %d\n", value, position);
}

// Delete by value (first occurrence)
void deleteByValue(int value) {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    // If first node has the value
    if (head->data == value) {
        deleteAtBeginning();
        return;
    }
    
    // Search for the node
    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    
    // If value not found
    if (temp->next == NULL) {
        printf("%d not found in list\n", value);
        return;
    }
    
    // Delete the node
    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    
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

// Display the entire list
void display() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    printf("List: ");
    struct Node* temp = head;
    
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

// Reverse the list
void reverse() {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        // Save next node
        next = current->next;
        
        // Reverse the link
        current->next = prev;
        
        // Move pointers forward
        prev = current;
        current = next;
    }
    
    head = prev;
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

// ==================== MAIN FUNCTION ====================

int main() {
    printf("=== Singly Linked List Operations ===\n\n");
    
    // Insert operations
    insertAtBeginning(10);
    insertAtBeginning(20);
    insertAtBeginning(30);
    display();  // 30 -> 20 -> 10 -> NULL
    
    printf("\n");
    insertAtEnd(40);
    insertAtEnd(50);
    display();  // 30 -> 20 -> 10 -> 40 -> 50 -> NULL
    
    printf("\n");
    insertAtPosition(25, 2);
    display();  // 30 -> 20 -> 25 -> 10 -> 40 -> 50 -> NULL
    
    printf("\nSize: %d\n", size());
    
    // Search operations
    printf("\n");
    search(25);
    search(100);
    
    // Delete operations
    printf("\n");
    deleteAtBeginning();
    display();  // 20 -> 25 -> 10 -> 40 -> 50 -> NULL
    
    printf("\n");
    deleteAtEnd();
    display();  // 20 -> 25 -> 10 -> 40 -> NULL
    
    printf("\n");
    deleteAtPosition(1);
    display();  // 20 -> 10 -> 40 -> NULL
    
    printf("\n");
    deleteByValue(10);
    display();  // 20 -> 40 -> NULL
    
    // Reverse
    printf("\n");
    reverse();
    display();  // 40 -> 20 -> NULL
    
    // Get value at position
    printf("\nValue at position 1: %d\n", getValueAt(1));
    
    // Clear list
    printf("\n");
    clear();
    display();
    
    return 0;
}