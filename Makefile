#GCC = @g++
GCC = @g++ -g -std=gnu++11 -Wall
LEX = @flex

demo: demo.cpp yacc.o
			$(GCC) demo.cpp yacc.o -o demo

yacc.o: yacc.c
			$(GCC) -c yacc.c

yacc.c: demo.lex
			$(LEX) -o yacc.c demo.lex

clean:
			@-rm -f *.o *~ yacc.c  demo
.PHONY: clean
