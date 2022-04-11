#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>



/***************** Queue ADT Implementation *****************/

void initQueue(Queue* q)
{
    // initialize  empty list by setting head and tail pointers to NULL
    q->head = q->tail = NULL;
}

void destroyQueue(Queue* q)
{
    //create temporary pointers
    intNode* current = q->head;
    intNode* next;

    //if list is empty
    if (isEmptyQueue(q)) {
        printf("list empty, cannot destroy elements\n");
        return;
    }

    //move pointer forward until end of list and release what remains behind
    while (current != NULL) {

        next = current->next; //move next pointer to following element

        free(current); //release element behind

        current = next; //set current pointer to next element

    }

    //set head and tail to NULL pointer
    q->head = q->tail = NULL;

}

void enqueue(Queue* q, unsigned int data)
{
    //create new element
    intNode* newElement = (intNode*)malloc(sizeof(intNode));

    //check if element was allocated
    if (newElement == NULL) {
        printf("no memory\n");
        return;
    }

    //insert new data into element
    newElement->data = data;

    //as we are inserting new element into the end of the list, we set its next pointer to NULL
    newElement->next = NULL;

    //if list is empty, set head  and tail pointer to new element
    if (isEmptyQueue(q)) q->head = newElement;

    //otherwise set tail->next to point to new element (puts it at end of list)
    else q->tail->next = newElement;

    //set the tail equal to new element in both cases
    q->tail = newElement;

}

unsigned int dequeue(Queue* q)
{
    int data = q->head->data;
    intNode* temp = q->head;

    //increment head forward one element
    q->head = q->head->next;

    //if there was only one element in the list, it will now be empty, so head and tail will point to NULL
    if (q->head == NULL) q->tail = NULL;

    //delete first element
    free(temp);

    //return its data
    return (data);
}

int isEmptyQueue(const Queue* q)
{
    if (q->head == NULL && q->tail == NULL) return 1; //both head and tail are NULL means list is empty
    return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/



void rotateQueue(Queue* q)
{
    intNode* ptr = q->head; //create pointer to head of q

    //if list is NULL
    if (q == NULL) {
        printf("list does not exist\n");
        return;
    }

    //if list is empty
    if (isEmptyQueue(q)) {
        printf("list is empty, cannot rotatate\n");
        return;
    }

    //if list has one element, no need to rotatate
    //if(q->head == q->tail) return;

    //create helping list
    Queue* aux = (Queue*)malloc(sizeof(Queue));
    initQueue(aux);

    //copy q to auxiliary list (except for last element)
    while (ptr->next != NULL) { //stop copying before last element
        ptr = ptr->next;
        enqueue(aux, dequeue(q)); //add each element to aux list and remove it from q (except last element)
    }

    ptr = aux->head; //set pointer to head of aux

   //copy auxiliary list to q, delete elements from aux
    while (ptr != NULL) {
        ptr = ptr->next;
        enqueue(q, dequeue(aux));
    }

    //free empty auxiliary list
    free(aux);
}

void cutAndReplace(Queue* q)
{
    int count = 0;

    //null list
    if (q == NULL) {
        printf("cannot cut and replace, list does not exist\n");
        return;
    }

    intNode* ptr = q->head;

    //create and initiate two auxiliary queues
    Queue* assist1 = (Queue*)malloc(sizeof(Queue));
    initQueue(assist1);

    Queue* assist2 = (Queue*)malloc(sizeof(Queue));
    initQueue(assist2);

    //empty list
    if (isEmptyQueue(q)) {
        printf("cannot cut and replace, list is empty\n");
        return;
    }

    //count number of elements in q
    while (ptr != NULL) {
        ptr = ptr->next;
        count++;
    }

    //one element
    if (count == 1) return;

    //odd elements in q
    if (count % 2) {

        int sum = 0;
        ptr = q->head;

        //add values of all elements in q
        while (ptr != NULL) {
            sum += ptr->data;
            ptr = ptr->next;
        }

        //add average of all elements to end of q
        enqueue(q, sum / count);

        //update count
        count++;
    }

    //pass first half of elements in q to assist 1
    for (int i = 0; i < count / 2; i++) {
        enqueue(assist1, dequeue(q));
    }
    //pass second half of elementsin q to assist 2
    for (int i = 0; i < count / 2; i++) {
        enqueue(assist2, dequeue(q));
    }

    //flip assist 2 and add in reversed order to q
    for (int i = 0; i < count / 2; i++) {
        //rotate list two, so that the last element is in the head
        rotateQueue(assist2);
        //remove the last element from assist 2
        int temp = dequeue(assist2);
        //place last element in head of q
        enqueue(q, temp);
    }

    //add assist 1 to end of q
    for (int i = 0; i < count / 2; i++) {
        enqueue(q, dequeue(assist1));
    }

    //release empty auxiliary lists 
    free(assist1);
    free(assist2);
}

void sortKidsFirst(Queue* q)
{
    int numElements = 0;

    //null list
    if (q == NULL) {
        printf("cannot sort, list does not exist\n");
        return;
    }

    intNode* ptr = q->head;

    //create and initiate auxiliary queue
    Queue* aux = (Queue*)malloc(sizeof(Queue));
    initQueue(aux);

    //empty list
    if (isEmptyQueue(q)) {
        printf("cannot sort, list is empty\n");
        return;
    }

    //one element
    if (q->head == q->tail) return;

    //count number of elements in q
    while (ptr != NULL) {
        ptr = ptr->next;
        numElements++;
    }

    while (numElements) {

        //variables to be reset each loop
        ptr = q->head;
        int min = q->head->data;
        int counter = 0;

        //find minimum value in list and save it
        while (ptr != NULL) {
            if (ptr->data < min) {
                min = ptr->data;
            }
            ptr = ptr->next;
        }

        ptr = q->head;

        //find location of minimum element
        while (ptr->data != min) {
            counter++;
            ptr = ptr->next;
        }

        //rotate list until minumum element is at head
        for (int i = 0; i < numElements - counter; i++) {
            rotateQueue(q);
        }

        //add minimum element to q auxiliary list and remove it from q
        enqueue(aux, dequeue(q));

        //update number of elements in list q
        numElements--;
    }
    //repeat until all elements have been transfered in order to auxiliary list

    //transfer all elements back to original list
    while (aux->head != NULL) {
        enqueue(q, dequeue(aux));
    }

    //release empty auxiliary list
    free(aux);
}
