#ifndef LEX
#define LEX

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct lexeme LEXEME;

struct lexeme {
  char *type;
  char *string;
  int integer;
  double real;
  int b;

  LEXEME **aval;
  int avalSize;
  LEXEME *(*fval)(LEXEME *, LEXEME *);
  FILE *fp;

  LEXEME *left;
  LEXEME *right;
};

LEXEME *lex(FILE *);
LEXEME *newLEXEME(char *);
LEXEME *badLEXEME(char);
LEXEME *lexVAR(FILE *, char);
LEXEME *lexNUM(FILE *, char);
LEXEME *lexSTRING(FILE *);
void displayLEXEME(LEXEME *);

LEXEME *cons(char *, LEXEME *, LEXEME *);
LEXEME *car(LEXEME *);
LEXEME *cdr(LEXEME *);
LEXEME *setCar(LEXEME *, LEXEME *);
LEXEME *setCdr(LEXEME *, LEXEME *);

LEXEME *newREALLEXEME(double);
LEXEME *newINTLEXEME(int);
LEXEME *newBOOLLEXEME(int);

#endif 