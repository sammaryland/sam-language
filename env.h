#ifndef __ENV_INCLUDED__
#define __ENV_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lexeme.h"

LEXEME *newENV();
LEXEME *extendENV(LEXEME *, LEXEME *, LEXEME *);
LEXEME *newTable(LEXEME *, LEXEME *);
LEXEME *insert(LEXEME *, LEXEME *, LEXEME *);
LEXEME *getVal(LEXEME *, LEXEME *);
LEXEME *updateVal(LEXEME *, LEXEME *, LEXEME *);
LEXEME *getVars(LEXEME *);
LEXEME *getVals(LEXEME *);

int sameVar(LEXEME *, LEXEME *);
void displayEnv(LEXEME *);
char *getIdentifierName(LEXEME *);
void printOut(LEXEME *);
void printVals(LEXEME *, LEXEME *);

#endif
