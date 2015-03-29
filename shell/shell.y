%{
#include "header.h"
#include "node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
extern char** environ;
alias_node *aliasNode;      //head of the alias list

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

void getDirectory(){  //test function to get current directory
	size_t size= sizeof(char) * 1024;
	char * buf= (char *)malloc(size);
	char * cwd;
	if((cwd = getcwd(buf,size))!=NULL){
    	printf("Dir: %s\n",cwd);
	}
}

main()
{
 	aliasNode=NULL;
        yyparse();
} 
%}

%token BYE SETENV UNSETENV PRINTENV CD TEST ALIAS UNALIAS
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
       test
       ;
bye:
       BYE
       {
	exit(0);
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
        
      }
      ;
cd_no_args:
     CD
     {
	printf("CD RAN\n");
	chdir("HOME");
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
      	alias_printList(&aliasNode);
      }
      ;
test:
    TEST WORD
     {
      printf("THIS RUNS");
     }
%%








