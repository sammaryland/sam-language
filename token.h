#ifndef __TOKEN_INCLUDED__
#define __TOKEN_INCLUDED__

#include <stdio.h>

typedef struct TOKEN TOKEN;

extern TOKEN *newTOKEN(char);
extern char getTOKEN(TOKEN *);

#endif
