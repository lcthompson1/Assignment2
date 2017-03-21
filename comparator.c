#include <stdio.h>
#include <string.h>
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
int realComparator(void *a,void *b)
{
	float af = getReal(a);
	float bf = getReal(b);

        int i = 0;
        if(af < bf)
                i = -1;
        else if(af > bf)
                i = 1;
        else if(af == bf)
                i = 0;

        return i;
}
int stringComparator(char *a,char *b)
{
	int i = 0;
	if((strcmp(a,b)) < 0)
		i = -1;
	else if((strcmp(a,b)) > 0)
		i = 1;
	else if((strcmp(a,b)) == 0)
		i = 0;

	return i;
}






