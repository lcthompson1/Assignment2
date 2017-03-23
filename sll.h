/*********************************************
*  File: sll.h
*
*  Author: Logan Thompson
*
*  Purpose: header file that implements the function headers for a singly linked list
*/

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct sllnode
{
	void *value;
	struct sllnode *next;
} sllnode;

typedef struct sll
{
	sllnode *head;
	sllnode *tail;
	int size;
	void (*display)(FILE *,void *);
} sll;

	extern sll *newSLL(void (*d)(FILE *,void *));            //constructor  DONE
	extern void insertSLL(sll *items,int index,void *value); //stores a generic value DONE
	extern void *removeSLL(sll *items,int index);            //returns a generic value DONE
	extern void unionSLL(sll *recipient,sll *donor);         //merge two lists into one
	extern void *getSLL(sll *items,int index);               //get the value at the index DONE
	extern int sizeSLL(sll *items);                          //DONE
	extern void displaySLL(FILE *,sll *items);
	extern int addSizes(sll *item1, sll *item2);

#endif
