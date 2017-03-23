#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "stack.h"

stack *newStack(void (*d)(FILE *,void *)) //constructor for new stack
{
	stack *items = malloc(sizeof(stack));
	dll *storage = newDLL(d);

	if(storage == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}

	items->store = storage;
	return items;
}

void push(stack *items,void *value) //call to push new value onto stack
{
	insertDLL(items->store,0,value);
}

void *pop(stack *items) //call to pop selected value
{
	return removeDLL(items->store,0);
}

void *peekStack(stack *items) //view value stored at index without removing
{
	return getDLL(items->store,0);
}

int sizeStack(stack *items) //returns size of dll stored in stack
{
	return sizeDLL(items->store);
}

void displayStack(FILE *fp,stack *items) //displays dll inside of stack
{
	displayDLL(fp,items->store);
}
