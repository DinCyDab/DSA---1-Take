#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree{
    int data;
    struct tree* left;
    struct tree* right;
}*Tree;

typedef struct node{
    Tree data;
    struct node* next;
}*Nodeptr;

typedef struct queue{
    Nodeptr front;
    Nodeptr rear;
}*Queue;

void enqueue(Queue* q, Tree root);
Tree dequeue(Queue* q);
Queue initQueue();
bool isEmpty(Queue q);

Tree createNode(int data);
void insertNode(Tree* root, int data);
void deleteNode(Tree* root, int data);
void BFS(Tree root);
void printTree(Tree root);
void freeTree(Tree root);


int main(){
    Tree root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 4);
    insertNode(&root, 8);
    insertNode(&root, 24);
    insertNode(&root, 16);
    insertNode(&root, 18);
    insertNode(&root, 17);
    deleteNode(&root, 20);
    BFS(root);
    // printTree(root);
    freeTree(root);
    return 0;
}

void enqueue(Queue* q, Tree root){
    Nodeptr newNode = (Nodeptr)malloc(sizeof * newNode);
    newNode->data = root;
    newNode->next = NULL;

    if(isEmpty(*q)){
        (*q)->front = newNode;
        (*q)->rear = newNode;
        return;
    }

    (*q)->rear->next = newNode;
    (*q)->rear = newNode;
}

Tree dequeue(Queue* q) {
    if (isEmpty(*q)) {
        return NULL;
    }

    Nodeptr tempNode = (*q)->front;
    Tree tempData = tempNode->data;
    (*q)->front = (*q)->front->next;

    if ((*q)->front == NULL) {
        (*q)->rear = NULL;
    }

    free(tempNode); // Free dequeued node to prevent memory leak
    return tempData;
}

bool isEmpty(Queue q){
    return q->front == NULL;
}

void insertNode(Tree* root, int data){
    Tree newNode = createNode(data);

    if(*root == NULL){
        *root = newNode;
        return;
    }

    Tree* trav = root;
    while(*trav != NULL && (*trav)->data != data){
        trav = (data > (*trav)->data)? &(*trav)->right : &(*trav)->left;
    }

    if(*trav == NULL){
        *trav = newNode;
        return;
    }

    free(newNode);
}

void deleteNode(Tree* root, int data){
    if(*root == NULL){
        return;
    }

    Tree* trav = root;
    while(*trav != NULL && (*trav)->data != data){
        trav = (data > (*trav)->data)? &(*trav)->right: &(*trav)->left;
    }

    if(*trav == NULL){
        // data not found inside the tree
        return;
    }

    Tree temp = *trav;
    if(temp->left == NULL && temp->right == NULL){
        *trav = NULL;
    }
    else{
        Tree* look;
        if((*trav)->left != NULL){
            look = &(*trav)->left;
            while((*look)->right != NULL){
                look = &(*look)->right;
            }
            temp->data = (*look)->data;
            temp = *look;
            *look = temp->left;
        }
        else{
            look = &(*trav)->right;
            while((*look)->left != NULL){
            look = &(*look)->left;
            }
            temp->data = (*look)->data;
            temp = *look;
            *look = temp->right;
        }
        
    }
    free(temp);
}

Tree createNode(int data){
    Tree newNode = (Tree)malloc(sizeof * newNode);
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Queue initQueue(){
    Queue q = (Queue)malloc(sizeof * q);
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void BFS(Tree root){
    if(root == NULL){
        return;
    }

    Queue q = initQueue();
    enqueue(&q, root);

    while(!isEmpty(q)){
        Tree current = dequeue(&q);
        printf("%d --> ", current->data);

        if(current->left != NULL){
            enqueue(&q, current->left);
        }
        if(current->right != NULL){
            enqueue(&q, current->right);
        }
    }
}

void printTree(Tree root){
    if(root == NULL){
        return;
    }

    printTree(root->left);
    printf("%d --> ", root->data);
    printTree(root->right);
}

void freeTree(Tree root){
    if(root == NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}