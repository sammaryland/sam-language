/*
  Token Class
  Written by Sam Maryland
  January 21, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "token.h"

struct TOKEN
    {
    char value;
    };

TOKEN *
newTOKEN(char x)
    {
    TOKEN *p = malloc(sizeof(TOKEN));
    assert(p != 0);
    p->value = x;
    return p;
    }

char
getTOKEN(TOKEN *v)
    {
    return v->value;
    }