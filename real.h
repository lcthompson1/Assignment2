#include <stdio.h>

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

typedef struct real
    {
    float value;
    } real;

extern real *newReal(float);
extern float getReal(real *);
extern float setReal(real *,float);
extern void displayReal(FILE *,void *);
extern int compareReal(void *,void *);
extern void freeReal(real *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif





