#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "real.h"

extern void Fatal(char *,...);

real *newReal(float x)
    {
    real *p = malloc(sizeof(real));
    if (p == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(-1);
    }
    p->value = x;
    return p;
    }

float getReal(real *v)
    {
    return v->value;
    }

float setReal(real *v,float x)
    {
    float old = v->value;
    v->value = x;
    return old;
    }

void displayReal(FILE *fp,void *v)
    {
    fprintf(fp,"%f",getReal(v));
    }

int compareReal(void *v,void *w)
    {
    return ((real *) v)->value - ((real *) w)->value;
    }

void freeReal(real *v)
    {
    free(v);
    }



