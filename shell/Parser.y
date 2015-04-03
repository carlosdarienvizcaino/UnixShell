%{
#include "header.h"

void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
}

%}



%token BYE SETENV UNSETENV PRINTENV CD TEST ALIAS UNALIAS LS
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
       cd_no_args
       |
       alias
       |
       unalias
       |
       alias_no_args
       |
       ls
       |
       test
       ;
bye:
       BYE
       {
	command->name="bye";
	command->args->args[0]=NULL;
	perform();
       }
       ;

setenv:
      SETENV WORD WORD
      {
      	  set($2,$3);
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
      CD WORD
      {
	command->name="cd";
	command->args->args[0]=$2;
	perform();
      }
      ;
cd_no_args:
     CD
     {
	     command->name="cd";
	     command->args->args[0]=NULL;
	     perform(); 
     }
     ;
alias:
     ALIAS WORD WORD
     {
     	push(&aliasNode,$2,$3);
     }
     ;
unalias:
     UNALIAS WORD
     {
     	removeAlias(&aliasNode,$2);
     }
     ;
alias_no_args:
      ALIAS
      {
      	alias_printList(aliasNode);
      }
      ;
ls:
      LS
       {
          printContentInCurrentDirectory();
       }
       ;
test:
    TEST WORD
     {
    	printf("Test\n");
     }
%%








