#include <stdlib.h>
#include <stdio.h>
#include "vbst.h"
#include "bst.h"

typedef struct vbstValue
{
	void *value;
	int freq;
	void (*display)(FILE *x, void *);
	int (*compare)(void *,void *);
}vbstValue;

vbstValue *newVBSTValue(void *value, void (*d)(FILE *fp, void *), int (*c)(void *,void *))
{
	vbstValue *vbstval = malloc(sizeof(vbstValue));
	if(vbstval == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}
	vbstval->value = value;
	vbstval->freq = 1;
	vbstval->display = d;
	vbstval->compare = c;
	return vbstval;
}

void displayVBSTValue(FILE *fp,void *passNode)
{
        vbstValue *node = passNode;
        fprintf(fp,"\"");
        node->display(fp,node->value);
        fprintf(fp,"\"");

        if(node->freq > 1)
        {
                fprintf(fp,"-%d-",node->freq);
        }
}

int compareVBSTValue(void *passNode1, void *passNode2)
{
        vbstValue *node1 = passNode1;
        vbstValue *node2 = passNode2;
        return node1->compare(node1->value,node2->value);
}

vbst *newVBST(void (*d)(FILE *,void *), int (*c)(void *,void *))
{
	vbst *vbstree = malloc(sizeof(vbst));
	if(vbstree == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}
	vbstree->tree = newBST(displayVBSTValue,compareVBSTValue);
	vbstree->display = d;
	vbstree->compare = c;
	vbstree->size = 0;
	vbstree->words = 0;

	return vbstree;
}

int findVBST(vbst *vbstree, void *value)
{
        vbstValue *temp = newVBSTValue(value,vbstree->display,vbstree->compare);
	bstNode *test = findBSTNode(vbstree->tree,(void*)temp);

	if(test == NULL)
		return 0;
	else
        	return ((vbstValue*)test->value)->freq;
}

bstNode *findVBSTNode(vbst *vbstree, void *value)
{
        vbstValue *temp = newVBSTValue(value,vbstree->display,vbstree->compare);
        return findBSTNode(vbstree->tree,(void*)temp);
}



void displayVBST(FILE *fp,vbst *vbstree)
{
        displayBST(fp,vbstree->tree);
}



void statisticsVBST(vbst *vbstree, FILE *fp)
{
        fprintf(fp,"Words/Phrases: %d\n",vbstree->words);
        fprintf(fp,"Nodes: %d\n",vbstree->size);
        statisticsBST(vbstree->tree,fp);
}

int sizeVBST(vbst *vbstree)
{
	return vbstree->size;
}

int wordsVBST(vbst *vbstree)
{
	return vbstree->words;
}

void insertVBST(vbst *vbstree,void *value)
{
	bstNode *temp = findVBSTNode(vbstree,value);
        if(temp == NULL)
        {
                vbstValue *tempValue = newVBSTValue(value,vbstree->display,vbstree->compare);
                insertBST(vbstree->tree,(void*)tempValue);
                vbstree->size ++;
                vbstree->words ++;
        }
        else
        {
                ((vbstValue*)temp->value)->freq ++;
                vbstree->words ++;
        }
}

void deleteVBST(vbst *vbstree,void *value)
{
	bstNode *temp = findVBSTNode(vbstree,value);
        if(temp == NULL)
        {
		fprintf(stderr,"Value not in tree\n");
        }
        else if(((vbstValue*)temp->value)->freq > 1)
        {
                ((vbstValue*)temp->value)->freq --;
                vbstree->words --;
        }
	else
	{
		pruneBSTNode(vbstree->tree,temp);
		vbstree->words --;
		vbstree->size --;
	}
}
