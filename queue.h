/*********************************************
*  File: queue.h
*
*  Author: Logan Thompson
*
*  Purpose: header file that corresponds to a queue implementing a single linked list as its store
*/

#ifndef __Q_INCLUDED__
#define __Q_INCLUDED__
#include "sll.h"

typedef struct queue
{
	sll *store;
	void (*display)(FILE *, void *);
} queue;

	queue *newQueue(void (*d)(FILE *,void *));   //constructor
	void enqueue(queue *items,void *value);      //stores a generic value
	void *dequeue(queue *items);                 //returns a generic value
	void *peekQueue(queue *items);               //returns a generic value
	int sizeQueue(queue *items);
	void displayQueue(FILE *fp,queue *items);

#endif
