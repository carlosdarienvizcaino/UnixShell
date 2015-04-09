all: structures.o commands.o y.tab.o lex.yy.o main.o 
	gcc -o main structures.o commands.o lex.yy.o y.tab.o main.o 

y.tab.h: Parser.y
	yacc -dv Parser.y

y.tab.c: Parser.y
	yacc -dv Parser.y

y.tab.o: y.tab.h y.tab.c
	cc -c y.tab.c 

lex.yy.c: Scanner.l
	lex Scanner.l

lex.yy.o: lex.yy.c
	cc -c lex.yy.c -g

structures.o: structures.c
	cc -c structures.c -g

commands.o: commands.c
	cc -c commands.c -g


main.o: main.c
	cc -c main.c -g

clean:
	rm -f *.o main structures lex.yy.* y.tab.* y.* 