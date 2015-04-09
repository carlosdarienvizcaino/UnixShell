#include "commands.h"


void shellInit(){
	n_args=0;
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

shellInit();
commandTable = (COMMAND*)malloc(sizeof(COMMAND));
commandTable->args= (ARGS *)malloc(sizeof(ARGS));
while(1){
  yyparse();
  getCurrentDirectory();
  }

} 