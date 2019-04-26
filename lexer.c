/*
  Lexer
  Written by Sam Maryland
  January 21, 2019
*/

#include "types.h"
#include "lexer.h"
#include "lexeme.h"
#include "stack.h"
#include "token.h"

// Keep track of line number for error reporting
int lineNo = 1;

LEXEME *lex(FILE *fp){
  skipWhiteSpace(fp);
  char ch = getNextCharacter(fp);

  if (ch == EOF){return newLEXEME(END_OF_FILE);}

  // Check if symbol
  switch (ch){
    case '.':
      return newLEXEME(DOT);
    case '(':
      return newLEXEME(LPAREN);
    case ')':
      return newLEXEME(RPAREN);
    case ';':
      return newLEXEME(SEMICOLON);
    case ',':
      return newLEXEME(COMMA);
    case '{':
      return newLEXEME(LBRACE);
    case '}':
      return newLEXEME(RBRACE);
    case '[':
      return newLEXEME(LBRACKET);
    case '!':
      ch = getNextCharacter(fp);
      if (ch == '='){
        return newLEXEME(NOTEQUAL);
      }
      else {
        return badLEXEME(ch);
      }
    case ']':
      return newLEXEME(RBRACKET);
    case ':':
      return newLEXEME(COLON);
    case '_':
      return newLEXEME(COMMENT);
    case '+':
      ch = getNextCharacter(fp);
      if (ch == '+'){
        return newLEXEME(PLUSPLUS);
      }
      else{
        if (!isWhiteSpace(ch)){ungetc(ch, fp);}
        return newLEXEME(PLUS);
      }
    case '-':
      ch = getNextCharacter(fp);
      if (ch == '-'){
        return newLEXEME(MINUSMINUS);
      }
      else{
        if (!isWhiteSpace(ch)){ungetc(ch, fp);}
        return newLEXEME(MINUS);
      }
    case '<':
      ch = getNextCharacter(fp);
      if (ch == '='){
        return newLEXEME(LTHE);
      }
      else{
        if (!isWhiteSpace(ch)){ungetc(ch, fp);}
        return newLEXEME(LTH);
      }
    case '>':
      ch = getNextCharacter(fp);
      if (ch == '='){
        return newLEXEME(GTHE);
      }
      else{
        if (!isWhiteSpace(ch)){ungetc(ch, fp);}
        return newLEXEME(GTH);
      }
    case '=':
      ch = getNextCharacter(fp);
      if (ch == '='){
        return newLEXEME(EQUALS);
      }
      else{
        if (!isWhiteSpace(ch)){ungetc(ch, fp);}
        return newLEXEME(SET);
      }
    case '/':
      return newLEXEME(DIVIDE);
    case '*':
      return newLEXEME(TIMES);
    case '%':
      return newLEXEME(MOD);
    case '&':
      return newLEXEME(AND);
    case '|':
      return newLEXEME(OR);

  // Check if number, variable, or string
  default:
    if (isdigit(ch)){
      return lexNUM(fp, ch);
    }
    else if (isalpha(ch)){
      return lexVAR(fp, ch);
    }
    else if (ch == '\"'){
      return lexSTRING(fp);
    }
    // If none of these, report error
    else{return badLEXEME(ch);}
  }
}

void skipWhiteSpace(FILE *fp){
  char c = getNextCharacter(fp);
  while (!feof(fp) && isWhiteSpace(c)){
    c = getNextCharacter(fp);
  }
  ungetc(c, fp);
}

char getNextCharacter(FILE *fp){
  int result;
  char ch;
  result = fgetc(fp);
  ch = result;
  if (result == EOF){return EOF;}
  if (result == 0){
    fprintf(stderr,"SCAN ERROR: attempt to read a raw character failed\n");
    fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
    exit(2);
  }
  return ch;
}

int isWhiteSpace(char ch){
  if (ch == '\n'){lineNo++;}
  return ch == ' ' || ch == '\r' || ch == '\t' || ch == '\n';
}

int getLineNo(){
  return lineNo;
}