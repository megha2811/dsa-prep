#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Global root pointer
struct Node* root = NULL;

// ==================== NODE CREATION ====================

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

// ==================== INSERTION (ITERATIVE) ====================

void insert(int value) {
    struct Node* newNode = createNode(value);
    
    if (newNode == NULL) return;
    
    // If tree is empty
    if (root == NULL) {
        root = newNode;
        printf("%d inserted (first node)\n", value);
        return;
    }
    
    // Find the correct position
    struct Node* current = root;
    struct Node* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            // Duplicate value
            printf("%d already exists\n", value);
            free(newNode);
            return;
        }
    }
    
    // Insert at the found position
    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    printf("%d inserted\n", value);
}

// ==================== SEARCHING (ITERATIVE) ====================

struct Node* search(int value) {
    struct Node* current = root;
    
    while (current != NULL) {
        if (value == current->data) {
            printf("%d found in tree\n", value);
            return current;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    printf("%d not found in tree\n", value);
    return NULL;
}

// ==================== FIND MIN/MAX (ITERATIVE) ====================

struct Node* findMin(struct Node* node) {
    if (node == NULL) return NULL;
    
    // Keep going left
    while (node->left != NULL) {
        node = node->left;
    }
    
    return node;
}

struct Node* findMax(struct Node* node) {
    if (node == NULL) return NULL;
    
    // Keep going right
    while (node->right != NULL) {
        node = node->right;
    }
    
    return node;
}

// ==================== DELETION (ITERATIVE) ====================

void deleteNode(int value) {
    struct Node* current = root;
    struct Node* parent = NULL;
    
    // Find the node to delete
    while (current != NULL && current->data != value) {
        parent = current;
        
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    // Node not found
    if (current == NULL) {
        printf("%d not found, cannot delete\n", value);
        return;
    }
    
    // CASE 1: Node has NO children (leaf node)
    if (current->left == NULL && current->right == NULL) {
        if (current == root) {
            root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    
    // CASE 2: Node has ONE child (only right)
    else if (current->left == NULL) {
        if (current == root) {
            root = current->right;
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(current);
    }
    
    // CASE 2: Node has ONE child (only left)
    else if (current->right == NULL) {
        if (current == root) {
            root = current->left;
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(current);
    }
    
    // CASE 3: Node has TWO children
    else {
        // Find inorder successor (smallest in right subtree)
        struct Node* successor = findMin(current->right);
        int successorValue = successor->data;
        
        // Delete the successor
        deleteNode(successorValue);
        
        // Replace current node's data with successor's data
        current->data = successorValue;
        return;  // Already printed in recursive call
    }
    
    printf("%d deleted from tree\n", value);
}

// ==================== TRAVERSALS (ITERATIVE) ====================

// Inorder: Left → Root → Right
void inorderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("Inorder: ");
    
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;
    
    while (current != NULL || top != -1) {
        // Go to leftmost node
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        // Pop and print
        current = stack[top--];
        printf("%d ", current->data);
        
        // Visit right subtree
        current = current->right;
    }
    
    printf("\n");
}

// Preorder: Root → Left → Right
void preorderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("Preorder: ");
    
    struct Node* stack[100];
    int top = -1;
    
    stack[++top] = root;
    
    while (top != -1) {
        // Pop and print
        struct Node* current = stack[top--];
        printf("%d ", current->data);
        
        // Push right first (so left is processed first)
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
    
    printf("\n");
}

// Postorder: Left → Right → Root
void postorderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("Postorder: ");
    
    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1;
    int top2 = -1;
    
    stack1[++top1] = root;
    
    while (top1 != -1) {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;
        
        if (current->left != NULL) {
            stack1[++top1] = current->left;
        }
        
        if (current->right != NULL) {
            stack1[++top1] = current->right;
        }
    }
    
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
    
    printf("\n");
}

// Level Order: Level by level
void levelOrderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("Level Order: ");
    
    // Simple queue using array
    struct Node* queue[100];
    int front = 0;
    int rear = 0;
    
    // Enqueue root
    queue[rear++] = root;
    
    while (front < rear) {
        // Dequeue
        struct Node* current = queue[front++];
        printf("%d ", current->data);
        
        // Enqueue children
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
    
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    
    printf("\n");
}

// ==================== UTILITY FUNCTIONS (ITERATIVE) ====================

// Calculate height iteratively
int height() {
    if (root == NULL) return -1;
    
    // Use level order traversal
    struct Node* queue[100];
    int front = 0;
    int rear = 0;
    int height = -1;
    
    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        height++;
        
        // Process all nodes at current level
        for (int i = 0; i < levelSize; i++) {
            struct Node* current = queue[front++];
            
            if (current->left != NULL) {
                queue[rear++] = current->left;
            }
            
            if (current->right != NULL) {
                queue[rear++] = current->right;
            }
        }
    }
    
    return height;
}

// Count nodes iteratively
int countNodes() {
    if (root == NULL) return 0;
    
    int count = 0;
    struct Node* queue[100];
    int front = 0;
    int rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct Node* current = queue[front++];
        count++;
        
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    
    return count;
}

// Count leaf nodes iteratively
int countLeaves() {
    if (root == NULL) return 0;
    
    int count = 0;
    struct Node* queue[100];
    int front = 0;
    int rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct Node* current = queue[front++];
        
        // Check if it's a leaf
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    
    return count;
}

// Check if tree is empty
int isEmpty() {
    return root == NULL;
}

// Display tree structure
void displayTree(struct Node* node, int space) {
    if (node == NULL) return;

    space += 5;

    displayTree(node->right, space);

    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);

    displayTree(node->left, space);
}

void display() {
    if (isEmpty()) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("\nTree Structure (rotated 90° clockwise):\n");
    displayTree(root, 0);
    printf("\n");
}

// Clear tree iteratively
void clear() {
    if (root == NULL) {
        printf("Tree is already empty\n");
        return;
    }
    
    // Use level order to delete all nodes
    struct Node* queue[100];
    int front = 0;
    int rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct Node* current = queue[front++];
        
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
        
        free(current);
    }
    
    root = NULL;
    printf("Tree cleared\n");
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("=== Binary Search Tree (Iterative Implementation) ===\n\n");
    
    // Insert nodes
    insert(50);
    insert(30);
    insert(70);
    insert(20);
    insert(40);
    insert(60);
    insert(80);
    
    display();
    
    // Traversals
    printf("\n--- Traversals ---\n");
    inorderTraversal();
    preorderTraversal();
    postorderTraversal();
    levelOrderTraversal();
    
    // Tree properties
    printf("\n--- Tree Properties ---\n");
    printf("Height: %d\n", height());
    printf("Total nodes: %d\n", countNodes());
    printf("Leaf nodes: %d\n", countLeaves());
    
    // Search
    printf("\n--- Search Operations ---\n");
    search(40);
    search(90);

    // Find min/max
    printf("\n--- Min/Max ---\n");
    struct Node* minNode = findMin(root);
    struct Node* maxNode = findMax(root);
    if (minNode) printf("Minimum value: %d\n", minNode->data);
    if (maxNode) printf("Maximum value: %d\n", maxNode->data);
    
    // Delete operations
    printf("\n--- Delete Operations ---\n");
    deleteNode(20);
    inorderTraversal();
    
    deleteNode(30);
    inorderTraversal();
    
    deleteNode(50);
    inorderTraversal();
    
    display();
    
    // Clear tree
    printf("\n");
    clear();
    printf("Is empty? %s\n", isEmpty() ? "Yes" : "No");
    
    return 0;
}
