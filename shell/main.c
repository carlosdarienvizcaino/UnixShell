#include "commands.h"


void shellInit(){
	n_commands=0;
	aliasNode=NULL;  
 	 signal(SIGQUIT, SIG_IGN); 
  	 signal(SIGTSTP, SIG_IGN); 
  	 signal(SIGINT, SIG_IGN);
}


int main(){

shellInit();
while(1){
  printPrompt();
  yyparse();
  }




} 