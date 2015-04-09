#include "commands.h"


void printPrompt(){
	printf("> ");
}


void execute(){
	char* command= commandTable->name;
	char* first=commandTable->args->args[0];
	char* second= commandTable->args->args[1];

	if(aliasExecution(first)==1) return;
	else first=commandTable->args->args[0];



	if(strcmp(command,"cd")==0){
		if(first==NULL){
			chdir(getenv("HOME"));
		}
		else{
			chdir(first);
		}
	}
	else if(strcmp(command,"setenv")==0){
		setenv(first,second,1);
	}
	else if(strcmp(command,"printenv")==0){
		int i=0;
		while(environ[i])
           printf("%s\n",environ[i++]);
      }
    else if(strcmp(command,"alias")==0){
    	if(first==NULL){
    		alias_printList(aliasNode);
    	}
    	else if(first!=NULL && commandTable->args->args[1]!=NULL){
    		push(&aliasNode,first,second);
    	}
    }
    else if(strcmp(command,"unalias")==0){
    	if(first!=NULL){
    		removeAlias(&aliasNode,first);
    	}
    }

    else if(strcmp(command,"bye")==0){
    	exit(0);
    }
	reset();



	}



void reset(){
	commandTable = (COMMAND*)malloc(sizeof(COMMAND));
	commandTable->args= (ARGS *)malloc(sizeof(ARGS));
	
		

	n_commands=0;
	n_args=0;

}


int aliasExecution(char *c){
	//if(checkForInfiniteAlias(c)==1){
		//printf("Alias loop");
		//return 1;
	//}
	 if(returnNestedAlias(c)!=0){
		printf("THIS RUNS\n");
		commandTable->args->args[0]=returnNestedAlias(c);
	}
	else if(aliasExists(&aliasNode,c)){
		commandTable->args->args[0]= retrieveValue(&aliasNode,c);
	}
	return 0;
}

