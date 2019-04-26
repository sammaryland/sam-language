#include "lexer.h"
#include "env.h"
#include "types.h"
#include "eval.h"

LEXEME *mainCall(){
  LEXEME *tree = newLEXEME(CALL);
  LEXEME *v = newLEXEME(ID);
  v -> string = "main";
  tree->left = v;
  return tree;
}

int main(int argc, char **argv){
  if (argc > 3){
    printf("INCORRECT NUMBER OF ARGUMENTS\n");
    exit(1);
  }

  FILE *fp = fopen(argv[1], "r");

  countCL = argc;
  argsCL = argv;

  LEXEME *env = newENV();

  LEXEME *tree = parse(fp);
  env = addBuiltIns(env);
  eval(tree, env);
  tree = mainCall();
  eval(tree, env);
  
  fclose(fp);

  return 0;
}