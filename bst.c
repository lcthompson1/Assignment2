#include <stdlib.h>
#include "bst.h"
#include <stdio.h>
#include "queue.h"

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *))
{
	bst *tree = malloc(sizeof(bst));
	if(tree == 0)
	{
		fprintf(stderr,"out of memory");
		exit(-1);
	}
	tree->root = NULL;
	tree->size = 0;
	tree->display = d;
	tree->compare = c;
	return tree;

}

bstNode *newBSTNode(void *val)
{
        bstNode *tmp = malloc(sizeof(bstNode));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->parent = NULL;
        tmp->value = val;

        return tmp;
}

bstNode *insertBSTNode(bstNode *node, void *val, int (*c)(void *,void *),bstNode **address)
{
        if(node == NULL)
	{
                bstNode *temp = newBSTNode(val);
                *address = temp;
                return temp;
	}
        else
        {

                if(c(val,node->value) <= 0)
                {
                        node->left = insertBSTNode(node->left,val,c,address);
                        node->left->parent = node;
                }
                else
                {
                        node->right = insertBSTNode(node->right,val,c,address);
                        node->right->parent = node;
                }
                return node;
        }
}


bstNode *insertBST(bst *tree,void *val)
{
	bstNode *ret;
	bstNode *address = NULL;
	if(sizeBST(tree) == 0)
	{
		tree->root = newBSTNode(val);
		tree->root->parent = tree->root;
		ret = tree->root;
	}
	else
	{
		ret = insertBSTNode(tree->root,val,tree->compare,&address);
		ret = address;
	}
	tree->size += 1;
	return ret;
}

bstNode *findBSTMax(bstNode *node)
{
        bstNode *cur = node;

        while(cur->right != NULL)
                cur = cur->right;

        return cur;

}

bstNode *findBSTMin(bstNode *node)
{
        bstNode *cur = node;

        while(cur->left != NULL)
                cur = cur->left;

        return cur;
}


int findBSTHelper(bstNode *node, void *val, int (*c)(void *,void *))
{
        if(node == NULL)
                return 0;
        if(c(node->value,val) == 0)
                return 1;
        if(c(node->value,val) > 1)
                return findBSTHelper(node->left,val,c);
        return findBSTHelper(node->left,val,c);
}


int findBST(bst *tree,void *val)
{
	if(sizeBST(tree) == 0)
	{
		return 0;
	}
	else
	{
		return findBSTHelper(tree->root,val,tree->compare);
	}
}

bstNode *findBSTNodeHelper(bstNode *node, void *val, int (*c)(void *,void *))
{
        if(node == NULL)
                return NULL;
        else if(c(node->value,val) == 0)
                return node;
        else if(c(node->value,val) > 0)
                return findBSTNodeHelper(node->left,val,c);
	else if(c(node->value,val) < 0)
		return findBSTNodeHelper(node->right,val,c);
        return findBSTNodeHelper(node->right,val,c);
}

bstNode *findBSTNode(bst *tree,void *val)
{
	if(sizeBST(tree) == 0)
		return NULL;
	else
		return findBSTNodeHelper(tree->root,val,tree->compare);
}


bstNode *swapToLeafBSTNode(bstNode *node)
{
	bstNode *temp;
	bstNode *swap = newBSTNode(node->value);

	if(node->left != NULL)
	{
		temp = findBSTMax(node->left);
	}
	else if(node->right != NULL)
	{
		temp = findBSTMin(node->right);
	}

	node->value = temp->value;
	temp->value = swap->value;

	return temp;
}

void pruneBSTNode(bst *tree,bstNode *node)
{
	if(node->left == NULL && node->right == NULL)
	{
		int comp = tree->compare(node->value,node->parent->value);
		if(node->parent->right == NULL && node->parent->left != NULL)
		{
			node->parent->left = NULL;
			node->parent = NULL;
		}
		else if(node->parent->left == NULL && node->parent->right != NULL)
		{
			node->parent->right = NULL;
			node->parent = NULL;
		}
		else if(comp > 0)
		{
			node->parent->right = NULL;
			node->parent = NULL;
		}
		else if(comp <= 0)
		{
			node->parent->left = NULL;
			node->parent = NULL;
		}
	}
	else
	{
		pruneBSTNode(tree,swapToLeafBSTNode(node));
	}
	tree->size --;
}

int sizeBST(bst *tree)
{
	return tree->size;
}

int minBST(bstNode *node)
{
        if(node == NULL)
                return 0;
        else
        {
                int left = minBST(node->left);
                int right = minBST(node->right);

                if(left < right)
                        return left + 1;
                else
                        return right + 1;
        }
}

int maxBST(bstNode *node)
{
        if(node == NULL)
                return 0;
        else
        {
                int left = maxBST(node->left);
                int right = maxBST(node->right);

                if(left > right)
                        return left + 1;
                else
                        return right + 1;
        }
}

void statisticsBST(bst *tree,FILE *fp)
{
	fprintf(fp,"Minimum Depth: %d\nMaximum Depth: %d\n",minBST(tree->root),maxBST(tree->root));
}

void levelOrder(bstNode *node, void (*d)(FILE *,void *),FILE *fp, int (*c)(void *,void *))
{
	if(node == NULL)
	{
		fprintf(fp,"0: \n");
		return;
	}

	queue *temp = newQueue(d);

	enqueue(temp,node);
	int level = 0;

	while(1)
	{

		int count = sizeQueue(temp);
		if(count == 0)
			break;

		fprintf(fp,"%d:",level);

		while(count > 0)
		{
			bstNode *newNode = dequeue(temp);
                        fprintf(fp," ");
			if(newNode->left == NULL && newNode->right == NULL)
				fprintf(fp,"=");
			d(fp,newNode->value);
			fprintf(fp,"(");
			d(fp,newNode->parent->value);
			fprintf(fp,")-");

			if(newNode == newNode->parent)
				;
			else if(c(newNode->value,newNode->parent->value) > 0)
				fprintf(fp,"r");
			else if(c(newNode->value,newNode->parent->value) <= 0)
				fprintf(fp,"l");


			if(newNode->left != NULL)
				enqueue(temp,newNode->left);
			if(newNode->right != NULL)
				enqueue(temp,newNode->right);

			count --;
		}
		fprintf(fp,"\n");
		level ++;
	}
}

void displayBST(FILE *fp,bst *tree)
{
	levelOrder(tree->root,tree->display,fp,tree->compare);
}



