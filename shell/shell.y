%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
extern char** environ;
//will probably need more stuff here


/* YACC */
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 
  
main()
{
        yyparse();
} 
%}

%token BYE SETENV UNSETENV PRINTENV CD
%union   //links lex and yacc
{
char *str;
}
%token <str> WORD;  
%%

commands: /* empty */
        | commands command
        ;

command:
       bye
       |
       setenv
       |
       unsetenv
       |
       printenv
       |
       cd
       |
       cd_args
       ;
bye:
       BYE
       {
	//call function and close the stream
       }
       ;

setenv:
      SETENV  //+ some words. Need to figure out.
      {
      	   //functionality
      }
      ;

unsetenv:
      UNSETENV //+ a word or two(I believe)
      {
	//functionality
      }
      ;

printenv:
      PRINTENV
      {
	int i=0;
	while(environ[i])
           printf("%s\n",environ[i++]);
      }
      ;
cd:
      CD
      {
	chdir("HOME");
      }
      ;
cd_args:
     CD WORD
     {
	printf("THIS RAN");
     }
     ;
%%








