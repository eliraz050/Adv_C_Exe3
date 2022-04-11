#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>

#define SIZE 8

void printQueue(Queue* q);
void checkQueueFunctions(Queue* myList);

void main()
{
	flipBetweenHashes("thi#si s# a sen#ecnet");
	Stack mainTry;
	initStack(&mainTry);
    isEmptyStack(&mainTry);
	push(&mainTry, 'a');
	push(&mainTry, 'b');
	push(&mainTry, 'c');
	push(&mainTry, 'c');
	push(&mainTry, 'v');
	push(&mainTry, 'a');
    pop(&mainTry);
	printf("%d\n", isPalindrome(&mainTry));
    printf("original stack:\n");
	printStackForChecks(&mainTry);
	rotateStack(&mainTry, 4);
    printf("rotated stack:\n");
	printStackForChecks(&mainTry);
    destroyStack(&mainTry);

    //int data[SIZE] = { 32,4,2,57,21,0,3,6 };

    ////initialize que
    //Queue* myList = (Queue*)malloc(sizeof(Queue));
    //initQueue(myList);

    ////add elements to que
    //for (int i = 0; i < SIZE; i++) {
    //    enqueue(myList, data[i]);
    //}

    ////check que functions
    //checkQueueFunctions(myList);

    ////release que
    //free(myList);

}

void printQueue(Queue* q) {

    intNode* ptr = q->head;
    int i = 0;

    if (isEmptyQueue(q)) {
        printf("list empty\n");
        return;
    }

    while (ptr != NULL) {

        printf("%d  ", ptr->data);

        ptr = ptr->next;
        i++;
    }
    printf("\n");
}

void checkQueueFunctions(Queue* myList) {

    //check enqueue
    printf("my list after enqueue: ");
    printQueue(myList);

    //empty list for tests
    Queue* emptyList = (Queue*)malloc(sizeof(Queue));
    initQueue(emptyList);

    //check isEmpty
    (isEmptyQueue(myList)) ? printf(" my list is empty\n") : printf("my list is not empty\n");
    (isEmptyQueue(emptyList)) ? printf("empty list is empty\n") : printf(" empty list is not empty\n");

    //rotate que
    rotateQueue(myList);
    printf("mylist rotated: ");
    printQueue(myList);

    printf("emptylist rotated: ");
    rotateQueue(emptyList);

    //sort list from lowest to highest
    printf("my list after sorting (lowest to highest): ");
    sortKidsFirst(myList);
    printQueue(myList);

    printf("try to sort NULL list: ");
    sortKidsFirst(NULL);

    printf("try to sort empty list: ");
    sortKidsFirst(emptyList);

    //cut and replace function
    printf("list after cutAndReplace() of even number: ");
    cutAndReplace(myList);
    printQueue(myList);

    dequeue(myList);
    printf("deque list: ");
    printQueue(myList);

    cutAndReplace(myList);
    printf("list after cutAndReplace() of odd number: ");
    printQueue(myList);

    printf("try to cut and replace NULL list: ");
    cutAndReplace(NULL);

    printf("try to cut and replace empty list: ");
    cutAndReplace(emptyList);

    //release all elements
    printf("after mylist elements destroyed: ");
    destroyQueue(myList);
    printQueue(myList);

    printf("try to destroy empty list: ");
    destroyQueue(emptyList);

    free(emptyList);
}
