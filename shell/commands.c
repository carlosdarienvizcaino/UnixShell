#include "commands.h"
#include "structures.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// ----------------------------------------
void createNewCommand(char* name){
 	
	CommandTable[n_commands].name = name;
	CommandTable[n_commands].argsCount = 0;
	CommandTable[n_commands].args = (ARGS*)malloc(sizeof(ARGS));
	CommandTable[n_commands].args->args[0] = "\0";
	pipe(CommandTable[n_commands].pipe);

	n_commands++;
}
// ----------------------------------------
void addArgToCurrentCommand(char* arg){

	int command_pos = n_commands -1; 
	COMMAND* tempCommand = &CommandTable[ command_pos ];
	tempCommand->args->args[ tempCommand->argsCount++ ] = arg;
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

			printf("\tArgs: %s\n", CommandTable[i].args->args[j]);
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
		doAlias(i);
		environmentExpansion(i);
		environmentExpansion(i);
		if(checkForBuiltIn(CommandTable[i].name)){
			
			runBuiltIn(i);
		}
		
		else if ( checkForCommand(CommandTable[i].name)){
				//God(0);
				runCommand(i);
				
			// If this command has a correspointing meta character
			if ( metachar_count-1 >= i ){

				if (strcmp("|",MetaCharsTable[i])==0){
					runPipe(i);
				}
			}
			
		}
		
	}
	
}


void runPipe(int i){

	int status;
	// If process was prepared successfully
	if ( (CommandTable[i].process = fork()) == 0 ){

		int lastCommand = n_commands - 1;
		char buffer[100];
		
		// Only Command
		if ( n_commands == 1){


		}
		// First Command
		else if ( i == 0){
				
				dup2(CommandTable[i].pipe[1], STDOUT_FILENO);
				
		}		
		// Last Commad
		else if ( i == (n_commands-1) ){

				// Process N reads from process N-1
	        	dup2(CommandTable[i].pipe[0], STDIN_FILENO);
	        
	    }
	    // Default case:
	    else {

	    		// Process N + 1 reads from process N
	        	dup2(CommandTable[i].pipe[0], STDIN_FILENO);
	        	// Process N + 1 writes to process 1
	        	dup2(CommandTable[i].pipe[1], STDOUT_FILENO);

	        	close(CommandTable[i+1].pipe[0]);
	        
	    }
		wait(&status);
	}
}

void runCommand(int i){
	
	int status;
	int n_args= CommandTable[i].argsCount;
	char *a[n_args+1];
	int check=0;
	char *patternBuffer[n_args+1];
	int patternBufferCount=0;
	a[0]=CommandTable[i].name;
	int k;
	int n;
	int count=1;
	for(k=0;k<n_args;k++){
		char* currentArg= CommandTable[i].args->args[k];
		int currLength=strlen(currentArg);
		for(n=0;n<currLength;n++){
			if(currentArg[n]=='*' || currentArg[n]=='?') 
				check=1;
		}
		if(check==0) a[count++]=CommandTable[i].args->args[k];
		else patternBuffer[patternBufferCount++]=currentArg;
		check=0;
	}
	char** b;
	if(patternBufferCount>0)
	b= matchPattern(a,patternBuffer,count);
	else{ 
		a[count]=NULL;
		b=a;
	}
	if ( fork() == 0 ){
		execvp(CommandTable[i].name,a) ;
		exit(status);
	}
	else {

		wait(&status);
	}

	
}

char** matchPattern(char** a, char** patternBuffer, int count){
	int patternCount=1;
	int k;
	for(k=0;k<patternCount;k++){
		glob_t glob_buffer;
		const char * pattern = patternBuffer[k];
		int i;
		int match_count;
		glob( pattern , 0 , NULL , &glob_buffer ); 
		match_count = glob_buffer.gl_pathc;
		for (i=0; i < match_count; i++){
  	 		 a[count]=glob_buffer.gl_pathv[i];
  	 		 count++;
  	 		}
		}
	a[count]=NULL;
	return &*a;
}

void God(int i){
	int status;
	if ( fork() == 0 ){
		char *n[]={"sh","-c" ,input, NULL};
		execvp(n[0],n);
		exit(status);
	}
	else {
		wait(&status);
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
			chdir(CommandTable[i].args->args[n_args-1]);
		}
		else{
			printf("ERROR: TOO MANY ARGUMENTS");
		}
	}
	
	else if(strcmp(command,"setenv")==0 && n_args==2){
		setenv(CommandTable[i].args->args[n_args-2],CommandTable[i].args->args[n_args-1],1);
	}
	else if(strcmp(command,"printenv")==0 && n_args==0){
		int i=0;
		while(environ[i])
           printf("%s\n",environ[i++]);
      }
      
    else if(strcmp(command,"alias")==0){
    	if(n_args==0) alias_printList(aliasNode);
    	
    	else if(n_args==2){
    		char* first= CommandTable[i].args->args[n_args-2];
    		char* second=CommandTable[i].args->args[n_args-1];
    		push(&aliasNode,first,second);
    	}
    }
    
    else if(strcmp(command,"unalias")==0 && n_args==1){
    		char* first= CommandTable[i].args->args[0];
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

int doAlias(int i){
	if(checkForInfiniteAlias(CommandTable[i].args->args[0])==1){
		printf("ALIAS LOOP MOTHERFUCKER\n");
	}
	else if(returnNestedAlias(CommandTable[i].args->args[0])!=0){
		CommandTable[i].args->args[0]=returnNestedAlias(CommandTable[i].args->args[0]);
	}

	return 0;
}

void environmentExpansion(i){
	int n_args=CommandTable[i].argsCount;
	int j;
	int k;
	int check=0;
	for(j=0;j<n_args;j++){
		char* currArg=CommandTable[i].args->args[j];
		if(strlen(currArg)>3){
			if(currArg[0]=='$' && currArg[1]=='{' && currArg[strlen(currArg)-1]=='}'){
				currArg=currArg+2;
				currArg[strlen(currArg)-1]='\0';
				if(getenv(currArg)!=NULL)
				CommandTable[i].args->args[j]=getenv(currArg);
			}
		}
	}
}

void printContentInCurrentDirectory(){
	
	printf("Inside: printContentInCurrentDirectory()\n");
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


