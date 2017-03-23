#include <stdlib.h>
#include "bst.h"
#include <stdio.h>

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
	bstNode *ret;
	if(sizeBST(tree) == 0)
	{
		tree->root = newBSTNode(val);
		ret = tree->root;
	}
	else
	{
		ret = insertBSTNode(tree->root,val,tree->compare);
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


bstNode *insertBSTNode(bstNode *node, void *val, int (*c)(void *,void *))
{
	if(node == NULL)
		return newBSTNode(val);
	else
	{
		bstNode *temp;

		if(c(val,node->value) <= 0)
		{
			temp = insertBSTNode(node->left,val,c);
			node->left = temp;
			temp->parent = node;
		}
		else
		{
			temp = insertBSTNode(node->right,val,c);
			node->right = temp;
			temp->parent = node;
		}
		return node;
	}
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
	if(node->left == NULL && node->right == NULL)
	{
		fprintf(stdout,"\nPruning\n");
		int comp = tree->compare(node->value,node->parent->value);
		fprintf(stdout,"\nstrcmp = %d\n",comp);
		if(comp < 0)
		{
			fprintf(stdout,"Case: prune is greater than parent\n");
			node->parent->right = NULL;
			node->parent = NULL;
		}
		if(comp >= 0)
		{
			fprintf(stdout,"Case: prune is less than or equal to parent\n");
			node->parent->left = NULL;
			node->parent = NULL;
		}
	}
	else
	{
		fprintf(stdout,"\nSwapping\n");
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

void inorder(bstNode *node, void (*d)(FILE *,void *),FILE *fp)
{
	if(node != NULL)
	{
		inorder(node->left,d,fp);
		d(fp,node->value);
		fprintf(fp,"	");
		inorder(node->right,d,fp);
	}
}

void displayBST(FILE *fp,bst *tree)
{
	inorder(tree->root,tree->display,fp);
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
