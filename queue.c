#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "queue.h"

queue *newQueue(void (*d)(FILE *, void *)) //constructor for new queue
{
	queue *items = malloc(sizeof(queue));
	sll *storage = newSLL(d);

	if(storage == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}

	items->store = storage;
	return items;
}

void enqueue(queue *items, void *value) //inserts new value onto queue
{
	insertSLL(items->store,sizeSLL(items->store),value);
}

void *dequeue(queue *items) //removes value from queue
{
	return removeSLL(items->store,0);
}

void *peekQueue(queue *items) //view value without removing
{
	return getSLL(items->store,0);
}

int sizeQueue(queue *items) //returns siz of sll used in queue
{
	return sizeSLL(items->store);
}

void displayQueue(FILE *fp, queue *items) //displays queue stored in queue
{
	displaySLL(fp,items->store);
}
