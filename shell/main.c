#include "commands.h"


void shellInit(){
	n_commands=0;
	aliasNode=NULL; //check this out.
}

char* getCurrentDirectory(){  //test function to get current directory
	size_t size= sizeof(char) * 1024;
	char * buf= (char *)malloc(size);
	char * cwd;
	if((cwd = getcwd(buf,size))!=NULL){

		printf("%s\n",cwd);
    	 return cwd;
	}
	return NULL;
}


int main(){

	//CommandTable[MAXCMDS]= (COMMAND*) malloc((MAXCMDS)*sizeof(COMMAND));
	//Command = (COMMAND*)malloc(sizeof(COMMAND));
	//Command->args = (char*)malloc(sizeof(char)*MAXARGS);
	//metaChars[MAXMETACHARS]=(char*) malloc((MAXMETACHARS)*sizeof(char*));  //might fail in the future 
shellInit();
while(1){
  printPrompt();
  yyparse();
  //getCurrentDirectory();
  }

} 