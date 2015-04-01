all: lex.yy.c y.tab.c y.tab.h
		cc lex.yy.c y.tab.c main.c -o main

y.tab.h: y.tab.c

y.tab.c: Parser.y
	yacc -dv Parser.y

lex.yy.c: Scanner.l
	lex Scanner.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h main
