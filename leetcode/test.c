#include <stdio.h>

#include <stdlib.h>

// Definition for singly-linked list.
typedef struct ListNode {
    int val;
    struct ListNode *next;
}*Link;

void insertLast(struct ListNode** head, int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct ListNode* trav = *head;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = newNode;
    }
}

void printList(Link head){
	printf("\nCurrent Queue\n");
	Link current = head;
	while(current != NULL){
		printf("%d->", current->val);
		current = current->next;
	}
	printf("NULL");
}

void freeList(Link head){
	Link current = head;
	Link next = NULL;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* trav1 = l1;
    struct ListNode* trav2 = l2;
    struct ListNode* head = NULL;
    int multiplier = 1;
    int number1 = 0;
    int number2 = 0;
    int sum = 0;

    while(trav1 != NULL){
        number1 = number1 + (trav1->val * multiplier);
        trav1 = trav1->next;
        multiplier *= 10;
    }

    multiplier = 1;

    while(trav2 != NULL){
        number2 = number2 + (trav2->val * multiplier);
        trav2 = trav2->next;
        multiplier *= 10;
    }

    sum = number1 + number2;
    if(sum == 0){
        insertLast(&head, 0);
        return head;
    }

    while(sum != 0){
       int value = sum % 10;
        insertLast(&head, value);
        sum = sum / 10;
    }

    return head;
}

int main(){
    struct ListNode* head = NULL;
    struct ListNode* l1 = NULL;
    struct ListNode* l2 = NULL;
    insertLast(&l1, 7);
    insertLast(&l1, 2);
    insertLast(&l1, 1);

    insertLast(&l2, 3);
    insertLast(&l2, 6);
    insertLast(&l2, 5);

    head = addTwoNumbers(l1, l2);
    printList(head);
    freeList(l1);
    freeList(l2);
    freeList(head);
    return 0;
}