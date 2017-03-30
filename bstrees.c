#include "bst.h"
#include <stdio.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "comparator.c"
#include "rbt.h"
#include "vbst.h"
#include <ctype.h>
#include "scanner.h"

void printString(FILE *fp,void *string)
{
	fprintf(fp,"%s",(char*)string);
}

void clean(char *str)
{
	unsigned long i = 0;
	unsigned long x = 0;
	char c;

	while((c = str[i++]) != '\0')
	{
		if(isalpha(c))
			str[x++] = tolower(c);
	}
	str[x] = '\0';
}

void readFileVanilla(FILE *fpin, FILE *fpout,FILE *commands)
{
	vbst *vbstree = newVBST(printString,stringComparator);
	while(!feof(fpin))
	{
		char *s = "";
		if(stringPending(fpin))
			s = readString(fpin);
		else
			s = readToken(fpin);
		if(feof(fpin))
			break;

		clean(s);

		if(strcmp(s,"") == 0)
			;
		else
		{
			insertVBST(vbstree,(void*)s);
		}
		if(feof(fpin))
			break;
	}

	while(!feof(commands))
	{
		char *s = "";
		s = readToken(commands);
		if(feof(commands))
			break;
		if(strcmp(s,"s") == 0)
		{
			displayVBST(fpout,vbstree);
		}
		else if(strcmp(s,"r") == 0)
		{
			statisticsVBST(vbstree,fpout);
		}
		else if(strcmp(s,"i") == 0)
		{
			char *c = "";
			if(stringPending(commands))
				c = readString(commands);
			else
				c = readToken(commands);

			clean(c);

 			if(strcmp(c,"") == 0)
                        	;
                	else
                	{
                        	insertVBST(vbstree,(void*)c);
                	}
		}
		else if(strcmp(s,"d") == 0)
		{
                        char *c = "";
                        if(stringPending(commands))
                                c = readString(commands);
                        else
                                c = readToken(commands);

                        clean(c);

                        if(strcmp(c,"") == 0)
                                ;
                        else
                        {
                                deleteVBST(vbstree,(void*)c);
                        }
		}
		else if(strcmp(s,"f") == 0)
		{
			char *c = "";
                        if(stringPending(commands))
                                c = readString(commands);
                        else
                                c = readToken(commands);

                        clean(c);

                        if(strcmp(c,"") == 0)
                                ;
                        else
                        {
				int freq = findVBST(vbstree,(void*)c);
				fprintf(fpout,"Frequency of \"%s\": %d\n",c,freq);
                        }
		}
		if(feof(commands))
			break;
	}
}

void readFileRB(FILE *fpin, FILE *fpout,FILE *commands)
{
	rbt *rbtree = newRBT(printString,stringComparator);
        while(!feof(fpin))
        {
                char *s = "";
                if(stringPending(fpin))
                        s = readString(fpin);
                else
                        s = readToken(fpin);

		if(feof(fpin))
			break;

                clean(s);

		if(strcmp(s,"") == 0)
                        ;
                else
                {
                        insertRBT(rbtree,(void*)s);
                }

                if(feof(fpin))
                        break;
        }

        while(!feof(commands))
        {
                char *s = "";
                s = readToken(commands);
                if(feof(commands))
                        break;
                if(strcmp(s,"s") == 0)
                {
                        displayRBT(fpout,rbtree);
                }
                else if(strcmp(s,"r") == 0)
                {
                        statisticsRBT(rbtree,fpout);
                }
                else if(strcmp(s,"i") == 0)
                {
                        char *c = "";
                        if(stringPending(commands))
                                c = readString(commands);
                        else
                                c = readToken(commands);

                        clean(c);

                        if(strcmp(c,"") == 0)
                                ;
                        else
                        {
                                insertRBT(rbtree,(void*)c);
                        }
                }
                else if(strcmp(s,"d") == 0)
                {
                        char *c = "";
                        if(stringPending(commands))
                                c = readString(commands);
                        else
                                c = readToken(commands);

                        clean(c);

                        if(strcmp(c,"") == 0)
                                ;
                        else
                        {
                                deleteRBT(rbtree,(void*)c);
                        }
                }
                else if(strcmp(s,"f") == 0)
                {
                        char *c = "";
                        if(stringPending(commands))
                                c = readString(commands);
                        else
                                c = readToken(commands);

                        clean(c);

                        if(strcmp(c,"") == 0)
                                ;
                        else
                        {
                                int freq = findRBT(rbtree,(void*)c);
                                fprintf(fpout,"Frequency of \"%s\": %d\n",c,freq);
                        }
                }
                if(feof(commands))
                        break;
        }

}

int main(int argc, char *argv[])
{
	if(argc == 4)
	{
		FILE *fpout = stdout;
		FILE *commands = fopen(argv[3],"r");
		FILE *fpin = fopen(argv[2], "r");
		if(strcmp("-v",argv[1]) == 0)
		{
			readFileVanilla(fpin,fpout,commands);
		}
		else if(strcmp("-r",argv[1]) == 0)
		{
			readFileRB(fpin,fpout,commands);
		}
		fclose(fpin);
		fclose(commands);
	}
	if(argc == 5)
	{
		FILE *fpout = fopen(argv[4],"w");
		FILE *commands = fopen(argv[3],"r");
		FILE *fpin = fopen(argv[2], "r");
                if(strcmp("-v",argv[1]) == 0)
                {
                        readFileVanilla(fpin,fpout,commands);
                }
                else if(strcmp("-r",argv[1]) == 0)
                {
                        readFileRB(fpin,fpout,commands);
                }
		fclose(fpout);
		fclose(commands);
		fclose(fpin);
	}

}



