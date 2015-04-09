#include "commands.h"
#include "structures.h"
#include <stddef.h>

// ----------------------------------------
void createNewCommand(char* name){
 	
	CommandTable[n_commands].name = name;
	CommandTable[n_commands].argsCount = 0;
	n_commands++;
}
// ----------------------------------------
void addArgToCurrentCommand(char* arg){

	int command_pos = n_commands -1; 
	COMMAND* tempCommand = &CommandTable[ command_pos ];
	tempCommand->args[ tempCommand->argsCount++ ] = arg;
}
// ----------------------------------------
void addMetaCharToTable(char* arg){

	MetaCharsTable[ metachar_count++ ] = arg;
}
// ----------------------------------------
void printCommandTable(){

	printf("Printing Command Table:\n");
	int i, j;
	for (i= 0; i < n_commands; i++){

		printf("\n--------------------\n");
		printf("Command Name: %s\n ", CommandTable[i].name);
		for (j=0; j < CommandTable[i].argsCount; j++){

			printf("\tArgs: %s\n", CommandTable[i].args[j]);
		}

		if ( metachar_count <= i){
			for (j=0; j < metachar_count; j++){

				printf("\tMeta Char(s) : %s\n", MetaCharsTable[j]);
			}
		}
	}

	printf("After command table\n");
}
// ----------------------------------------
int checkForMetaChar(char* c){

	printf("Inside checkForMetaChar() \n");
	printf("Word: %s \n", c);
	printf("Result %d\n", strcmp(c, "|") );

	if ( strcmp(c, "|") == 0){

		return 1;
	}
	else if (strcmp(c, ">") ==0){

		return 1;
	}
	else if ( strcmp(c, "<") == 0){

		return 1;
	}

	return 0;
}
// ----------------------------------------
void printPrompt(){
	printf("> ");
}
// ----------------------------------------
void execute(){

	char* command= CommandTable[0].name;
	char* first=CommandTable[0].args[0];
	char* second= CommandTable[0].args[1];

	//if(aliasExecution(first)==1) return;
	//else first=Command.args.args[0];

	/*

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
    	else if(first!=NULL && Command->args->args[1]!=NULL){
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
	
	*/
	
	}
// ---------------------------------------- 
void reset(){
	
	n_commands = 0; 
	metachar_count = 0;
}
// ----------------------------------------
int aliasExecution(char *c){
	//if(checkForInfiniteAlias(c)==1){
		//printf("Alias loop");
		//return 1;
	//}

	/*
	 if(returnNestedAlias(c)!=0){
		printf("THIS RUNS\n");
		Command->args->args[0]=returnNestedAlias(c);
	}
	else if(aliasExists(&aliasNode,c)){
		Command->args->args[0]= retrieveValue(&aliasNode,c);
	}
	*/
	return 0;
}

