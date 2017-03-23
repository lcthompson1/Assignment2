#include "bst.h"
#include <stdio.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "comparator.c"


void printString(FILE *fp,void *string)
{
	fprintf(fp,"%s",(char*)string);
}

int main()
{
	printf("Starting");

	char *str1 = "c";
	char *str2 = "b";
	char *str3 = "d";
	char *str4 = "e";
	char *str5 = "a";

	fprintf(stdout,"\nb cmp c: %d\n",strcmp(str2,str3));

	bst *tree = newBST(printString,stringComparator);

	insertBST(tree,str1);
	insertBST(tree,str2);
	insertBST(tree,str3);
	insertBST(tree,str4);
	insertBST(tree,str5);


	displayBST(stdout,tree);


	statisticsBST(tree,stdout);




	pruneBSTNode(tree,tree->root->right);
//	pruneBSTNode(tree,tree->root->right);
//	fprintf(stdout,"\n\n\n");

	fprintf(stdout,"\n");
	displayBST(stdout,tree);

//	fprintf(stdout,"\n\n");
}



