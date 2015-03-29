%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"
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
        yyparse();
} 
%}

%token BYE SETENV UNSETENV PRINTENV CD TEST
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
       test
       ;
bye:
       BYE
       {
	//call function and close the stream
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
test:
    TEST WORD
     {
      printf("THIS RUNS");
     }
%%








