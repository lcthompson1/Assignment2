#include "bst.h"
#include <stdio.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "comparator.c"
#include "rbt.h"
#include "vbst.h"
#include "scanner.h"

void printString(FILE *fp,void *string)
{
	fprintf(fp,"%s",(char*)string);
}

void readFileVanilla(FILE *fpin, FILE *fpout)
{
	vbst *vbstree = newVBST(printString,stringComparator);
	while(1)
	{
		char *s = "";
		if(stringPending(fpin))
			s = readString(fpin);
		else
			s = readToken(fpin);
		if(feof(fpin))
			break;
		insertVBST(vbstree,(void*)s);
	}
	displayVBST(fpout,vbstree);
}

void readFileRB(FILE *fpin, FILE *fpout)
{
	rbt *rbtree = newRBT(printString,stringComparator);
        while(1)
        {
                char *s = "";
                if(stringPending(fpin))
                        s = readString(fpin);
                else
                        s = readToken(fpin);
                if(feof(fpin))
                        break;
                insertRBT(rbtree,(void*)s);
		displayRBT(fpout,rbtree);
        }
        displayRBT(fpout,rbtree);
}

int main(int argc, char *argv[])
{
	if(argc == 4)
	{
		FILE *fpout = stdout;
		FILE *fpin = fopen(argv[2], "r");
		if(strcmp("-v",argv[1]) == 0)
		{
			readFileVanilla(fpin,fpout);
		}
		else if(strcmp("-r",argv[1]) == 0)
		{
			readFileRB(fpin,fpout);
		}
		fclose(fpin);
	}
	if(argc == 5)
	{
		FILE *fpout;
		fpout = fopen(argv[4],"w");
		FILE *fpin = fopen(argv[2], "r");
                if(strcmp("-v",argv[1]) == 0)
                {
                        readFileVanilla(fpin,fpout);
                }
                else if(strcmp("-r",argv[1]) == 0)
                {
                        readFileRB(fpin,fpout);
                }
		fclose(fpout);
		fclose(fpin);
	}

/*
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

	vbst *tree = newVBST(printString,stringComparator);
	displayVBST(stdout,tree);

	insertVBST(tree,str1);
	insertVBST(tree,str2);
	insertVBST(tree,str3);
	insertVBST(tree,str4);
	insertVBST(tree,str5);
        insertVBST(tree,str6);
        insertVBST(tree,str7);
        insertVBST(tree,str8);
        insertVBST(tree,str9);
        insertVBST(tree,str10);
	displayVBST(stdout,tree);

	insertVBST(tree,str8);

	deleteVBST(tree,str8);
	deleteVBST(tree,str6);
	deleteVBST(tree,str7);

	displayVBST(stdout,tree);
	statisticsVBST(tree,stdout);

//	statisticsBST(tree,stdout);
//	fprintf(stdout,"\n\n");



//	swapToLeafBSTNode(tree->root);
//	pruneBSTNode(tree,tree->root->right->left);
//	fprintf(stdout,"\n\n\n");

//	fprintf(stdout,"\n");
//	displayBST(stdout,tree);

//	fprintf(stdout,"\n\n");
*/
}



