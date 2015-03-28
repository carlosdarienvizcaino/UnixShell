# simple script that creates an executable. Acts in a similar fashion to a makefile.
# ENTER ---  chmod u+rw script.sh --- in the terminal to give permission to the script.

lex shell.l
yacc -d shell.y
cc lex.yy.c y.tab.c -o shell
