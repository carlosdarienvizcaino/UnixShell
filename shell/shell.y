%
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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

%token BYE SETENV UNSETENV PRINTENV CD
%%

commands: /* empty */
        | commands command
        ;

command:
       BYE
       |
       SETENV
       |
       UNSETENV
       |
       PRINTENV
       |
       CD
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
	//functionality
      }
      ;
cd:
      CD
      {
	//functionality
      }
      ;
%%








