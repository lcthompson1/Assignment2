#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

dll *newDLL(void (*d)(FILE *,void *)) //constructor for dll
{
	dll *items = malloc(sizeof(dll));
	if(items == 0)
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

int sizeDLL(dll *items) //return size of dll
{
	return items->size;
}

void displayDLL(FILE *file, dll *items) //display values in dll
{
	int i;
	fprintf(file,"[");
	for(i = 0; i < (sizeDLL(items));i++)
	{
		items->display(file,getDLL(items,i));
		if(i < (sizeDLL(items)-1))
			fprintf(file,",");
	}
	fprintf(file,"]");
}

int addSizesDLL(dll *item1, dll *item2) //support function to add sizes of two dll's
{
	int x = item1->size;
	int y = item2->size;
	int i = x + y;
	return i;
}

void *getDLL(dll *items, int index) //retrieve value at index of dll
{
	if(index < (sizeDLL(items) / 2))
	{
		return getDLLLeft(items, index);
	}
	else
	{
		return getDLLRight(items, index);
	}
}

void *getDLLLeft(dll *items, int index) //seperate function for maximum effiencey
{
	int c;
	dllnode *current = malloc(sizeof(dllnode));
	current = items->head;

	for(c = 0; c < (index); c++)
	{
		current = current->next;
	}

	void *ret = current->value;
	return ret;
}

void *getDLLRight(dll *items, int index) //seperate function for maximum effiency
{
	int c;
	dllnode *current = malloc(sizeof(dllnode));
	current = items->tail;

	for(c = 0;  c < ((sizeDLL(items) - index) - 1); c++)
	{
		current = current->prev;
	}

	void *ret = current->value;
	return ret;
}

void insertDLL(dll *items,int index,void *value) //inserts new value into dll
{
	if(index <= (sizeDLL(items) / 2))
        {
                insertDLLLeft(items, index, value);
        }
        else
        {
                insertDLLRight(items, index, value);
        }
}

void insertDLLLeft(dll *items, int index, void *value) //seperate function for maximum effiency
{
	int i;
	dllnode *tmp = malloc(sizeof(dllnode));
	dllnode *current = malloc(sizeof(dllnode));

	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = NULL;

	current = items->head;

	if(index == 0)
	{
		if(sizeDLL(items) == 0)
		{
			items->head = tmp;
			items->tail = tmp;
		}
		else
		{
			tmp->next = current;
			current->prev = tmp;
			items->head = tmp;
		}
	}
	else if(index == 1)
	{
		current = current->next;
		items->head->next = tmp;
		tmp->next = current;
		tmp->prev = items->head;
		current->prev = tmp;
		if(index == sizeDLL(items))
		{
			items->tail = tmp;
		}
	}
	else
	{
		for(i = 1; i <= index; i++)
		{
			current = current->next;
		}
			tmp->next = current;
			tmp->prev = current->prev;
			current->prev = tmp;
			tmp->prev->next = tmp;
	}
	items->size ++;
}

void insertDLLRight(dll *items, int index, void *value) //seperate function for maximum effiency
{
        int i, newIndex;
        dllnode *tmp = malloc(sizeof(dllnode));
        dllnode *current = malloc(sizeof(dllnode));

	newIndex = sizeDLL(items) - index;

        tmp->value = value;
        tmp->next = NULL;
        tmp->prev = NULL;

        current = items->tail;

	if((index == sizeDLL(items)))
	{
		current->next = tmp;
		tmp->prev = current;
		items->tail = tmp;
	}
	else
	{
		for(i = 0;i < (newIndex - 1);i++)
		{
			current = current->prev;
		}
		tmp->prev = current->prev;
		tmp->next = current;
		tmp->prev->next = tmp;
		current->prev = tmp;
	}
	items->size ++;

}

void unionDLL(dll *recipient, dll *donor) //merge two dlls
{
	if(donor->size > 0 && (recipient->size != 0))
	{
		recipient->tail->next = donor->head;
		donor->head->prev = recipient->tail;
		recipient->tail = donor->tail;
		recipient->size = addSizesDLL(recipient,donor);
		donor->size = 0;
		donor->head = NULL;
		donor->tail = NULL;
	}
	else if(donor->size > 0 && (recipient->size == 0))
	{
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = addSizesDLL(recipient,donor);
		donor->size = 0;
		donor->tail = NULL;
		donor->head = NULL;
	}
}

void *removeDLL(dll *items, int index) //removes and returns value from index of dll
{
        if(index < (sizeDLL(items) / 2))
        {
                return removeDLLLeft(items, index);
        }
        else
        {
                return removeDLLRight(items, index);
        }
}

void *removeDLLLeft(dll *items, int index) //seperate function for maximum effiency
{
        int c;
        dllnode *current = malloc(sizeof(dllnode));
	void *tmpValue;
        current = items->head;
	if(index == 0)
	{
		tmpValue = items->head->value;
		items->head = items->head->next;
		items->head->prev = NULL;
	}
	else
	{
		for(c = 0; c < (index); c++)
		{
			current = current->next;
		}

	tmpValue = current->value;
	current->prev->next = current->next;
	current->next->prev = current->prev;

	}
	items->size --;
	return tmpValue;
}

void *removeDLLRight(dll *items, int index) //seperate function for maximum effiency
{
        int c;
	void *tmpValue;
        dllnode *current = malloc(sizeof(dllnode));
        current = items->tail;
	if(index == (sizeDLL(items) - 1))
	{
		if(index == 0)
		{
			tmpValue = items->head->value;
			items->tail = NULL;
			items->head = NULL;
		}
		else
		{
		tmpValue = items->tail->value;
		items->tail = items->tail->prev;
		items->tail->next = NULL;
		}
	}
        else
	{
		for(c = 0;  c < ((sizeDLL(items) - index) - 1); c++)
		{
			current = current->prev;
		}
		tmpValue = current->value;
		current->prev->next = current->next;
		current->next->prev = current->prev;

	}
        items->size --;
	return tmpValue;
}


