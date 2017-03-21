#include "bst.h"
#include <stdio.h>
//#include "comparator.h"
#include "integer.h"
#include "real.h"

int intComparator(void *a,void *b)
{
        int ai = getInteger(a);
        int bi = getInteger(b);

        int i = 0;
        if(ai < bi)
                i = -1;
        else if(ai > bi)
                i = 1;
        else if(ai == bi)
                i = 0;

        return i;

}

int main()
{
	printf("Starting");




	bst *tree = newBST(displayInteger,intComparator);

	insertBST(tree,newInteger(50));



	insertBST(tree,newInteger(30));
        insertBST(tree,newInteger(20));
        insertBST(tree,newInteger(40));
        insertBST(tree,newInteger(70));
        insertBST(tree,newInteger(60));
        insertBST(tree,newInteger(80));
	insertBST(tree,newInteger(90));
	insertBST(tree,newInteger(70));

	displayBST(stdout,tree);


	statisticsBST(tree,stdout);



}



