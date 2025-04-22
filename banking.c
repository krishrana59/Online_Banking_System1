#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------- QUEUE --------------------
typedef struct QueueNode {
    int id;
    char name[50];
    char serviceType[50];
    struct QueueNode* next;
} QueueNode;

QueueNode* front = NULL;
QueueNode* rear = NULL;

void enqueue(int id, char name[], char service[]) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->serviceType, service);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("Enqueued Customer: %s (Service: %s)\n", name, service);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    QueueNode* temp = front;
    printf("Dequeued Customer: %s\n", front->name);
    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
}

void displayQueue() {
    QueueNode* temp = front;
    printf("\nCustomer Queue:\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Service: %s\n", temp->id, temp->name, temp->serviceType);
        temp = temp->next;
    }
}
// -------------------- LINKED LIST --------------------
typedef struct Customer {
    int id;
    char name[50];
    struct Customer* next;
} Customer;

Customer* head = NULL;

void addCustomer(int id, char name[]) {
    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = head;
    head = newNode;

    printf("Customer Added: %s\n", name);
}

void displayCustomers() {
    Customer* temp = head;
    printf("\nCustomer Records:\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}
// -------------------- BST FOR TRANSACTIONS --------------------
typedef struct TransactionNode {
    int transactionID;
    float amount;
    struct TransactionNode* left;
    struct TransactionNode* right;
} TransactionNode;

TransactionNode* createTransaction(int id, float amount) {
    TransactionNode* newNode = (TransactionNode*)malloc(sizeof(TransactionNode));
    newNode->transactionID = id;
    newNode->amount = amount;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TransactionNode* insertTransaction(TransactionNode* root, int id, float amount) {
    if (root == NULL) return createTransaction(id, amount);

    if (id < root->transactionID)
        root->left = insertTransaction(root->left, id, amount);
    else
        root->right = insertTransaction(root->right, id, amount);

    return root;
}

void inorderTransactions(TransactionNode* root) {
    if (root != NULL) {
        inorderTransactions(root->left);
        printf("Transaction ID: %d | Amount: %.2f\n", root->transactionID, root->amount);
        inorderTransactions(root->right);
    }
}
int main() {
    // Add some customers
    addCustomer(101, "Alice");
    addCustomer(102, "Bob");

    // Enqueue some service requests
    enqueue(101, "Alice", "Deposit");
    enqueue(102, "Bob", "Withdrawal");

    displayCustomers();
    displayQueue();

    dequeue();
    displayQueue();

    // Handle transactions
    TransactionNode* root = NULL;
    root = insertTransaction(root, 1001, 500.0);
    root = insertTransaction(root, 1002, 150.0);
    root = insertTransaction(root, 1003, 300.0);

    printf("\nTransaction History:\n");
    inorderTransactions(root);

    return 0;
}




