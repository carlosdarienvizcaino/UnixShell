#include "commands.h"


void shellInit(){
	n_commands=0;
	aliasNode=NULL; //check this out.
}

int main(){

	//CommandTable[MAXCMDS]= (COMMAND*) malloc((MAXCMDS)*sizeof(COMMAND));
	//Command = (COMMAND*)malloc(sizeof(COMMAND));
	//Command->args = (char*)malloc(sizeof(char)*MAXARGS);
	//metaChars[MAXMETACHARS]=(char*) malloc((MAXMETACHARS)*sizeof(char*));  //might fail in the future 
shellInit();
while(1){
  printPrompt();
  fgets(input,sizeof(input),stdin);
    yy_scan_string(input);
  yyparse();
  }

} 