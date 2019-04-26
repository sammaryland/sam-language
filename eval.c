#include "eval.h"
#include <assert.h>

LEXEME *addBuiltIn(LEXEME *env, char *name, LEXEME *(*f)(LEXEME *, LEXEME *)){
  LEXEME *l = newLEXEME(BUILTIN);
  l -> fval = f;
  LEXEME *i = newLEXEME(ID);
  i -> string = name;
  return insert(env, i, l);
}

LEXEME *addBuiltIns(LEXEME *env){
  addBuiltIn(env, "CLA", evalCLA);
  addBuiltIn(env, "openFile", openFile);
  addBuiltIn(env, "readInt", readInt);
  addBuiltIn(env, "notFileEnd", notFileEnd);
  addBuiltIn(env, "closeFile", closeFile);
  addBuiltIn(env, "PRINT", evalPrint);
  addBuiltIn(env, "array", evalArray);
  addBuiltIn(env, "arrayOfSize", evalArrayOfSize);
  addBuiltIn(env, "sizeArray", evalSizeArray);
  addBuiltIn(env, "setArray", evalSetArray);
  addBuiltIn(env, "getArray", evalGetArray);
  return env;
}

LEXEME *eval(LEXEME *tree, LEXEME *env){
  char *t = typeLEXEME(tree);
  if (t == STRING){
    return tree;
  }
  else if (t == INTEGER){
    return tree;
  }
  else if (t == DOUBLE){
    return tree;
  }
  else if (t == ARRAY){
    return tree;
  }
  else if (t == CLOSURE){
    return tree;
  }
  else if (t == PLUS){
    return evalSimpleOp(tree, env);
  }
  else if (t == MINUS){
    return evalSimpleOp(tree, env);
  }
  else if (t == UMINUS){
    return evalUMINUS(tree, env);
  }
  else if (t == TIMES){
    return evalSimpleOp(tree, env);
  }
  else if (t == DIVIDE){
    return evalSimpleOp(tree, env);
  }
  else if (t == GTHE){
    return evalSimpleOp(tree, env);
  }
  else if (t == LTHE){
    return evalSimpleOp(tree, env);
  }
  else if (t == GTH){
    return evalSimpleOp(tree, env);
  }
  else if (t == LTH){
    return evalSimpleOp(tree, env);
  }
  else if (t == EQUALS){
    return evalSimpleOp(tree, env);
  }
  else if (t == NOTEQUAL){
    return evalSimpleOp(tree, env);
  }
  else if (t == AND){
    return evalSimpleOp(tree, env);
  }
  else if (t == OR){
    return evalSimpleOp(tree, env);
  }
  else if (t == LPAREN){
    return eval(tree -> right, env);
  }
  else if (t == SET){
    return evalSET(tree, env);
  }
  else if (t == PROGRAM){
    return evalProgram(tree, env);
  }
  else if (t == ID){
    return evalID(tree, env);
  }
  else if (t == CALL){
    return evalCall(tree, env);
  }
  else if (t == FUNC){
    return evalFuncDef(tree, env);
  }
  else if (t == STRUCTDEF){
    return evalStructDef(tree, env);
  }
  else if (t == VAR){
    return evalVarDef(tree, env);
  }
  else if (t == BLOCK){
    return evalBlock(tree, env);
  }
  else if (t == STATEMENTLIST){
    return evalStatementList(tree, env);
  }
  else if (t == RETURN){
    return evalReturn(tree, env);
  }
  else if (t == CLA){
    return evalCLA(tree, env);
  }
  else if (t == PRINTSTATEMENT){
    return evalPrint(tree, env);
  }
  else if (t == IF){
    return evalIf(tree, env);
  }
  else if (t == ELSE){
    return evalELSE(tree, env);
  }
  else if (t == LAMBDA){
    return evalLambda(tree, env);
  }
  else if (t == LAMBDACALL){
    return evalLambdaCall(tree, env);
  }
  else if (t == WHILE){
    return evalWhile(tree, env);
  }
  else if (t == PLUSPLUS || t == MINUSMINUS){
    return evalUnaryOp(tree, env);
  }
  else if (t == DOT){
    return evalDot(tree, env);
  }
  else if (t == COMMENT){
    return NULL;
  }
  else {
    if (t != NULL){printf("Haven't eval %s yet\n", t);}
    return NULL;
  }
}

// NON-SIMPLE OPERATIONS

LEXEME *evalUMINUS(LEXEME *tree, LEXEME *env){
  LEXEME *a = eval(tree -> right, env);
  a -> integer *= -1;
  return a;
}

LEXEME *evalCLA(LEXEME *tree, LEXEME *env){
  (void)(env);
  int a = tree -> right -> integer;
  if (a > countCL){
    printf("ERROR - Argument does not exist.\n");
    exit(0);  
  }
  LEXEME *ret = newLEXEME(STRING);
  ret -> string = argsCL[a];
  return ret;
}

LEXEME *openFile(LEXEME *tree, LEXEME *env){
  (void)(env);
  char *f = tree -> left -> string;
  LEXEME *fp = newLEXEME("FILE_POINTER");
  fp -> fp = fopen(f, "r");
  return fp;
}

LEXEME *readInt(LEXEME *tree, LEXEME *env){
  (void)(env);
  FILE *fp = car(tree) -> fp;
  int x = 0;
  fscanf(fp, "%d", &x);
  return newINTLEXEME(x);
}

LEXEME *notFileEnd(LEXEME *tree, LEXEME *env){
  (void)(env);
  FILE *fp = car(tree) -> fp;
  if (!feof(fp)){
    return newBOOLLEXEME(1);
  }
  else{
    return newBOOLLEXEME(0);
  }
}

LEXEME *closeFile(LEXEME *tree, LEXEME *env){
  (void)(env);
  FILE *fp = car(tree) -> fp;
  fclose(fp);
  return newBOOLLEXEME(1);
}

LEXEME *evalProgram(LEXEME *tree, LEXEME *env){
  while (tree != NULL){
    eval(car(tree), env);
    tree = cdr(tree);
  }
  return NULL;
}

LEXEME *evalSET(LEXEME *tree, LEXEME *env){
  //printf("EVAL ASSIGN\n");
  //printf("HERE\n");
  LEXEME *val = eval(cdr(tree), env);
  if (typeLEXEME(car(tree)) == DOT){
    LEXEME *obj = eval(car(car(tree)), env);
    updateVal(cdr(car(tree)), val, obj);
  }
  else if (typeLEXEME(car(tree)) == ID){
    updateVal(car(tree), val, env);
  }
  return val;
}

LEXEME *evalDot(LEXEME *tree, LEXEME *env){
  LEXEME *obj = eval(tree -> left, env);
  return eval(tree -> right, obj);
}

LEXEME *evalFuncDef(LEXEME *tree, LEXEME *env){
  //printf("EVAL FUNCDEF\n");
  LEXEME *closure = cons(CLOSURE, env, tree);
  LEXEME *val = insert(env, tree -> left, closure);
  return val;
}

LEXEME *evalStructDef(LEXEME *tree, LEXEME *env){
  return insert(env, tree -> left, cons(OCLOSURE, env, tree));
}

LEXEME *evalConstructor(LEXEME *closure, LEXEME *env){
  (void)(env);
  LEXEME *senv = car(closure);
  LEXEME *xenv = extendENV(senv, NULL, NULL);
  LEXEME *body = cdr(cdr(closure));
  eval(body, xenv);
  return xenv;
}

LEXEME *evalLambda(LEXEME *tree, LEXEME *env){
  LEXEME *n = cons(FUNC, NULL, tree);
  return cons(CLOSURE, env, n);
}

LEXEME *evalVarDef(LEXEME *tree, LEXEME *env){
  LEXEME *val = eval(tree -> right, env);
  LEXEME *var = insert(env, tree -> left, val);
  return var;
}

LEXEME *evalID(LEXEME *tree, LEXEME *env){
  //printf("EVAL ID\n");
  return getVal(env, tree);
}

LEXEME *evalIDDEF(LEXEME *tree, LEXEME *env){
  LEXEME *temp = cons(SET, tree -> left, tree -> right);
  return eval(temp, env);
}

LEXEME *evalCall(LEXEME *tree, LEXEME *env){
  //printf("EVAL CALL\n");
  LEXEME *closure = eval(tree -> left, env);

  if (typeLEXEME(closure) == OCLOSURE){
    return evalConstructor(closure, env);
  }

  LEXEME *args = evalArgs(cdr(tree), env);

  if (typeLEXEME(closure) == BUILTIN){
    return closure -> fval(args, env);
  }
  
  LEXEME *senv = car(closure);
  LEXEME *params = getParams(closure);
  LEXEME *lenv = extendENV(senv, params, args);
  LEXEME *body = getBody(closure);

  LEXEME *val = eval(body, lenv);

  if (typeLEXEME(val) == RETURNED){
    return car(val);
  }
  
  return val;
}

LEXEME *evalLambdaCall(LEXEME *tree, LEXEME *env){
  LEXEME *closure = evalLambda(tree -> right, env);
  LEXEME *args = evalArgs(tree -> left, env);

  LEXEME *senv = car(closure);
  LEXEME *params = tree -> right -> left;
  LEXEME *lenv = extendENV(senv, params, args);
  LEXEME *body = tree -> right -> right;

  LEXEME *val = eval(body, lenv);

  if (typeLEXEME(val) == RETURNED){
    return car(val);
  }
  
  return val;  
}

LEXEME *evalArgs(LEXEME *args, LEXEME *env){
  //printf("EVAL ARGS\n");
  if (args == NULL){return NULL;}
  else if (args -> type == EXPLIST){
    return cons("GLUE", evalArgs(car(args), env), evalArgs(cdr(args), env));
  }
  return eval(args, env);
}

LEXEME *evalBlock(LEXEME *tree, LEXEME *env){
  //printf("EVAL BLOCK\n");
  LEXEME *result = NULL;
  while (tree != NULL){
    result = eval(car(tree), env);
    
    if (typeLEXEME(result) == RETURNED){
      return result;
    }

    tree = cdr(tree);
  }
  return result;
}

LEXEME *evalStatementList(LEXEME *tree, LEXEME *env){
  //printf("EVAL STATEMENT LIST\n");
  LEXEME *val = NULL;
  while (tree != NULL){
    val = eval(tree -> left, env);

    if (typeLEXEME(val) == RETURNED){
      return val;
    }

    tree = cdr(tree);
  }
  return val;
}

LEXEME *evalStatement(LEXEME *tree, LEXEME *env){
  //printf("EVAL STATEMENT\n");
  return eval(tree, env);
}

LEXEME *evalNegative(LEXEME *tree, LEXEME *env){
  //printf("EVAL NEG\n");
  LEXEME *result = eval(tree -> right, env);
  if (typeLEXEME(result) == INTEGER){
    result -> integer *= -1;
  }
  if (typeLEXEME(result) == DOUBLE){
    result -> real *= -1.0;
  }
  return result;
}

LEXEME *evalReturn(LEXEME *tree, LEXEME *env){
  return cons(RETURNED, eval(tree -> right, env), NULL);
  //return eval(tree -> right, env);
}

LEXEME *evalIf(LEXEME *tree, LEXEME *env){
  LEXEME *b = eval(tree -> left, env);
  if (b -> b == 1){
    return eval(tree -> right -> left, env);
  }
  else if (tree -> right -> right){
    return evalELSE(tree -> right -> right, env);
  }
  return NULL;
}

LEXEME *evalELSE(LEXEME *tree, LEXEME *env){
  if (typeLEXEME(car(tree)) == IF){
    return evalIf(car(tree), env);
  }
  return eval(car(tree), env);
}

LEXEME *evalWhile(LEXEME *tree, LEXEME *env){
  LEXEME *result = eval(tree -> left, env);
  LEXEME *b = eval(tree -> left, env);
  while (b -> b == 1){
    result = eval(tree -> right, env);
    b = eval(tree -> left, env);
  }
  return result;
}

LEXEME *evalUnaryOp(LEXEME *tree, LEXEME *env){
  LEXEME *a = eval(tree -> right, env);
  if (typeLEXEME(tree) == PLUSPLUS){
    a -> integer += 1;
  }
  if (typeLEXEME(tree) == MINUSMINUS){
    a -> integer -= 1;
  }
  return a;
}

LEXEME *evalArray(LEXEME *tree, LEXEME *env){
  LEXEME *a = newLEXEME(ARRAY);
  a -> right = env;
  int count = 0;
  LEXEME *check = tree;
  while (check != NULL){
    count++;
    check = check -> right;
  }
  a -> aval = malloc(sizeof(LEXEME *) * (count + 1));
  a -> avalSize = count;
  count = 0;
  while (tree != NULL){
    a -> aval[count] = tree -> left;
    count++;
    tree = tree -> right;
  }
  return a;
}

LEXEME *evalArrayOfSize(LEXEME *tree, LEXEME *env){
  LEXEME *a = newLEXEME(ARRAY);
  a -> right = env;
  a -> aval = malloc(sizeof(LEXEME *) * tree -> left -> integer + 1);
  a -> avalSize = tree -> left -> integer;
  return a;
}

LEXEME *evalSizeArray(LEXEME *tree, LEXEME *env){
  LEXEME *a = eval(tree -> left, env);
  return newINTLEXEME(a -> avalSize);
}

LEXEME *evalGetArray(LEXEME *tree, LEXEME *env){
  int index = tree -> right -> left -> integer;
  LEXEME *a = eval(tree -> left, env);
  if (index >= a -> avalSize) {
    printf("ERROR: cannot access index %d\n", index);
    exit(-1);
  }
  return a -> aval[index];
}

LEXEME *evalSetArray(LEXEME *tree, LEXEME *env){
  int index = tree -> right -> left -> integer;
  LEXEME *a = eval(tree -> left, env);
  if (index >= a -> avalSize) {
    printf("ERROR: cannot access index %d\n", index);
    exit(-1);
  }
  LEXEME *item = tree -> right -> right -> left;
  a -> aval[index] = item;
  return tree;
}

// GET FUNCTIONS

LEXEME *getParams(LEXEME *l){
  return l -> right -> right -> left;
}

LEXEME *getArgs(LEXEME *l){
  return l -> right -> right -> left;
}

LEXEME *getBody(LEXEME *l){
  return l -> right -> right -> right;
}

// CHECKING FUNCTIONS

int isBuiltIn(LEXEME *l){
  char *t = typeLEXEME(l);
  return t == PRINT || t == GETINT || t == CLA;
}

// SIMPLE OPERATIONS

LEXEME *evalSimpleOp(LEXEME *tree, LEXEME *env){
  char *t = typeLEXEME(tree);
  if (t == PLUS){
    return evalPlus(tree, env);
  }
  if (t == MINUS){
    return evalMinus(tree, env);
  }
  if (t == TIMES){
    return evalTimes(tree, env);
  }
  if (t == DIVIDE){
    return evalDivide(tree, env);
  }
  if (t == GTHE){
    return evalGTHE(tree, env);
  }
  if (t == LTHE){
    return evalLTHE(tree, env);
  }
  if (t == GTH){
    return evalGTH(tree, env);
  }
  if (t == LTH){
    return evalLTH(tree, env);
  }
  if (t == EQUALS){
    return evalEQUALS(tree, env);
  }
  if (t == NOTEQUAL){
    return evalNOTEQUAL(tree, env);
  }
  if (t == AND){
    return evalAND(tree, env);
  }
  if (t == OR){
    return evalOR(tree, env);
  }
  return NULL;
}

LEXEME *evalPlus(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    return newINTLEXEME(left -> integer + right -> integer);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    return newREALLEXEME(left -> real + right -> integer);
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> integer + right -> real);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> real + right -> real);
  }
  return NULL;
}

LEXEME *evalMinus(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    return newINTLEXEME(left -> integer - right -> integer);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    return newREALLEXEME(left -> real - right -> integer);
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> integer - right -> real);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> real - right -> real);
  }
  return NULL;
}

LEXEME *evalTimes(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    return newINTLEXEME(left -> integer * right -> integer);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    return newREALLEXEME(left -> real * right -> integer);
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> integer * right -> real);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> real * right -> real);
  }
  return NULL;
}

LEXEME *evalDivide(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    return newINTLEXEME(left -> integer / right -> integer);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    return newREALLEXEME(left -> real / right -> integer);
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> integer / right -> real);
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    return newREALLEXEME(left -> real / right -> real);
  }
  return NULL;
}

LEXEME *evalGTHE(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer >= right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    if (left -> real >= right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    if (left -> integer >= right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real >= right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  return NULL;
}

LEXEME *evalLTHE(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer <= right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    if (left -> real <= right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    if (left -> integer <= right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real <= right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  return newBOOLLEXEME(0);
}

LEXEME *evalGTH(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer > right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    if (left -> real > right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    if (left -> integer > right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real > right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }

  return NULL;
}

LEXEME *evalLTH(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer < right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == INTEGER){
    if (left -> real < right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == DOUBLE){
    if (left -> integer < right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real < right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  return NULL;
}

LEXEME *evalEQUALS(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer == right -> integer){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real == right -> real){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  else if (typeLEXEME(left) == STRING && typeLEXEME(right) == STRING){
    if (!strcmp(left -> string, right -> string)){
      return newBOOLLEXEME(1);
    }
    else {return newBOOLLEXEME(0);}
  }
  return newBOOLLEXEME(0);
}

LEXEME *evalNOTEQUAL(LEXEME *tree, LEXEME *env){
  LEXEME *left = eval(car(tree), env);
  LEXEME *right = eval(cdr(tree), env);
  if (typeLEXEME(left) == INTEGER && typeLEXEME(right) == INTEGER){
    if (left -> integer == right -> integer){
      return newBOOLLEXEME(0);
    }
    else {return newBOOLLEXEME(1);}
  }
  else if (typeLEXEME(left) == DOUBLE && typeLEXEME(right) == DOUBLE){
    if (left -> real == right -> real){
      return newBOOLLEXEME(0);
    }
    else {return newBOOLLEXEME(1);}
  }
  else if (typeLEXEME(left) == STRING && typeLEXEME(right) == STRING){
    if (!strcmp(left -> string, right -> string)){
      return newBOOLLEXEME(0);
    }
    else {return newBOOLLEXEME(1);}
  }
  return newBOOLLEXEME(1);
}

LEXEME *evalAND(LEXEME *tree, LEXEME *env){
  LEXEME *c = eval(tree -> left, env);
  if (c -> b == 0){return newBOOLLEXEME(0);}
  c = eval(tree -> right, env);
  if (c -> b == 0){return newBOOLLEXEME(0);}
  return newBOOLLEXEME(1);
}

LEXEME *evalOR(LEXEME *tree, LEXEME *env){
  LEXEME *c = eval(tree -> left, env);
  if (c -> b == 1){return newBOOLLEXEME(1);}
  c = eval(tree -> right, env);
  if (c -> b == 1){return newBOOLLEXEME(1);}
  return newBOOLLEXEME(0);
}

// PRINT FUNCTIONS
void evalPrintHelper(LEXEME *tree, LEXEME *env){
  char *t = typeLEXEME(tree);
  if (t == PRINTSTATEMENT){
    evalPrintHelper(tree -> left, env);
  }
  else if (t == EXPLIST){
    evalPrintHelper(tree -> left, env);
    evalPrintHelper(tree -> right, env);
  }
  else {
    LEXEME *e = eval(tree, env);
    t = typeLEXEME(e);
    if (t == INTEGER){printf("%d", e -> integer);}
    if (t == STRING){
      if (!strcmp(e -> string, "/n")){printf("\n");}
      else {printf("%s", e -> string);}
    }
    if (t == DOUBLE){printf("%g", e -> real);}
    if (t == ARRAY){printArrays(e, env);}
    if (t == CLOSURE){
      LEXEME *f = e;
      printf("FUNC");
      f = f -> right -> right -> left;
      printf("<");
      while (f != NULL){
        printf("%s", f -> left -> string);
        if (f -> right != NULL){printf(",");}
        f = f -> right;
      }
      printf(">");
    }
  }
}

LEXEME *evalPrint(LEXEME *tree, LEXEME *env){
  evalPrintHelper(tree, env);
  return tree;
}

void printArrays(LEXEME *tree, LEXEME *env) {
    LEXEME **array = tree->aval;
    int count = 0;
    printf("(");
    while(count < tree -> avalSize) {
        if(count > 0) printf(", ");
        if(array[count] == NULL) {
            printf("nil");
        } else {
            LEXEME *i = array[count];
            evalPrint(i, env);
        }
        count++;
    }
    printf(")");
}