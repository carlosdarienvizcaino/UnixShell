
%{
#include "commands.h"
#include "structures.h"
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

COMMAND* newCommand;
%}


%union   
{

char *str;
struct arguments *arg;
}

%token <str> WORD
%token <arg> argv
%token END_OF_FILE
%type<arg> arg_list

%%

commands: /* empty */
        | commands arg_list{execute();}
        | eof

arg_list:
       WORD{
           // Creates a new Command: set argsCount to zero and the name
           reset();
           createNewCommand($1);
        }
        |
        arg_list WORD{

          // Check if is a buildin command
          if ( checkForBuiltIn($2) || checkForCommand($2) ){
          //if (checkForCommand($2)){

              // Create new command
              createNewCommand($2);

          }
          else {

              // Set this argument to the argument of the current command
              addArgToCurrentCommand($2);
          }

        }
        ;
eof:
    END_OF_FILE{
        exit(1);
    }
       
%%








