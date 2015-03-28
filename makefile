all: y.tab.o lex.yy.o

lex.yy.c: Example1.l
    #flex Example1.l
	@touch $@

y.tab.c y.tab.h: Example1.y
    #bison -d Example1.y
	@touch y.tab.c y.tab.h

lex.yy.o: lex.yy.c y.tab.h
    #gcc -c lex.yy.c
	@touch $@

y.tab.o: y.tab.c
    #gcc -c y.tab.c
	@touch $@

create:
	touch Example1.l Example1.y

clean:
	rm y.tab.o lex.yy.o lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o Example1.l Example1.y