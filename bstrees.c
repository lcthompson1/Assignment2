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
	printf("Starting\n");

	char *str1 = "g";
	char *str2 = "c";
	char *str3 = "n";
	char *str4 = "b";
	char *str5 = "d";
	char *str6 = "i";
        char *str7 = "z";
        char *str8 = "a";
        char *str9 = "f";
        char *str10 = "j";


//	fprintf(stdout,"\nb cmp c: %d\n",strcmp(str2,str3));

	bst *tree = newBST(printString,stringComparator);

	insertBST(tree,str1);
	insertBST(tree,str2);
	insertBST(tree,str3);
	insertBST(tree,str4);
	insertBST(tree,str5);
        insertBST(tree,str6);
        insertBST(tree,str7);
        insertBST(tree,str8);
        insertBST(tree,str9);
        insertBST(tree,str10);

	displayBST(stdout,tree);


//	statisticsBST(tree,stdout);




//	pruneBSTNode(tree,tree->root->right);
//	pruneBSTNode(tree,tree->root->right);
//	fprintf(stdout,"\n\n\n");

//	fprintf(stdout,"\n");
//	displayBST(stdout,tree);

//	fprintf(stdout,"\n\n");
}



