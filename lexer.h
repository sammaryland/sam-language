#ifndef LEXER
#define LEXER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void skipWhiteSpace(FILE *);
char getNextCharacter(FILE *);
int isWhiteSpace(char);
int getLineNo();

#endif 