#ifndef EVAL
#define EVAL

#include "lexeme.h"
#include "lexer.h"
#include "types.h"
#include "parser.h"
#include "env.h"

int countCL;
char **argsCL;

LEXEME *addBuiltIn(LEXEME *, char *, LEXEME *(*f)(LEXEME *, LEXEME *));
LEXEME *addBuiltIns(LEXEME *);


LEXEME *eval(LEXEME *, LEXEME *);

LEXEME *evalSimpleOp(LEXEME *, LEXEME *);
LEXEME *evalPlus(LEXEME *, LEXEME *);
LEXEME *evalMinus(LEXEME *, LEXEME *);
LEXEME *evalTimes(LEXEME *, LEXEME *);
LEXEME *evalDivide(LEXEME *, LEXEME *);
LEXEME *evalGTHE(LEXEME *, LEXEME *);
LEXEME *evalLTHE(LEXEME *, LEXEME *);
LEXEME *evalGTH(LEXEME *, LEXEME *);
LEXEME *evalLTH(LEXEME *, LEXEME *);
LEXEME *evalEQUALS(LEXEME *, LEXEME *);
LEXEME *evalNOTEQUAL(LEXEME *, LEXEME *);
LEXEME *evalAND(LEXEME *, LEXEME *);
LEXEME *evalOR(LEXEME *, LEXEME *);
LEXEME *evalSET(LEXEME *, LEXEME *);
LEXEME *evalUnaryOp(LEXEME *, LEXEME *);
LEXEME *evalDot(LEXEME *, LEXEME *);
LEXEME *evalUMINUS(LEXEME *t, LEXEME *);

LEXEME *evalArray(LEXEME *, LEXEME *);
LEXEME *evalSetArray(LEXEME *, LEXEME *);
LEXEME *evalGetArray(LEXEME *, LEXEME *);
LEXEME *evalArrayOfSize(LEXEME *, LEXEME *);
LEXEME *evalSizeArray(LEXEME *, LEXEME *);

LEXEME *openFile(LEXEME *, LEXEME *);
LEXEME *readInt(LEXEME *, LEXEME *);
LEXEME *notFileEnd(LEXEME *, LEXEME *);
LEXEME *closeFile(LEXEME *, LEXEME *);

LEXEME *evalCall(LEXEME *, LEXEME *);
LEXEME *evalArgs(LEXEME *, LEXEME *);
LEXEME *evalFuncDef(LEXEME *, LEXEME *);
LEXEME *evalStructDef(LEXEME *, LEXEME *);
LEXEME *evalConstructor(LEXEME *, LEXEME *);
LEXEME *evalLambda(LEXEME *, LEXEME *);
LEXEME *evalLambdaCall(LEXEME *, LEXEME *);
LEXEME *evalVarDef(LEXEME *, LEXEME *);
LEXEME *evalProgram(LEXEME *, LEXEME *);
LEXEME *evalID(LEXEME *, LEXEME *);
LEXEME *evalIDDEF(LEXEME *, LEXEME *);
LEXEME *evalBlock(LEXEME *, LEXEME *);
LEXEME *evalReturn(LEXEME *, LEXEME *);
LEXEME *evalStatementList(LEXEME *, LEXEME *);

LEXEME *evalIf(LEXEME *, LEXEME *);
LEXEME *evalELSIF(LEXEME *, LEXEME *);
LEXEME *evalELSE(LEXEME *, LEXEME *);
LEXEME *evalWhile(LEXEME *, LEXEME *);

LEXEME *getParams(LEXEME *);
LEXEME *getArgs(LEXEME *);
LEXEME *getBody(LEXEME *);

int isBuiltIn(LEXEME *);

LEXEME *evalPrint(LEXEME *, LEXEME *);
LEXEME *evalPrintLN(LEXEME *, LEXEME *);
void printArrays(LEXEME *, LEXEME *);
LEXEME *evalCLA(LEXEME *, LEXEME *);
LEXEME *evalGetInt(LEXEME *, LEXEME *);

#endif