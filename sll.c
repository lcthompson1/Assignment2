#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

sll *newSLL(void (*d)(FILE *,void *)) //d is the display function
        {
        sll *items = malloc(sizeof(sll));
        if (items == 0)
            {
            fprintf(stderr,"out of memory");
            exit(-1);
            }
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        return items;
        }

int sizeSLL(sll *items) //returns size of linked list
{
	return items->size;
}

void *getSLL(sll *items,int index) //retrieve value at specific index
{
	int c;
	sllnode *current = malloc(sizeof(sllnode));
	current = items->head;
	for(c = 0; c < (index); c++)
	{

		current = current->next;
	}

	void *ret = current->value;
	return ret;
}

void insertSLL(sll *items, int index, void *value) //add new value at index
{
	int i;
	sllnode *tmp = malloc(sizeof(sllnode));
	sllnode *current = malloc(sizeof(sllnode));
	sllnode *previous = malloc(sizeof(sllnode));

	tmp->value = value;
	tmp->next = NULL;

	current = items->head;

	if(index == 0)
	{
		if(sizeSLL(items) == 0) //special case for empty list
		{
			items->head = tmp;
			items->tail = tmp;
		}
		else //add at beginning of nonempty list
		{
 			tmp->next = current;
			items->head = tmp;
		}
	}
	else if(index == 1)
	{
		previous = current;
		current = current->next;
		tmp->next = current;
		previous->next = tmp;
		if(index == sizeSLL(items)) //special case for adding tail pointer
		{
			items->tail = tmp;
		}
	}
	else if((index == sizeSLL(items)) && index > 0) //special case for end of list to fix tail pointer
	{
		current = items->tail;
		current->next = tmp;
		items->tail = current->next;
	}
	else
	{
		for(i = 1; i <= index; i++)
		{
			previous = current;
 			current = current->next;
		}
		tmp->next = current;
		previous->next = tmp;
	}

	items->size ++;
}

void *removeSLL(sll *items, int index) //remove and return value at index
{

	int i;
	sllnode *current = malloc(sizeof(sllnode));
	sllnode *previous = malloc(sizeof(sllnode));
	current = items->head;
	void *tmpValue;

	if(index == 0)
	{
		tmpValue = current->value;
		items->head = current->next;
	}
	else if(index == sizeSLL(items)-1)
	{
		for(i = 0; i < index; i++)
		{
//			tmpValue = current->value;
			previous = current;
			current = current->next;
		}
		tmpValue = current->value;
		items->tail = previous;
	}
	else
	{
		for(i = 0; i < index; i++)
		{
			tmpValue = current->value;
			previous = current;
			current = current->next;
		}

		previous->next = current->next;
//		if(index == sizeSLL(items)-1)
//		{
//			items->tail = previous;
//		}
	}
	items->size --;
	return tmpValue;
}

void unionSLL(sll *recipient, sll *donor) //merge two linked lists
{
	sllnode *tmp;
	if(donor->size > 0 && (recipient->size != 0))
	{
		tmp = recipient->tail;
		recipient->tail = donor->tail;
		tmp->next = donor->head;
		recipient->size = addSizes(recipient,donor);
		donor->size = 0;
		donor->head = NULL;
		donor->tail = NULL;
	}
	else if(donor->size > 0 && (recipient->size == 0)) //special case for empty recipient
	{
		recipient->head = donor->head;
		recipient->tail = recipient->tail;
		recipient->size = addSizes(recipient,donor);
		donor->size = 0;
		donor->tail = NULL;
		donor->head = NULL;
	}
}

void displaySLL(FILE *file, sll *items) //display values of list
{
	int i;
	fprintf(file,"[");
	for(i = 0; i < (sizeSLL(items));i++)
	{
		items->display(file,getSLL(items,i));
		if(i < (sizeSLL(items)-1))
			fprintf(file,",");
	}
	fprintf(file,"]");
}

int addSizes(sll *item1, sll *item2) //support function to add size of lists
{
	int x = item1->size;
	int y = item2->size;
	int i = x + y;
	return i;
}
