
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
      | commands arg_list {if(checkForBuiltIn(CommandTable[0]->name)==1) execute(); }

arg_list:
       WORD{
           Command->name=$1;
           Command->args->args[0]=NULL; 
           CommandTable[n_commands]=Command;
        }
        |
        arg_list WORD{
          CommandTable[n_commands]->args->args[CommandTable[n_commands]->args_count++]=$2;

        }

 ;
       
%%








