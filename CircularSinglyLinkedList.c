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
    if (isEmpty()) {
        return 0;
    }
    
    int count = 1;
    struct Node* temp = head->next;
    
    while (temp != head) {
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
    
    newNode->data = value;
    
    // If list is empty
    if (head == NULL) {
        newNode->next = newNode;  // Point to itself
        head = newNode;
        printf("%d inserted at beginning (first node)\n", value);
        return;
    }
    
    // Find last node
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    // Insert new node
    newNode->next = head;
    temp->next = newNode;
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
    
    // If list is empty
    if (head == NULL) {
        newNode->next = newNode;
        head = newNode;
        printf("%d inserted at end (first node)\n", value);
        return;
    }
    
    // Find last node
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    // Insert new node at end
    temp->next = newNode;
    newNode->next = head;
    
    printf("%d inserted at end\n", value);
}

// Insert at specific position (0-indexed)
void insertAtPosition(int value, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }
    
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
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
        if (temp == head) {
            printf("Position out of bounds\n");
            free(newNode);
            return;
        }
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
    
    // If only one node
    if (head->next == head) {
        int value = head->data;
        free(head);
        head = NULL;
        printf("%d deleted from beginning\n", value);
        return;
    }
    
    // Find last node
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    // Save and delete head
    struct Node* toDelete = head;
    int value = toDelete->data;
    
    temp->next = head->next;
    head = head->next;
    free(toDelete);
    
    printf("%d deleted from beginning\n", value);
}

// Delete from end
void deleteAtEnd() {
    if (isEmpty()) {
        printf("List is empty, nothing to delete\n");
        return;
    }
    
    // If only one node
    if (head->next == head) {
        int value = head->data;
        free(head);
        head = NULL;
        printf("%d deleted from end\n", value);
        return;
    }
    
    // Find second-last node
    struct Node* temp = head;
    while (temp->next->next != head) {
        temp = temp->next;
    }
    
    // Save and delete last node
    struct Node* toDelete = temp->next;
    int value = toDelete->data;
    
    temp->next = head;
    free(toDelete);
    
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
    
    if (position == 0) {
        deleteAtBeginning();
        return;
    }
    
    // Traverse to position-1
    struct Node* temp = head;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
        if (temp == head) {
            printf("Position out of bounds\n");
            return;
        }
    }
    
    // Check if next node exists
    if (temp->next == head) {
        printf("Position out of bounds\n");
        return;
    }
    
    // Delete node
    struct Node* toDelete = temp->next;
    int value = toDelete->data;
    
    temp->next = toDelete->next;
    free(toDelete);
    
    printf("%d deleted from position %d\n", value, position);
}

// Delete by value (first occurrence)
void deleteByValue(int value) {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    // If head has the value
    if (head->data == value) {
        deleteAtBeginning();
        return;
    }
    
    // Search for the node
    struct Node* temp = head;
    while (temp->next != head && temp->next->data != value) {
        temp = temp->next;
    }
    
    // If value not found
    if (temp->next == head) {
        printf("%d not found in list\n", value);
        return;
    }
    
    // Delete the node
    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
    
    printf("%d deleted from list\n", value);
}

// ==================== SEARCH & ACCESS FUNCTIONS ====================

// Search for a value
int search(int value) {
    if (isEmpty()) {
        printf("List is empty\n");
        return -1;
    }
    
    struct Node* temp = head;
    int position = 0;
    
    do {
        if (temp->data == value) {
            printf("%d found at position %d\n", value, position);
            return position;
        }
        temp = temp->next;
        position++;
    } while (temp != head);
    
    printf("%d not found in list\n", value);
    return -1;
}

// Get value at specific position
int getValueAt(int position) {
    if (isEmpty()) {
        printf("List is empty\n");
        return -1;
    }
    
    if (position < 0) {
        printf("Invalid position\n");
        return -1;
    }
    
    struct Node* temp = head;
    int index = 0;
    
    do {
        if (index == position) {
            return temp->data;
        }
        temp = temp->next;
        index++;
    } while (temp != head);
    
    printf("Position out of bounds\n");
    return -1;
}

// ==================== DISPLAY & OTHER FUNCTIONS ====================

// Display the entire list
void display() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    printf("List (Circular): ");
    struct Node* temp = head;
    
    do {
        printf("%d", temp->data);
        if (temp->next != head) {
            printf(" → ");
        }
        temp = temp->next;
    } while (temp != head);
    
    printf(" → (back to %d)\n", head->data);
}

// Split list into two halves
void splitList(struct Node** head1, struct Node** head2) {
    if (isEmpty() || head->next == head) {
        *head1 = head;
        *head2 = NULL;
        return;
    }
    
    // Find middle using slow and fast pointers
    struct Node* slow = head;
    struct Node* fast = head;
    
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    // Set head1
    *head1 = head;
    
    // Set head2
    if (head->next != head) {
        *head2 = slow->next;
    }
    
    // Make both lists circular
    fast->next = slow->next;
    slow->next = head;
    
    printf("List split into two halves\n");
}

// Clear the entire list
void clear() {
    if (isEmpty()) {
        printf("List is already empty\n");
        return;
    }
    
    struct Node* current = head;
    struct Node* next;
    
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);
    
    head = NULL;
    printf("List cleared\n");
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("=== Circular Singly Linked List Operations ===\n\n");
    
    // Insert operations
    insertAtBeginning(10);
    insertAtBeginning(20);
    insertAtBeginning(30);
    display();
    
    printf("\n");
    insertAtEnd(40);
    insertAtEnd(50);
    display();
    
    printf("\n");
    insertAtPosition(25, 2);
    display();
    
    printf("\nSize: %d\n", size());
    
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
    
    // Get value at position
    printf("\nValue at position 1: %d\n", getValueAt(1));
    
    // Clear list
    printf("\n");
    clear();
    display();
    
    return 0;
}
