/*
  Lexeme
  Written by Sam Maryland
  January 21, 2019
*/

#include "types.h"
#include "lexer.h"
#include "lexeme.h"
#include "stack.h"
#include "token.h"

LEXEME *newLEXEME(char *s){
  LEXEME *items = malloc(sizeof(LEXEME));
  items -> type = s;
  items -> string = NULL;
  items -> integer = 0;
  items -> real = 0;
  items -> b = 0;
  items -> left = NULL;
  items -> right = NULL;
  return items;
}

LEXEME *badLEXEME(char ch){
  LEXEME *items = newLEXEME(BAD_LEX);
  char *bad = malloc(sizeof(char *));
  bad[0] = ch;
  items -> string = bad;
  items -> integer = __LINE__;
  return items;
}

LEXEME *lexVAR(FILE *fp, char ch){
  STACK *items = newSTACK(0, 0);
  push(items, newTOKEN(ch));
  char n = getNextCharacter(fp);
  while (!isWhiteSpace(n) && isalnum(n) && n != EOF && n != '\n'){
    push(items, newTOKEN(n));
    n = getNextCharacter(fp);
  }
  ungetc(n, fp);
  char *string = malloc(sizeof(char) * sizeSTACK(items) + 1);
  int size = sizeSTACK(items);
  for (int i = size - 1; i >= 0; i--){
    char c = getTOKEN(pop(items));
    string[i] = c;
  }
  string[size] = '\0';
  LEXEME *new;
  freeSTACK(items);
  // Check if string is a keyword
  if (strcmp(string, "FUNC") == 0){
    new = newLEXEME(FUNC);
  }
  else if (strcmp(string, "VAR") == 0){
    new = newLEXEME(VAR);
  }
  else if (strcmp(string, "RETURN") == 0){
    new = newLEXEME(RETURN);
  }
  else if (strcmp(string, "WHILE") == 0){
    new = newLEXEME(WHILE);
  }
  else if (strcmp(string, "FOR") == 0){
    new = newLEXEME(FOR);
  }
  else if (strcmp(string, "NOT") == 0){
    new = newLEXEME(NOT);
  }
  else if (strcmp(string, "IF") == 0){
    new = newLEXEME(IF);
  }
  else if (strcmp(string, "ELSE") == 0){
    new = newLEXEME(ELSE);
  }
  else if (strcmp(string, "STRUCT") == 0){
    new = newLEXEME(STRUCT);
  }
  else if (strcmp(string, "NEW") == 0){
    new = newLEXEME(NEW);
  }
  else if (strcmp(string, "ARR") == 0){
    new = newLEXEME(ARR);
  }
  else if (strcmp(string, "PRINT") == 0){
    new = newLEXEME(PRINT);
  }
  else if (strcmp(string, "LAMBDA") == 0){
    new = newLEXEME(LAMBDA);
  }
  else if (strcmp(string, "CLA") == 0){
    new = newLEXEME(CLA);
  }
  else if (strcmp(string, "GETINT") == 0){
    new = newLEXEME(GETINT);
  }
  // If not, it is a variable
  else {
    new = newLEXEME(ID);
    new -> string = string;
  }
  return new;
}

LEXEME *lexNUM(FILE *fp, char ch){
  int dec = 0;
  STACK *items = newSTACK(0, 0);
  push(items, newTOKEN(ch));
  char n = getNextCharacter(fp);
  while ((isdigit(n) && !isWhiteSpace(n) && n != EOF) || n == '.'){
    if (n == '.'){dec = 1;}
    push(items, newTOKEN(n));
    n = getNextCharacter(fp);
  }
  ungetc(n, fp);
  char *num = malloc(sizeof(char) * sizeSTACK(items) + 1);
  int size = sizeSTACK(items);
  for (int i = size - 1; i >= 0; i--){
    char c = getTOKEN(pop(items));
    num[i] = c;
  }
  num[size] = '\0';
  LEXEME *new;
  if (dec == 1){
    new = newLEXEME(DOUBLE);
    new -> real = atof(num);
  } 
  else{ 
    new = newLEXEME(INTEGER);
    new -> integer = atoi(num);
  }
  freeSTACK(items);
  return new;
}

LEXEME *lexSTRING(FILE *fp){
  STACK *items = newSTACK(0, 0);
  char n = getNextCharacter(fp);
  while (n != '\"'){
    push(items, newTOKEN(n));
    n = getNextCharacter(fp);
  }
  char *string = malloc(sizeof(char) * sizeSTACK(items) + 1);
  int size = sizeSTACK(items);
  for (int i = size - 1; i >= 0; i--){
    char c = getTOKEN(pop(items));
    string[i] = c;
  }
  string[size] = '\0';
  LEXEME *new = newLEXEME(STRING);
  new -> string = string;
  freeSTACK(items);
  return new;
}

void displayLEXEME(LEXEME *l){
  char *t = l -> type;
  if (strcmp(t, "INTEGER") == 0){
    printf("%s %d\n", t, l -> integer);
  }
  else if (strcmp(t, "DOUBLE") == 0){
    printf("%s %g\n", t, l -> real);
  }
  else if (strcmp(t, "STRING") == 0 || strcmp(t, "ID") == 0){
    printf("%s %s\n", t, l -> string);
  }
  else if (strcmp(t, "BAD_LEX") == 0){
    printf("%s: Offending Character is '%s' on line %d\n", t, l -> string, getLineNo());
    exit(2);
  }
  else if (strcmp(t, "NEWLINE") != 0){
    printf("%s\n", t);
  }
}

LEXEME *cons(char *t, LEXEME *l, LEXEME *r){
  LEXEME *n = newLEXEME(t);
  n -> left = l;
  n -> right = r;
  return n;
}

LEXEME *car(LEXEME *l){
  return l -> left;
}

LEXEME *cdr(LEXEME *l){
  return l -> right;
}

LEXEME *setCar(LEXEME *l, LEXEME *left){
  l -> left = left;
  return l;
}

LEXEME *setCdr(LEXEME *l, LEXEME *right){
  l -> right = right;
  return l;
}

LEXEME *newREALLEXEME(double i){
  LEXEME *l = newLEXEME(DOUBLE);
  l -> real = i;
  return l;
}

LEXEME *newINTLEXEME(int i){
  LEXEME *l = newLEXEME(INTEGER);
  l -> integer = i;
  return l;
}

LEXEME *newBOOLLEXEME(int i){
  LEXEME *l = newLEXEME(BOOLEAN);
  l -> b = i;
  return l;
}