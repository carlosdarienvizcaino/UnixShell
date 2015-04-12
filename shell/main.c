#include "commands.h"


void displayArt(){
	int status;
	if ( fork() == 0 ){
		char *n[]={"sh","-c" ,"cat art.txt", NULL};

		execvp(n[0],n);
		exit(status);
	}
	else {
		wait(&status);
	}
}


void shellInit(){
	n_commands=0;
	aliasNode=NULL;  
	displayArt();
 	 signal(SIGQUIT, SIG_IGN); 
  	 signal(SIGTSTP, SIG_IGN); 
  	 signal(SIGINT, SIG_IGN);
}


int main(){

shellInit();
while(1){
  //printPrompt();
  yyparse();
  }




} 