#include <stdlib.h>
#include <stdio.h>
#include "rbt.h"
#include "bst.h"


typedef struct rbtValue
{
	void *value;
	int freq;
	int color;
	void (*display)(FILE *x, void *);
	int (*compare)(void *,void *);
}rbtValue;

rbtValue *newRBTValue(void *value,void (*d)(FILE *fp, void *),int (*c)(void *,void *))
{
	rbtValue *rbvalue = malloc(sizeof(rbtValue));
	if(rbvalue == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}
	rbvalue->value = value;
	rbvalue->freq = 1;
	rbvalue->color = 1;
	rbvalue->display = d;
	rbvalue->compare = c;
	return rbvalue;
}

void displayRBTValue(FILE *fp,void *passNode)
{
        rbtValue *node = passNode;
        fprintf(fp,"\"");
        node->display(fp,node->value);
        fprintf(fp,"\"-");

        if(node->freq > 1)
        {
                fprintf(fp,"%d-",node->freq);
        }

	if(node->color == 0)
		fprintf(fp,"B");
	else if(node->color == 1)
		fprintf(fp,"R");
}

int compareRBTValue(void *passNode1, void *passNode2)
{
        rbtValue *node1 = passNode1;
        rbtValue *node2 = passNode2;
        return node1->compare(node1->value,node2->value);
}


rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *))
{
	rbt *rbtree = malloc(sizeof(rbt));
	if(rbtree == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}
	rbtree->tree = newBST(displayRBTValue,compareRBTValue);
	rbtree->display = d;
	rbtree->compare = c;
	rbtree->size = 0;
	rbtree->words = 0;

	return rbtree;
}

void displayRBT(FILE *fp,rbt *rbtree)
{
	displayBST(fp,rbtree->tree);
}

int sizeRBT(rbt *rbtree)
{
	return rbtree->size;
}

int wordsRBT(rbt *rbtree)
{
	return rbtree->words;
}

void statisticsRBT(rbt *rbtree, FILE *fp)
{
	fprintf(fp,"Words/Phrases: %d\n",rbtree->words);
	fprintf(fp,"Nodes: %d\n",rbtree->size);
	statisticsBST(rbtree->tree,fp);
}

int findRBT(rbt *rbtree, void *value)
{
	rbtValue *temp = newRBTValue(value,rbtree->display,rbtree->compare);
	return findBST(rbtree->tree,(void*)temp);
}

bstNode *findRBTNode(rbt *rbtree, void *value)
{
	rbtValue *temp = newRBTValue(value,rbtree->display,rbtree->compare);
	return findBSTNode(rbtree->tree,(void*)temp);
}

bstNode *parent(bstNode *node)
{
	return node->parent;
}

bstNode *uncle(bstNode *node)
{
	if(node->parent == node->parent->parent->left)
		return node->parent->parent->right;
	else
		return node->parent->parent->left;
}

bstNode *grandparent(bstNode *node)
{
	return node->parent->parent;
}


int color(bstNode *node)
{
	rbtValue *temp = node->value;
	return temp->color;
}

void changeColor(bstNode *node,int color)
{
	((rbtValue*)node->value)->color = color;
}

void leftRotate(bst *tree, bstNode *node)
{
        bstNode *y = node->right;
        node->right = y->left;
        if(y->left != NULL)
                y->left->parent = node;

        y->parent = node->parent;
        if(node->parent == node)
                tree->root = y;
        else
        {
                if(node == (node->parent->left))
                        node->parent->left = y;
                else
                        node->parent->right = y;
        }
        y->left = node;
        node->parent = y;
}

void rightRotate(bst *tree, bstNode *node)
{
        bstNode *y = node->left;
        node->left = y->right;
        if(y->right != NULL)
                y->right->parent = node;

        y->parent = node->parent;
        if(node->parent == node)
                tree->root = y;
        else
        {
                if(node == (node->parent->right))
                        node->parent->right = y;
                else
                        node->parent->left = y;
        }
        y->right = node;
        node->parent = y;
}


void insertionFixup(bst *tree,bstNode *node)
{
        while((node != tree->root) && ((color(node->parent)) == 1))
        {
		if(node->parent == node->parent->parent->left)
		{
			bstNode *y = node->parent->parent->right;
			fprintf(stdout,"\nUncle address: %d Uncle color: %d\n",node,((rbtValue*)y->value)->color);
			if(color(y) == 1)
			{
				changeColor(node->parent,0);
				changeColor(y,0);
				changeColor(node->parent->parent,1);

				node = node->parent->parent;
			}
			else
			{
				if(node == node->parent->right)
				{
					node = node->parent;
					leftRotate(tree,node);
				}

				changeColor(node->parent,0);
				changeColor(node->parent->parent,1);
				rightRotate(tree,node->parent->parent);
			}
		}
		else
		{
                       bstNode *y = node->parent->parent->left;
                        if(color(y) == 1)
                        {
                                changeColor(node->parent,0);
                                changeColor(y,0);
                                changeColor(node->parent->parent,1);

                                node = node->parent->parent;
                        }
                        else
                        {
                                if(node == node->parent->left)
                                {
                                        node = node->parent;
                                        rightRotate(tree,node);
                                }

                                changeColor(node->parent,0);
                                changeColor(node->parent->parent,1);
                                leftRotate(tree,node->parent->parent);
                        }
		}

        }
	changeColor(tree->root,0);
}

void insertRBT(rbt *rbtree, void *value)
{
	bstNode *temp = findRBTNode(rbtree,value);
	if(temp == NULL)
	{
		rbtValue *tempValue = newRBTValue(value,rbtree->display,rbtree->compare);
		bstNode *inserted = insertBST(rbtree->tree,(void*)tempValue);
		insertionFixup(rbtree->tree,inserted);
		rbtree->size ++;
		rbtree->words ++;
	}
	else
	{
		((rbtValue*)temp->value)->freq ++;
		rbtree->words ++;
	}
}


void deleteRBT(rbt *rbtree,void *value)
{
	bstNode *temp = findRBTNode(rbtree,value);
	if(temp == NULL)
		fprintf(stderr,"Not located in the tree.\n");
	else if(((rbtValue*)temp->value)->freq > 1)
		((rbtValue*)temp->value)->freq --;
}

