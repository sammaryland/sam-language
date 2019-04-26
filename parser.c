#include "parser.h"

LEXEME *parse(FILE *fp){
  PARSER *items = malloc(sizeof(PARSER));
  items -> fp = fp;
  items -> next = lex(items -> fp);
  items -> line = 1;
  items -> out = stdout;
  LEXEME *tree = NULL;
  while(strcmp(typeLEXEME(items -> next), "END_OF_FILE")){
    if (!strcmp(typeLEXEME(items -> next), BAD_LEX)){
      matchNoAdvance(items, BAD_LEX);
    }
    tree = program(items);
  }
  return tree;
}

void advance(PARSER *p){
  p -> prev = p -> next;
  p -> next = lex(p -> fp);
}

LEXEME *match(PARSER *p, char *ch){
  LEXEME *i = p -> next;
  matchNoAdvance(p, ch);
  advance(p);
  return i;
}

void matchNoAdvance(PARSER *p, char *ch){
  if (!check(p, ch) || check(p, BAD_LEX)){
    printf("illegal %s on line %d\n", ch, getLineNo());
    exit(1);
  }
}

int check(PARSER *p, char *ch){
  return typeLEXEME(p -> next) == ch;
}

char *typeLEXEME(LEXEME *i){
  if (i == NULL){return NULL;}
  else {return i -> type;}
}

// PENDING FUNCTIONS

int commentPending(PARSER *p){
  //printf("CHECKED COMMENT");
  //printf("%s\n", typeLEXEME(p -> next));
  return check(p, COMMENT);
}

int operatorPending(PARSER *p){
  return comparatorPending(p) || check(p, EQUALS) || check(p, PLUS) || 
    check(p, TIMES) || check(p, MINUS) || 
    check(p, DIVIDE) || check(p, MOD) || 
    check(p, SET) || check(p, AND) || 
    check(p, OR) || check(p, NOTEQUAL);
}

int structDefPending(PARSER *p){
  return check(p, STRUCT);
}

int varDefPending(PARSER *p){
  return check(p, VAR);
}

int funcDefPending(PARSER *p){
  return check(p, FUNC);
}

int paramListPending(PARSER *p){
  return check(p, VAR);
}

int expListPending(PARSER *p){
  return expressionPending(p);
}

int expressionPending(PARSER *p){
  return returnPending(p) || unaryPending(p)  || unaryOperatorPending(p);
}

int statementListPending(PARSER *p){
  return statementPending(p);
}

int statementPending(PARSER *p){
  return definitionPending(p) || expressionPending(p) || ifStatementPending(p) ||
    whileLoopPending(p) || arrayPending(p) || commentPending(p) || printPending(p);
}

int lambdaPending(PARSER *p){
  return check(p, LAMBDA);
}

int ifStatementPending(PARSER *p){
  return check(p, IF);
}

int whileLoopPending(PARSER *p){
  return check(p, WHILE);
}

int arrayPending(PARSER *p){
  return check(p, ARR);
}

int printPending(PARSER *p){
  return check(p, PRINT);
}

int unaryPending(PARSER *p){
  //printf ("MADE IT TO UNARY PENDING %s\n", typeLEXEME(p -> next));
  return literalPending(p) || claPending(p) || getintPending(p) || lambdaPending(p) || check(p, ID) 
    || check(p, LPAREN) || check(p, MINUS) || check(p, LPAREN);
}

int literalPending(PARSER *p){
  return check(p, INTEGER) || check(p, DOUBLE) 
    || check(p, STRING) || check(p, BOOLEAN)
    || check(p, CHAR);
}

int comparatorPending(PARSER *p){
  return check(p, GTH) || check(p, LTH) || 
    check(p, GTHE) || check(p, LTHE);
}

int unaryOperatorPending(PARSER *p){
  return check(p, PLUSPLUS) || check(p, MINUSMINUS);
}

int elseStatementPending(PARSER *p){
  return check(p, ELSE);
}

int blockPending(PARSER *p){
  return check(p, LBRACE);
}

int programPending(PARSER *p){
  return definitionPending(p);
}

int definitionPending(PARSER *p){
  return structDefPending(p) || varDefPending(p) || funcDefPending(p);
}

int returnPending(PARSER *p){
  return check(p, RETURN);
}

int claPending(PARSER *p){
  return check(p, CLA);
}

int getintPending(PARSER *p){
  return check(p, GETINT);
}

// PARSE FUNCTIONS

LEXEME *program(PARSER *p){
  //printf ("MADE IT TO PROGRAM\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  a = definition(p);
  if (programPending(p)){
    b = program(p);
  }
  return cons(PROGRAM, a, b);
}

LEXEME *definition(PARSER *p){
  //printf ("MADE IT TO DEFINITION\n");
  if (structDefPending(p)){
    return structDef(p);
  }
  else if (varDefPending(p)){
    return varDef(p);
  }
  else if(funcDefPending(p)){
    return funcDef(p);
  }
  else if (commentPending(p)){
    return comment(p);
  }
  return NULL;
}

LEXEME *literal(PARSER *p){
  //printf ("MADE IT TO LITERAL\n");
  if (check(p, INTEGER)){
    return match(p, INTEGER);
  }
  else if (check(p, DOUBLE)){
    return match(p, DOUBLE);
  }
  else if (check(p, STRING)){
    return match(p, STRING);
  }
  else if (check(p, BOOLEAN)){
    return match(p, BOOLEAN);
  }
  else if (check(p, CHAR)){
    return match(p, CHAR);
  }
  return NULL;
}

LEXEME *operators(PARSER *p){
  //printf ("MADE IT TO OPERATORS\n");
  if (check(p, EQUALS)){
    return match(p, EQUALS);
  }
  else if (comparatorPending(p)){
    return comparator(p);
  }
  else if (check(p, PLUS)){
    return match(p, PLUS);
  }
  else if (check(p, TIMES)){
    return match(p, TIMES);
  }
  else if (check(p, MINUS)){
    return match(p, MINUS);
  }
  else if (check(p, DIVIDE)){
    return match(p, DIVIDE);
  }
  else if (check(p, MOD)){
    return match(p, MOD);
  }
  else if (check(p, SET)){
    return match(p, SET);
  }
  else if (check(p, AND)){
    return match(p, AND);
  }
  else if (check(p, OR)){
    return match(p, OR);
  }
  else if (check(p, NOTEQUAL)){
    return match(p, NOTEQUAL);
  }
  return NULL;
}

LEXEME *unaryOperator(PARSER *p){
  //printf ("MADE IT TO UNARYOPERATOR\n");
  if (check(p, PLUSPLUS)){
    return match(p, PLUSPLUS);
  }
  else if (check(p, MINUSMINUS)){
    return match(p, MINUSMINUS);
  }
  return NULL;
}

LEXEME *comparator(PARSER *p){
  //printf ("MADE IT TO COMPARATOR\n");
  if (check(p, GTH)){
    return match(p, GTH);
  }
  else if (check(p, LTH)){
    return match(p, LTH);
  }
  else if (check(p, GTHE)){
    return match(p, GTHE);
  }
  else if (check(p, LTHE)){
    return match(p, LTHE);
  }
  return NULL;
}

LEXEME *expression(PARSER *p){
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  LEXEME *c = NULL;
  //printf ("MADE IT TO EXPRESSION\n");
  if (returnPending(p)){
    //printf("made it to return\n");
    a = returnStatement(p);
    b = expression(p);
    a -> right = b;
  }
  else if (unaryPending(p)){
    a = unary(p);
    if (operatorPending(p)){
      b = operators(p);
      if (check(p, LBRACKET)){
        printf("ARRDEF\n");
        match(p, LBRACKET);
        c = optExpList(p);
        match(p, RBRACKET);
        return cons(ARRDEF, a, cons(ARRDEF, b, c));
      }
      else{
        c = expression(p);
        b -> left = a;
        b -> right = c;
        return b;
      }
    }
  }
  else if (unaryOperatorPending(p)){
    //printf("unary op pending\n");
    a = unaryOperator(p);
    b = unary(p);
    a -> right = b;
  }
  return a;
}

LEXEME *varDef(PARSER *p){
  //printf ("MADE IT TO VARDEF\n");
  LEXEME *a = match(p, VAR);
  a -> left = match(p, ID);
  if (check(p, SET)){
    match(p, SET);
    a -> right = expression(p);
  }
  match(p, SEMICOLON);
  return a;
}

LEXEME *unary(PARSER *p){
  //printf ("MADE IT TO UNARY\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  if (check(p, INTEGER)){
    return match(p, INTEGER);
  }
  else if (check(p, DOUBLE)){
    return match(p, DOUBLE);
  }
  else if (check(p, STRING)){
    return match(p, STRING);
  }
  else if (check(p, BOOLEAN)){
    return match(p, BOOLEAN);
  }
  else if (check(p, CHAR)){
    return match(p, CHAR);
  }
  else if (check(p, MINUS)){
    match(p, MINUS);
    a = unary(p);
    return cons(UMINUS, NULL, a);
  }
  else if (check(p, LAMBDA)){
    return lambda(p);
  }
  else if (check(p, CLA)){
    return cla(p);
  }
  else if (check(p, GETINT)){
    return getint(p);
  }
  else if (check(p, ID)){
    a = match(p, ID);
    if (check(p, DOT)){
      match(p, DOT);
      LEXEME *b = unary(p);
      return cons(DOT, a, b);
    }
    if (check(p, LPAREN)){
      match(p, LPAREN);
      b = optExpList(p);
      match(p, RPAREN);
      return cons(CALL, a, b);
    }
    if (check(p, LBRACKET)){
      match(p, LBRACKET);
      b = unary(p);
      match(p, RBRACKET);
      return cons(ARRSET, a, b);
    }
    return a;
  }
  else {
    match(p, LPAREN);
    a = expression(p);
    match(p, RPAREN);
    return cons(LPAREN, NULL, a);
  }
  return NULL;
}

LEXEME *expList(PARSER *p){
  //printf ("MADE IT TO EXPLIST\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  a = expression(p);
  if (check(p, COMMA)){
    match(p, COMMA);
    b = expList(p);
  }
  return cons(EXPLIST, a, b);
}

LEXEME *optExpList(PARSER *p){
  //printf ("MADE IT TO OPTEXPLIST\n");
  if (expListPending(p)){
    return expList(p);
  }
  else {
    return NULL;
  }
}

LEXEME *ifStatement(PARSER *p){
  //printf ("MADE IT TO IFSTATEMENT\n");
  match(p, IF);
  match(p, LPAREN);
  LEXEME *a = expression(p);
  match(p, RPAREN);
  LEXEME *b = block(p);
  LEXEME *c = optElse(p);
  return cons(IF, a, cons("GLUE", b, c));
}

LEXEME *optElse(PARSER *p){
  //printf ("MADE IT TO OPTELSE\n");
  LEXEME *tree = NULL;
  if (elseStatementPending(p)){
    tree = match(p, ELSE);
    if (ifStatementPending(p)){
      tree -> left = ifStatement(p);
    }
    else{     
      tree -> left = block(p);
    }
    return tree;
  }
  else {
    return NULL;
  }
}

LEXEME *elsif(PARSER *p){
  match(p, IF);
  match(p, LPAREN);
  LEXEME *a = expression(p);
  match(p, RPAREN);
  LEXEME *b = block(p);
  LEXEME *c = optElse(p);
  LEXEME *d = cons(ELSIF, a, b);
  LEXEME *e = cons(IFLIST, d, c);
  return e;
}

LEXEME *whileLoop(PARSER *p){
  //printf ("MADE IT TO WHILELOOP\n");
  match(p, WHILE);
  match(p, LPAREN);
  LEXEME *a = expression(p);
  match(p, RPAREN);
  LEXEME *b = block(p);
  return cons(WHILE, a, b);
}

LEXEME *block(PARSER *p){
  //printf ("MADE IT TO BLOCK\n");
  LEXEME *a = NULL;
  match(p, LBRACE);
  a = optStatementList(p);
  match(p, RBRACE);
  return cons(BLOCK, NULL, a);
}

LEXEME *conditional(PARSER *p){
  //printf ("MADE IT TO CONDITIONAL\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  LEXEME *c = NULL;
  if (unaryPending(p)){
    b = unary(p);
    a = comparator(p);
    c = unary(p);
    a -> right = c;
    a -> left = b;
    return a;
  }
  else if (check(p, NOT)){
    a = match(p, NOT);
    match(p, LPAREN);
    b = conditional(p);
    match(p, RPAREN);
    a -> right = b;
  }
  return a;
}

LEXEME *conditionalList(PARSER *p){
  //printf ("MADE IT TO CONDITIONALLIST\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  a = conditional(p);
  if (check(p, AND)){
    b = match(p, AND);
    b -> right = conditionalList(p);
    b -> left = a;
    a = b;

  }
  else if (check(p, OR)){
    b = match(p, OR);
    b -> right = conditionalList(p);
    b -> left = a;
    a = b;
  }
  return a;
}

LEXEME *optStatementList(PARSER *p){
  //printf ("MADE IT TO OPTSTATEMENT\n");
  if (statementListPending(p)){
    return statementList(p);
  }
  else {
    return NULL;
  }
}

LEXEME *statementList(PARSER *p){
  //printf ("MADE IT TO STATEMENT LIST\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  a = statement(p);
  if (statementListPending(p)){
    b = statementList(p);
  }
  return cons(STATEMENTLIST, a, b);
}

LEXEME *statement(PARSER *p){
  LEXEME *a = NULL;
  if (definitionPending(p)){
    return definition(p);
  }
  else if (expressionPending(p)){
    a = expression(p);
    match(p, SEMICOLON);
    return a;
  }
  else if (ifStatementPending(p)){
    return ifStatement(p);
  }
  else if (whileLoopPending(p)){
    return whileLoop(p);
  }
  else if (arrayPending(p)){
    return arrayDef(p);
  }
  else if (commentPending(p)){
    return comment(p);
  }
  else if (printPending(p)){
    return printStatement(p);
  }
  return a;
}

LEXEME *funcDef(PARSER *p){
  //printf ("MADE IT TO FUNCDEF\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  LEXEME *c = NULL;
  a = match(p, FUNC);
  a -> left = match(p, ID);
  match(p, LPAREN);
  if (paramListPending(p)){
    b = optParamList(p);
  }
  match(p, RPAREN);
  c = block(p);
  a -> right = cons(NULL, b, c);
  return a;
}

LEXEME *funcCall(PARSER *p){
  //printf ("MADE IT TO FUNCCALL\n");
  LEXEME *a = match(p, ID);
  LEXEME *b = NULL;
  match(p, LPAREN);
  b = optExpList(p);
  match(p, RPAREN);
  match(p, SEMICOLON);
  return cons(CALL, a, b);
}

LEXEME *optParamList(PARSER *p){
  //printf ("MADE IT TO OPTPARAMLIST\n");
  if (paramListPending(p)){
    return paramList(p);
  }
  else {
    return NULL;
  }
}

LEXEME *paramList(PARSER *p){
  //printf ("MADE IT TO PARAMLIST\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  match(p, VAR);
  a = match(p, ID);
  if (check(p, COMMA)){
    match(p, COMMA);
    b = paramList(p);
  }
  return cons(IDLIST, a, b);
}

LEXEME *arrayDef(PARSER *p){
  //printf ("MADE IT TO ARRAYDEF\n");
  LEXEME *a = match(p, ARR);
  a -> left = match(p, ID);
  match(p, LBRACKET);
  a -> right = optExpList(p);
  match(p, RBRACKET);
  match(p, SEMICOLON);
  return a;
}

LEXEME *pointerVar(PARSER *p){
  //printf ("MADE IT TO POINTERVAR\n");
  LEXEME *a = NULL;
  match(p, VAR);
  match(p, ASTERISK);
  match(p, ID);
  if (check(p, SET)){
    expression(p);
    match(p, SEMICOLON);
  }
  return a;
}

LEXEME *structAccess(PARSER *p){
  //printf ("MADE IT TO STRUCTACCESS\n");
  LEXEME *a = NULL;
  match(p, ID);
  match(p, COLON);
  match(p, ID);
  return a;
}

LEXEME *structDef(PARSER *p){
  //printf ("MADE IT TO STRUCTDEF\n");
  LEXEME *a = NULL;
  LEXEME *b = NULL;
  match(p, STRUCT);
  a = match(p, ID);
  b = block(p);
  match(p, SEMICOLON);
  return cons(STRUCTDEF, a, b);
}

LEXEME *comment(PARSER *p){
  //printf("MADE IT TO COMMENT\n");
  LEXEME *a = match(p, COMMENT);
  while (1){
    if (check(p, COMMENT)){break;}
    advance(p);
  }
  match(p, COMMENT);
  return a;
}

LEXEME *returnStatement(PARSER *p){
  //printf("MADE IT TO RETURN\n");
  return match(p, RETURN);
}

LEXEME *printStatement(PARSER *p){
  match(p, PRINT);
  LEXEME *a = NULL;
  if (check(p, LPAREN)){
    match(p, LPAREN);
    a = optExpList(p);
    match(p, RPAREN);
  }
  match(p, SEMICOLON);
  return cons(PRINTSTATEMENT, a, NULL);
}

LEXEME *lambda(PARSER *p){
  LEXEME *a = match(p, LAMBDA);
  match(p, LPAREN);
  a -> left = optParamList(p);
  match(p, RPAREN);
  a -> right = block(p);
  LEXEME *b = NULL;
  if (check(p, LPAREN)){
    match(p, LPAREN);
    b = optExpList(p);
    match(p, RPAREN);
    return cons(LAMBDACALL, b, a);
  }
  return a;
}

LEXEME *cla(PARSER *p){
  //printf("MADE IT TO CLA");
  LEXEME *a = NULL;
  match(p, CLA);
  match(p, LPAREN);
  a = expression(p);
  match(p, RPAREN);
  return cons(CLA, NULL, a);
}

LEXEME *getint(PARSER *p){
  LEXEME *a = NULL;
  match(p, GETINT);
  match(p, LPAREN);
  a = expression(p);
  match(p, RPAREN);
  return cons(GETINT, NULL, a);
}
