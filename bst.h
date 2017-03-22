#include <stdio.h>

#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

typedef struct bstNode
    {
        struct bstNode *left;
        struct bstNode *right;
        struct bstNode *parent;
        void *value;
    } bstNode;

typedef struct bst
    {
        bstNode *root;
        int size;
        void (*display)(FILE *,void *);
        int (*compare)(void *,void *);
    } bst;

extern bst *newBST(void (*)(FILE *,void *),int (*)(void *,void *));
extern bstNode *insertBST(bst *,void *);
extern int findBST(bst *,void *);
extern bstNode *findBSTNode(bst *,void *);
extern bstNode *swapToLeafBSTNode(bstNode *);
extern void pruneBSTNode(bst *,bstNode *);
extern int sizeBST(bst *);
extern void statisticsBST(bst *,FILE *);
extern void displayBST(FILE *,bst *);
extern void checkBST(bst *);                //optional
extern bstNode *newBSTNode(void *val);
extern bstNode *insertBSTNode(bstNode *node, void *val, int (*c)(void *,void *));
extern int findBSTHelper(bstNode *node, void *val, int (*c)(void *,void *));
extern bstNode *findBSTNodeHelper(bstNode *node, void *val, int (*c)(void *,void *));
extern int minBST(bstNode *node);
extern int maxBST(bstNode *node);
extern bstNode *findBSTMin(bstNode *node);
extern bstNode *findBSTMax(bstNode *node);

#endif
