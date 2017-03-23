/*********************************************
*  File: stack.h
*
*  Author: Logan Thompson
*
*  Purpose: header file that corresponds to a stack implementing a doubly linked list as its store
*/

#ifndef __Q_INCLUDED__
#define __S_INCLUDED__
#include "dll.h"

typedef struct stack
{
	dll *store;
} stack;


	stack *newStack(void (*d)(FILE *,void *));   //constructor
	void push(stack *items,void *value);         //stores a generic value
	void *pop(stack *items);                     //returns a generic value
	void *peekStack(stack *items);               //returns a generic value
	int sizeStack(stack *items);
	void displayStack(FILE *,stack *items);

#endif
