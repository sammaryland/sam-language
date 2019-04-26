#ifndef PARSER_REC
#define PARSER_REC

#include "lexeme.h"
#include "lexer.h"
#include "types.h"

typedef struct parser PARSER;

struct parser {
  FILE *fp;
  LEXEME *prev;
  LEXEME *next;
  FILE *out;
  int line;
};

LEXEME *parse(FILE *);
void displayTree(LEXEME *, char *);
int typeEqual(LEXEME *, LEXEME *);

// Pending Declarations
int commentPending(PARSER *);
int operatorPending(PARSER *);
int structDefPending(PARSER *);
int varDefPending(PARSER *);
int funcDefPending(PARSER *);
int paramListPending(PARSER *);
int expListPending(PARSER *);
int expressionPending(PARSER *);
int statementListPending(PARSER *);
int statementPending(PARSER *);
int ifStatementPending(PARSER *);
int whileLoopPending(PARSER *);
int forLoopPending(PARSER *);
int unaryPending(PARSER *);
int literalPending(PARSER *);
int comparatorPending(PARSER *);
int unaryOperatorPending(PARSER *);
int elseStatementPending(PARSER *);
int blockPending(PARSER *);
int programPending(PARSER *);
int definitionPending(PARSER *);
int returnPending(PARSER *);
int arrayPending(PARSER *);
int printPending(PARSER *);
int lambdaPending(PARSER *);
int claPending(PARSER *);
int getintPending(PARSER *);

// Parser Declarations
LEXEME *program(PARSER *);
LEXEME *definition(PARSER *);
LEXEME *literal(PARSER *);
LEXEME *operators(PARSER *);
LEXEME *unaryOperator(PARSER *);
LEXEME *comparator(PARSER *);
LEXEME *expression(PARSER *);
LEXEME *varDef(PARSER *);
LEXEME *unary(PARSER *);
LEXEME *expList(PARSER *);
LEXEME *optExpList(PARSER *);
LEXEME *ifStatement(PARSER *);
LEXEME *optElse(PARSER *);
LEXEME *elsif(PARSER *);
LEXEME *whileLoop(PARSER *);
LEXEME *forLoop(PARSER *);
LEXEME *block(PARSER *);
LEXEME *conditional(PARSER *);
LEXEME *conditionalList(PARSER *);
LEXEME *optStatementList(PARSER *);
LEXEME *statementList(PARSER *);
LEXEME *statement(PARSER *);
LEXEME *funcDef(PARSER *);
LEXEME *funcCall(PARSER *);
LEXEME *optParamList(PARSER *);
LEXEME *paramList(PARSER *);
LEXEME *arrayDef(PARSER *);
LEXEME *arraySet(PARSER *);
LEXEME *pointerVar(PARSER *);
LEXEME *structAccess(PARSER *);
LEXEME *structDef(PARSER *);
LEXEME *comment(PARSER *);
LEXEME *returnStatement(PARSER *);
LEXEME *printStatement(PARSER *);
LEXEME *lambda(PARSER *);
LEXEME *cla(PARSER *);
LEXEME *getint(PARSER *);

// Other Functions
void advance(PARSER *);
LEXEME *match(PARSER *, char *);
void matchNoAdvance(PARSER *, char *);
int check(PARSER *, char *);
char *typeLEXEME(LEXEME *);

#endif