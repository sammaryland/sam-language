#include "env.h"
#include "types.h"
#include "parser.h"

LEXEME *newENV(){
  return extendENV(NULL, NULL, NULL);
}

LEXEME *extendENV(LEXEME *env, LEXEME *vars, LEXEME *vals){
  return cons(ENV, newTable(vars, vals), env);
}

LEXEME *newTable(LEXEME *vars, LEXEME *vals){
  return cons(TABLE, vars, vals);
}

LEXEME *insert(LEXEME *env, LEXEME *id, LEXEME *val){
  LEXEME *table = car(env);
  setCar(table, cons(I, id, car(table)));
  setCdr(table, cons(V, val, cdr(table)));
  return id;
}

LEXEME *getVal(LEXEME *env, LEXEME *id){
  while (env != NULL){
    LEXEME *vars = getVars(env);
    LEXEME *vals = getVals(env);
    while (vars != NULL){
      if (sameVar(id, car(vars))){
        return car(vals);
      }
      vars = cdr(vars);
      vals = cdr(vals);
    }
    env = cdr(env);
  }
  printf("UNKNOWN VARIABLE GET - %s\n", id -> string);
  exit(1);
  return NULL;
}

LEXEME *updateVal(LEXEME *var, LEXEME *newVal, LEXEME *env){
  while (env != NULL){
    LEXEME *table = car(env);
    LEXEME *vars = car(table);
    LEXEME *vals = cdr(table);
    while (vars != NULL){
      if (sameVar(var, car(vars))){
        return setCar(vals, newVal);
      }
      vars = cdr(vars);
      vals = cdr(vals);
    }
    env = cdr(env);
  }
  printf("UNKNOWN VARIABLE UPDATE - %s\n", var -> string);
  exit(1);
  return NULL;
}

LEXEME *getVars(LEXEME *env){
  return car(car(env));
}

LEXEME *getVals(LEXEME *env){
  return cdr(car(env));
}

int sameVar(LEXEME *l1, LEXEME *l2){
  return (0 == strcmp(getIdentifierName(l1), getIdentifierName(l2)));
}

void displayEnv(LEXEME *env){
  LEXEME *ids = getVars(env);
  LEXEME *values = getVals(env);
  printf("Table\n");
  printVals(ids, values);
  LEXEME *top = cdr(env);
  while (top != NULL){
    ids = getVars(top);
    values = getVals(top);
    printVals(ids, values);
    top = cdr(top);
  }
}

void printVals(LEXEME *ids, LEXEME *values){
  char *pad = "   ";
  char *bound = "  ->  ";
  while (ids != NULL) {
    printf("%s%s%s", pad, getIdentifierName(car(ids)), bound);
    printOut(car(values));
    if (cdr(values) == NULL && cdr(ids) != NULL) {
        fprintf(stderr, "Environment error: Malformed table has more identifiers than values.\n");
        exit(-1);
    }
    ids = cdr(ids);
    values = cdr(values);
  }
}

char *getIdentifierName(LEXEME *id){
  return id -> string;
}

void printOut(LEXEME *L){
  if (L == NULL) 
    printf("NULL (no lexeme)");
  else {
    if (strcmp(typeLEXEME(L), INTEGER) == 0)
      printf("%d", L->integer);
    else if (strcmp(typeLEXEME(L), DOUBLE) == 0)
      printf("%g", L->real);
    else if (strcmp(typeLEXEME(L), STRING) == 0 || strcmp(typeLEXEME(L), ID) == 0)
      printf("%s", L->string);
  }
  printf("\n");
}