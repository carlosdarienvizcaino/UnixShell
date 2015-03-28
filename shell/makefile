all: y.tab.o lex.yy.o

lex.yy.c: shell.l
    #flex shell.l
	@touch $@

y.tab.c y.tab.h: shell.y
    #bison -d shell.y
	@touch y.tab.c y.tab.h

lex.yy.o: lex.yy.c y.tab.h
    #gcc -c lex.yy.c
	@touch $@

y.tab.o: y.tab.c
    #gcc -c y.tab.c
	@touch $@

create:
	touch shell.l shell.y

clean:
	rm y.tab.o lex.yy.o lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o shell.l shell.y
