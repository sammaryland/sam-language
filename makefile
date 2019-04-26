OBJS = types.o stack.o lexer.o lexeme.o dll.o token.o parser.o env.o eval.o
OOPTS = -std=c99 -Wall -Wextra -g -c
LOPTS = -std=c99 -Wall -Wextra -g

all : eval

eval : $(OBJS)
	gcc $(LOPTS) $(OBJS) main.c -o dpl

recognizer : $(OBJS) recognizer.c
	gcc $(LOPTS) $(OBJS) recognizer.c -o recognizer

eval.o : eval.c eval.h
	gcc $(OOPTS) eval.c

env.o : env.c env.h
	gcc $(OOPTS) env.c

types.o : types.c types.h
	gcc $(OOPTS) types.c

stack.o	:	stack.c stack.h
	gcc $(OOPTS) stack.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

lexer.o	:	lexer.c lexer.h
	gcc $(OOPTS) lexer.c

lexeme.o : lexeme.c lexeme.h
	gcc $(OOPTS) lexeme.c

token.o : token.c token.h
	gcc $(OOPTS) token.c

parser.o : parser.c parser.h
	gcc $(OOPTS) parser.c

test : eval
	@echo "ERROR1"
	@make error1x
	@echo
	@echo "ERROR2"
	@make error2x
	@echo
	@echo "ERROR3"
	@make error3x
	@echo
	@echo "ERROR4"
	@make error4x
	@echo
	@echo "ERROR5"
	@make error5x
	@echo
	@echo "ARRAYS"
	@make arraysx
	@echo
	@echo "CONDITIONALS"
	@make conditionalsx
	@echo
	@echo "RECURSION"
	@make recursionx
	@echo
	@echo "ITERATION"
	@make iterationx
	@echo
	@echo "FUNCTIONS"
	@make functionsx
	@echo
	@echo "LAMBDA"
	@make lambdax
	@echo
	@echo "OBJECTS"
	@make objectsx
	@echo
	@echo "TEST PROBLEM"
	@make problemx
	@echo

error1 : eval
	@cat input/error1.sam

error1x : eval
	-@./dpl input/error1.sam

error2 : eval
	@cat input/error2.sam

error2x : eval
	-@./dpl input/error2.sam

error3 : eval
	@cat input/error3.sam

error3x : eval
	-@./dpl input/error3.sam

error4 : eval
	@cat input/error4.sam

error4x : eval
	-@./dpl input/error4.sam

error5 : eval
	@cat input/error5.sam

error5x : eval
	-@./dpl input/error5.sam

arrays : eval
	@cat input/arrays.sam

arraysx : eval
	@./dpl input/arrays.sam

conditionals : eval
	@cat input/conditionals.sam

conditionalsx : eval
	@./dpl input/conditionals.sam

recursion : eval
	@cat input/recursion.sam

recursionx : eval
	@./dpl input/recursion.sam

iteration : eval
	@cat input/iteration.sam

iterationx : eval
	@./dpl input/iteration.sam

functions : eval
	@cat input/functions.sam

functionsx : eval
	@./dpl input/functions.sam

lambda : eval
	@cat input/lambda.sam

lambdax : eval
	@./dpl input/lambda.sam

objects : eval
	@cat input/objects.sam

objectsx : eval
	@./dpl input/objects.sam

problem : eval
	@cat iAVL

problemx : eval
	@./dpl iAVL input/commands0

clean    :
	rm -f $(OBJS) dpl
