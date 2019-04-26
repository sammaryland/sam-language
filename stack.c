#include "stack.h"
#include "dll.h"

struct stack{
  DLL *pointer;
  void (*d)(void *,FILE *);
  void (*f)(void *);
};

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
  STACK *items = malloc(sizeof(STACK));
  assert(items != 0);
  items -> pointer = newDLL(d, f);
  items -> d = d;
  items -> f = f;
  return items;
}

void push(STACK *items,void *value){
  insertDLL(items -> pointer, 0, value);
  return;
}

void *pop(STACK *items){
  assert(sizeSTACK(items) > 0);
  void *val = removeDLL(items -> pointer, 0);
  return val;
}

void *peekSTACK(STACK *items){
  assert(sizeSTACK(items) > 0);
  return getDLL(items -> pointer, 0);
}

int sizeSTACK(STACK *items){
  return sizeDLL(items -> pointer);
}

void displaySTACK(STACK *items,FILE *fp){
  fprintf(fp, "|");
  for (int i = 0; i < sizeSTACK(items); i++){
    items -> d(getDLL(items -> pointer, i), fp);
    if (i != sizeSTACK(items) - 1){fprintf(fp, ",");}
  }
  fprintf(fp, "|");
  return;
}

void displaySTACKdebug(STACK *items,FILE *fp){
  displayDLLdebug(items -> pointer, fp);
}

void freeSTACK(STACK *items){
  freeDLL(items -> pointer);
  free(items);
}
