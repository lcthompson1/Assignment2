#include <stdlib.h>
#include "bst.h"
#include <stdio.h>
#include "scanner.h"

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

bstNode *insertBST(bst *tree,void *val)
{
	bstNode *ret = newBSTNode(val);
	if(sizeBST(tree) == 0)
	{
		tree->root = newBSTNode(val);
	}
	else
	{
		insertBSTNode(tree->root,val,tree->compare);
	}
	tree->size += 1;
	return ret;
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

bstNode *newBSTNodePar(void *val, bstNode *par)
{
	bstNode *tmp = malloc(sizeof(bstNode));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->parent = par;
        tmp->value = val;

        return tmp;

}

bstNode *insertBSTNode(bstNode *node, void *val, int (*c)(void *,void *))
{
	if(node == NULL)
		return newBSTNodePar(val,node);
	if(c(val,node->value)<0)
		node->left = insertBSTNode(node->left, val, c);
	else if(c(val,node->value) > 0)
		node->right = insertBSTNode(node->right, val, c);
	return node;

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

bstNode *findBSTNode(bst *tree,void *val)
{
	if(sizeBST(tree) == 0)
		return 0;
	else
		return findBSTNodeHelper(tree->root,val,tree->compare);
}

bstNode *findBSTNodeHelper(bstNode *node, void *val, int (*c)(void *,void *))
{
        if(node == NULL)
                return 0;
        if(c(node->value,val) == 0)
                return node;
        if(c(node->value,val) > 1)
                return findBSTNodeHelper(node->left,val,c);
        return findBSTNodeHelper(node->left,val,c);
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
	fprintf(stdout,"Running\n");
	if(node->left == NULL && node->right == NULL)
	{
		fprintf(stdout,"Case 1\n");
		int comp = tree->compare(node->value,node->parent->value);
		if(comp >= 0)
			node->parent->right = NULL;
		if(comp < 0)
			node->parent->left = NULL;
	}
	else
	{
		fprintf(stdout,"Case 2\n");
		pruneBSTNode(tree,swapToLeafBSTNode(node));
	}
}

int sizeBST(bst *tree)
{
	return tree->size;
}

void statisticsBST(bst *tree,FILE *fp)
{
	fprintf(fp,"Minimum Depth: %d\nMaximum Depth: %d\n",minBST(tree->root),maxBST(tree->root));
}

void inorder(bstNode *node, void (*d)(FILE *,void *))
{
	if(node != NULL)
	{
		inorder(node->left,d);
		d(stdout,node->value);
		fprintf(stdout,"	");
		inorder(node->right,d);
	}
}

void displayBST(FILE *fp,bst *tree)
{
	inorder(tree->root,tree->display);
}

void checkBST(bst *tree)
{
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
