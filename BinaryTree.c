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

// Create a new node
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

// ==================== INSERTION ====================

// Insert a node recursively (returns new root of subtree)
struct Node* insertNode(struct Node* node, int value) {
    // Base case: found the spot to insert
    if (node == NULL) {
        return createNode(value);
    }
    
    // Recursive case: traverse left or right
    if (value < node->data) {
        node->left = insertNode(node->left, value);
    } else if (value > node->data) {
        node->right = insertNode(node->right, value);
    } else {
        // Duplicate value, don't insert
        printf("Value %d already exists\n", value);
    }
    
    return node;
}

// Wrapper function for insertion
void insert(int value) {
    root = insertNode(root, value);
    printf("%d inserted\n", value);
}

// ==================== SEARCHING ====================

// Search for a value recursively
struct Node* searchNode(struct Node* node, int value) {
    // Base cases
    if (node == NULL) {
        return NULL;  // Not found
    }
    
    if (value == node->data) {
        return node;  // Found!
    }
    
    // Recursive cases
    if (value < node->data) {
        return searchNode(node->left, value);
    } else {
        return searchNode(node->right, value);
    }
}

// Wrapper function for search
int search(int value) {
    struct Node* result = searchNode(root, value);
    
    if (result != NULL) {
        printf("%d found in tree\n", value);
        return 1;
    } else {
        printf("%d not found in tree\n", value);
        return 0;
    }
}

// ==================== FINDING MIN/MAX ====================

// Find minimum value node (leftmost node)
struct Node* findMin(struct Node* node) {
    if (node == NULL) {
        return NULL;
    }
    
    while (node->left != NULL) {
        node = node->left;
    }
    
    return node;
}

// Find maximum value node (rightmost node)
struct Node* findMax(struct Node* node) {
    if (node == NULL) {
        return NULL;
    }
    
    while (node->right != NULL) {
        node = node->right;
    }
    
    return node;
}

// ==================== DELETION ====================

// Delete a node recursively
struct Node* deleteNode(struct Node* node, int value) {
    // Base case: empty tree
    if (node == NULL) {
        printf("%d not found, cannot delete\n", value);
        return NULL;
    }
    
    // Recursive cases: find the node to delete
    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        // Found the node to delete!
        
        // Case 1: Leaf node (no children)
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        
        // Case 2: One child (only right)
        else if (node->left == NULL) {
            struct Node* temp = node->right;
            free(node);
            return temp;
        }
        
        // Case 2: One child (only left)
        else if (node->right == NULL) {
            struct Node* temp = node->left;
            free(node);
            return temp;
        }
        
        // Case 3: Two children
        else {
            // Find inorder successor (smallest in right subtree)
            struct Node* successor = findMin(node->right);
            
            // Copy successor's data to this node
            node->data = successor->data;
            
            // Delete the successor
            node->right = deleteNode(node->right, successor->data);
        }
    }
    
    return node;
}

// Wrapper function for deletion
void delete(int value) {
    root = deleteNode(root, value);
    printf("%d deleted from tree\n", value);
}

// ==================== TRAVERSALS ====================

// Inorder traversal (Left → Root → Right)
void inorderTraversal(struct Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

// Preorder traversal (Root → Left → Right)
void preorderTraversal(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

// Postorder traversal (Left → Right → Root)
void postorderTraversal(struct Node* node) {
    if (node != NULL) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        printf("%d ", node->data);
    }
}

// Level order traversal (using queue simulation)
void levelOrderTraversal(struct Node* node) {
    if (node == NULL) {
        return;
    }
    
    // Simple array-based queue (max 100 nodes)
    struct Node* queue[100];
    int front = 0, rear = 0;
    
    // Enqueue root
    queue[rear++] = node;
    
    while (front < rear) {
        // Dequeue
        struct Node* current = queue[front++];
        printf("%d ", current->data);
        
        // Enqueue left child
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        
        // Enqueue right child
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

// Wrapper functions for traversals
void inorder() {
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");
}

void preorder() {
    printf("Preorder: ");
    preorderTraversal(root);
    printf("\n");
}

void postorder() {
    printf("Postorder: ");
    postorderTraversal(root);
    printf("\n");
}

void levelOrder() {
    printf("Level Order: ");
    levelOrderTraversal(root);
    printf("\n");
}

// ==================== UTILITY FUNCTIONS ====================

// Calculate height of tree
int height(struct Node* node) {
    if (node == NULL) {
        return -1;  // Height of empty tree is -1
    }
    
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Count total nodes
int countNodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Count leaf nodes
int countLeaves(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    
    // If it's a leaf
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    
    return countLeaves(node->left) + countLeaves(node->right);
}

// Check if tree is empty
int isEmpty() {
    return root == NULL;
}

// Find sum of all nodes
int sum(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    
    return node->data + sum(node->left) + sum(node->right);
}

// Check if a value exists (iterative)
int contains(int value) {
    struct Node* current = root;
    
    while (current != NULL) {
        if (value == current->data) {
            return 1;  // Found
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return 0;  // Not found
}

// ==================== DISPLAY FUNCTIONS ====================

// Display tree structure (rotated 90 degrees)
void displayTree(struct Node* node, int space) {
    if (node == NULL) {
        return;
    }
    
    // Increase distance between levels
    space += 5;
    
    // Process right child first
    displayTree(node->right, space);
    
    // Print current node
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);
    
    // Process left child
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

// ==================== CLEANUP ====================

// Delete entire tree
void clearTree(struct Node* node) {
    if (node != NULL) {
        clearTree(node->left);
        clearTree(node->right);
        free(node);
    }
}

void clear() {
    clearTree(root);
    root = NULL;
    printf("Tree cleared\n");
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("=== Binary Search Tree Operations ===\n\n");
    
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
    inorder();      // Sorted order: 20 30 40 50 60 70 80
    preorder();     // Root first: 50 30 20 40 70 60 80
    postorder();    // Root last: 20 40 30 60 80 70 50
    levelOrder();   // Level by level: 50 30 70 20 40 60 80
    
    // Tree properties
    printf("\n--- Tree Properties ---\n");
    printf("Height: %d\n", height(root));
    printf("Total nodes: %d\n", countNodes(root));
    printf("Leaf nodes: %d\n", countLeaves(root));
    printf("Sum of all nodes: %d\n", sum(root));
    
    // Search
    printf("\n--- Search Operations ---\n");
    search(40);
    search(90);
    printf("Contains 60? %s\n", contains(60) ? "Yes" : "No");
    
    // Find min/max
    printf("\n--- Min/Max ---\n");
    struct Node* minNode = findMin(root);
    struct Node* maxNode = findMax(root);
    printf("Minimum value: %d\n", minNode->data);
    printf("Maximum value: %d\n", maxNode->data);
    
    // Delete operations
    printf("\n--- Delete Operations ---\n");
    delete(20);  // Leaf node
    inorder();
    
    delete(30);  // Node with two children
    inorder();
    
    delete(50);  // Root node
    inorder();
    
    display();
    
    // Clear tree
    printf("\n");
    clear();
    printf("Is empty? %s\n", isEmpty() ? "Yes" : "No");
    
    return 0;
}
