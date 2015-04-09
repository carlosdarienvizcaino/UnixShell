
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
      | commands arg_list {if(checkForBuiltIn(CommandTable[0]->name)==1) execute(); n_commands = 0; }

arg_list:
       WORD{

           printf("COMMANDS: %d\n", n_commands);

           // Creates a new Command: set argsCount to zero
           COMMAND* newCommand = getNewCommand();

           // Give a name to the command
           newCommand->name = $1;

        }
        |
        arg_list WORD{

          printf("%s\n", $2);
          
          // Check if is a builtin command
          if ( checkForBuiltIn($2)  || checkForMetaChar($2) ){

              // Set the prev command to table 

              // Create new command

              // Increment command count

              if ( checkForMetaChar($2) ){

                  // set character to metaChar array

                  // Increment metachar count
              }
          }
          else {

              // set this argument to the argument of the current command

              // increment argument count for this command
          }

        }

 ;
       
%%








