#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void removeItem(charNode** head);
charNode* addToHead(charNode* head, charNode* toAdd);
void printStackForChecks(Stack* s);
int hoManyInStack(Stack* s);

/***************** Stack ADT Implementation *****************/

void initStack(Stack* s) //initalize a stack
{
	s->head = NULL;
}

void destroyStack(Stack* s) //free all elements of stack
{
	charNode* head = s->head;
	while (head->next != NULL) {
		charNode* temp = head;
		head = head->next;
		free(temp);
	}
	free(head);
}

void push(Stack* s, char data) // push an element to top of stack
{
	charNode* newNode = (charNode*)malloc(sizeof(charNode));
	if (newNode == NULL) {
		printf("push: allocation failed\n");
		return;
	}
	newNode->data = data;
	s->head = addToHead(s->head, newNode);
}

charNode* addToHead(charNode* head, charNode* toAdd) { // add an element to top of linked list
	toAdd->next = head;
	head = toAdd;
	return head;
}

char pop(Stack* s) // remove an elemnt from top of stack and return its data
{
	char res;
	res = s->head->data;
	removeItem(&(s->head));
	return res;
}

void removeItem(charNode** head) { // remove an element from top of linked list
	charNode* tmp = *head;
	*head = (*head)->next;
	free(tmp);
}


int isEmptyStack(const Stack* s) // return 1 if stack is empty and 0 if not
{
	return (!(s->head));
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	int hashCount = 0; // if zogi no need for reverse and if e-zogi need to reverse
	Stack partSentence; // stack for reversed parts
	initStack(&partSentence);
	while (*sentence != '\0') { // run untill end of sentence
		if (hashCount % 2 == 0) { // if no need for reverse
			while (*sentence != '#' && *sentence != '\0') { // print untill need for reverse or end of sentence
				printf("%c", *sentence);
				sentence = sentence++;
			}
			hashCount++;
			sentence = sentence++;
		}
		if (hashCount % 2 == 1) { // if need for reverse
			while (*sentence != '#' && *sentence != '\0') { // put into a stack (which will reverse the letters)
				push(&partSentence, *sentence);
				sentence = sentence++;
			}
			while (!isEmptyStack(&partSentence)) { // while stack is not empty print stack
				printf("%c", pop(&partSentence));
			}
			sentence = sentence++;
			hashCount++;
		}
		
	}
	printf("\n");
}

int isPalindrome(Stack* s)
{
	if (s == NULL) { //check if s in nullptr
		printf("no sentence");
		return 0;
	}
	if (isEmptyStack(s) || s->head->next == NULL) return 1; // if stack is empty or has one element its polindrome -return 1
	Stack reversedStack; // stack for reversed stack
	initStack(&reversedStack);
	charNode* temp = s->head;
	while (temp) { //make a reversed stack
		push(&reversedStack, temp->data);
		temp = temp->next;
	}
	temp = s->head;
	charNode* temp2 = reversedStack.head;
	while (temp || temp2) { // check if data is equell on top of stack and revesed stack
		if (temp2->data != temp->data) return 0; // stop if not polindrome and return 0
		temp2 = temp2->next;
		temp = temp->next;
	}
	return 1; // is polidrome
	
}

void rotateStack(Stack* s, int n)
{
	if (s == NULL) { //check if s in nullptr
		printf("no sentence");
		return;
	}
	if (isEmptyStack(s) || s->head->next == NULL || hoManyInStack(s) < n || n <= 0) return; // if stack is empty or has one element or if n is more than the number of elements or if n is negetive or zero do nothing
	int counter = 0; 
	charNode* temp = s->head;
	while (counter < n) { //do it n times
		while (temp->next->next != NULL) { // find last element
			temp = temp->next;
		}
		push(s, temp->next->data); // push last elemnt to top of stack
		temp->next = NULL; // remove last elemnt from stack
		counter++;
		temp = s->head;
	}
}
int hoManyInStack(Stack* s) { // checks how many elements in a stack
	int counter = 0;
	charNode* temp = s->head;
	while (temp) {
		counter++;
		temp = temp->next;
	}
	return counter;
}

void printStackForChecks(Stack* s) { // fast print of all stack elements data 
	charNode* temp = s->head;
	while (temp != NULL) {
		printf("%c\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}