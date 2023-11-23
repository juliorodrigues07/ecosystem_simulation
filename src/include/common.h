#ifndef __COMMON__
#define __COMMON__

#include <limits.h>

#define FOREVER INT_MAX

typedef struct cell {
    int type;
    union {
        unsigned int age_rabbit;
        unsigned int age_fox;
    };
    union {
        unsigned hunger_fox;
    };
} cell;

typedef struct environment {
    unsigned int rabbit_gen;
    unsigned int fox_gen;
    unsigned int fox_food;
    unsigned int n_gen;
    unsigned int r;
    unsigned int c;
    unsigned int n;
    cell **spaces;
} environment;

#endif
