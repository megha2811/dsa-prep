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
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        printf("%d inserted at beginning (first node)\n", value);
        return;
    }
    
    // Get last node
    struct Node* last = head->prev;
    
    // Insert new node
    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
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
        newNode->prev = newNode;
        head = newNode;
        printf("%d inserted at end (first node)\n", value);
        return;
    }
    
    // Get last node
    struct Node* last = head->prev;
    
    // Insert new node at end
    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
    
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
    
    // Traverse to position
    struct Node* temp = head;
    for (int i = 0; i < position; i++) {
        temp = temp->next;
        if (temp == head) {
            printf("Position out of bounds\n");
            free(newNode);
            return;
        }
    }
    
    // Insert new node before temp
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
    
    // If inserting at head position
    if (temp == head) {
        head = newNode;
    }
    
    printf("%d inserted at position %d\n", value, position);
}

// ==================== DELETION FUNCTIONS ====================

// Delete from beginning
void deleteAtBeginning() {
    if (isEmpty()) {
        printf("List is empty, nothing to delete\n");
        return;
    }
    
    int value = head->data;
    
    // If only one node
    if (head->next == head) {
        free(head);
        head = NULL;
        printf("%d deleted from beginning\n", value);
        return;
    }
    
    // Get last node
    struct Node* last = head->prev;
    struct Node* toDelete = head;
    
    // Update connections
    last->next = head->next;
    head->next->prev = last;
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
    
    // Get last node
    struct Node* last = head->prev;
    int value = last->data;
    
    // Update connections
    last->prev->next = head;
    head->prev = last->prev;
    
    free(last);
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
    
    // Traverse to position
    struct Node* temp = head;
    for (int i = 0; i < position; i++) {
        temp = temp->next;
        if (temp == head) {
            printf("Position out of bounds\n");
            return;
        }
    }
    
    int value = temp->data;
    
    // Update connections
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    
    // If deleting head
    if (temp == head) {
        head = temp->next;
    }
    
    free(temp);
    printf("%d deleted from position %d\n", value, position);
}

// Delete by value (first occurrence)
void deleteByValue(int value) {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* temp = head;
    
    // Search for the node
    do {
        if (temp->data == value) {
            // If only one node
            if (temp->next == temp) {
                free(temp);
                head = NULL;
                printf("%d deleted from list\n", value);
                return;
            }
            
            // Update connections
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            
            // If deleting head
            if (temp == head) {
                head = temp->next;
            }
            
            free(temp);
            printf("%d deleted from list\n", value);
            return;
        }
        temp = temp->next;
    } while (temp != head);
    
    printf("%d not found in list\n", value);
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

// Display the list forward
void display() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    printf("List (Forward): ");
    struct Node* temp = head;
    
    do {
        printf("%d", temp->data);
        if (temp->next != head) {
            printf(" ↔ ");
        }
        temp = temp->next;
    } while (temp != head);
    
    printf(" ↔ (back to %d)\n", head->data);
}

// Display the list backward
void displayBackward() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    
    printf("List (Backward): ");
    struct Node* temp = head->prev;
    
    do {
        printf("%d", temp->data);
        if (temp->prev != head->prev) {
            printf(" ↔ ");
        }
        temp = temp->prev;
    } while (temp != head->prev);
    
    printf("%d ↔ (back to %d)\n", temp->data, head->prev->data);
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
    printf("=== Circular Doubly Linked List Operations ===\n\n");
    
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