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

	int i;
	for(i=0;i<n_commands;i++){
		
		if(checkForBuiltIn(CommandTable[i].name)){
			runBuiltIn(i);
		}
		else if ( checkForCommand(CommandTable[i].name)){

				runCommand(i);

			if ( checkForMetaChar(MetaCharsTable[i]) && metachar_count-1 >= i ){


			}
		}



	}
}


void runPipe(){

}

void runCommand(int i){
	char* command= CommandTable[i].name;
	int n_args = CommandTable[i].argsCount;


 	if(strcmp(command,"ls")==0 && n_args==0){
		printContentInCurrentDirectory();		

 	}


}

void runBuiltIn(int i){
	char* command= CommandTable[i].name;
	int n_args= CommandTable[i].argsCount;

	if(strcmp(command,"cd")==0){
		if(n_args==0){
			chdir(getenv("HOME"));
		}
		else if(n_args==1){
			chdir(CommandTable[i].args[n_args-1]);
		}
		else{
			printf("ERROR: TOO MANY ARGUMENTS");
		}
	}
	
	else if(strcmp(command,"setenv")==0 && n_args==2){
		setenv(CommandTable[i].args[n_args-2],CommandTable[i].args[n_args-1],1);
	}
	else if(strcmp(command,"printenv")==0 && n_args==0){
		int i=0;
		while(environ[i])
           printf("%s\n",environ[i++]);
      }
      
    else if(strcmp(command,"alias")==0){
    	if(n_args==0) alias_printList(aliasNode);
    	
    	else if(n_args==2){
    		char* first= CommandTable[i].args[n_args-2];
    		char* second=CommandTable[i].args[n_args-1];
    		push(&aliasNode,first,second);
    	}
    }
    
    else if(strcmp(command,"unalias")==0 && n_args==1){
    		char* first= CommandTable[i].args[0];
    		removeAlias(&aliasNode,first);
    }
    else if(strcmp(command,"bye")==0){
    	exit(0);
    }
    
	//reset();
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

void printContentInCurrentDirectory(){
	
	printf("Inside the function\n");
	char* currentDirectory = getCurrentDirectory();
	DIR* dirp = opendir( getCurrentDirectory() );
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL){
		printf("%s ",dp->d_name);
		dp++;
	}
	printf("\n");
}


char* getCurrentDirectory(){  //test function to get current directory
	size_t size= sizeof(char) * 1024;
	char * buf= (char *)malloc(size);
	char * cwd;
	if((cwd = getcwd(buf,size))!=NULL){

		//printf("%s",cwd);
    	 return cwd;
	}
	return NULL;
}


