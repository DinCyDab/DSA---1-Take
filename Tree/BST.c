#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}*BST;

BST createNode(int data);
void insertNode(BST* root, int data);
void deleteNode(BST* root, int data);
void printTree(BST root);
void freeTree(BST root);

int main(){
    BST root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 7);
    insertNode(&root, 15);
    insertNode(&root, 5);
    insertNode(&root, 4);
    insertNode(&root, 9);
    insertNode(&root, 8);
    insertNode(&root, 13);
    insertNode(&root, 14);
    insertNode(&root, 16);
    deleteNode(&root, 13);
    printTree(root);
    freeTree(root);
    return 0;
}

void deleteNode(BST* root, int data){
    // BST* trav = root;
    // BST temp;
    // BST* look;
    
    // while(*trav != NULL && (*trav)->data != data){
    //     trav = (data > (*trav)->data)? &(*trav)->right : &(*trav)->left;
    // }

    // if(*trav != NULL){
    //     temp = *trav;
    //     if((*trav)->left == NULL && (*trav)->right == NULL){
    //         *trav = (temp->left != NULL)? temp->left : temp->right;
    //     }
    //     else{
    //         look = &temp->left;
    //         while((*look)->right != NULL){
    //             look = &(*look)->right;
    //         }
    //         temp->data = (*look)->data;
    //         temp = *look;
    //         *look = temp->left;
    //     }
    // }
    // free(temp);
    BST* trav = root;
    BST temp;
    BST* look;

    while(*trav != NULL && (*trav)->data != data){
        trav = (data < (*trav)->data)? &(*trav)->left : &(*trav)->right;
    }
    if(*trav != NULL){
        temp = *trav;
        if((*trav)->left == NULL && (*trav)->right == NULL){
            *trav = ((*trav)->left != NULL)? temp->left : temp->right;
        }
        else{
            look = trav;
            while((*look)->right != NULL){
                look = &(*look)->right;
            }
            temp->data = (*look)->data;
            temp = *look;
            *look = temp->left;
        }
    }
    free(temp);
}

void insertNode(BST* root, int data){
    BST newNode = createNode(data);
    
    if(*root == NULL){
        *root = newNode;
        return;
    }

    BST* trav = root;

    while(*trav != NULL && (*trav)->data != data){
        trav = (data < (*trav)->data)? &(*trav)->left : &(*trav)->right;
    }

    if(*trav == NULL){
        *trav = newNode;
        return;
    }

    free(newNode);
}
BST createNode(int data){
    BST newNode = (BST)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void printTree(BST root){
    if(root->left != NULL){
        printTree(root->left);
    }
    if(root->right != NULL){
        printTree(root->right);
    }
    printf("%d --> ", root->data);
}
void freeTree(BST root){
    if(root->left != NULL){
        freeTree(root->left);
    }
    if(root->right != NULL){
        freeTree(root->right);
    }
    free(root);
}