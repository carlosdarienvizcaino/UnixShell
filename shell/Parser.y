
%{
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> 
#include  <sys/types.h>
#include <sys/wait.h>

void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
}

%}


%union   
{
char *str;
struct arguments *arg;
}

%token <str> WORD
%token <arg> argv
%type<arg> arg_list



%%

commands: /* empty */
      | commands arg_list {execute();}

arg_list:
       WORD{
           commandTable->name=$1;
           commandTable->args->args[0]=NULL; 
        }
        |
        arg_list WORD{
          commandTable->args->args[n_args++]=$2;

        }

 ;
       
%%








