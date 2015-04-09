
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
%type<arg> arg_list

%%

commands: /* empty */
        | commands arg_list { printCommandTable();}

arg_list:
       WORD{

           // Creates a new Command: set argsCount to zero and the name
           reset();
           createNewCommand($1);
        }
        |
        arg_list WORD{

          printf("%s\n", $2);
          
          // Check if is a buildin command
          if ( checkForBuiltIn($2) || checkForCommand($2) ){

              // Create new command
              createNewCommand($2);

          } 
          else if (checkForMetaChar($2)){

              // Add character to metaChar array
              addMetaCharToTable($2);
          }
          else {

              // Set this argument to the argument of the current command
              addArgToCurrentCommand($2);
          }

        }
        ;
       
%%








