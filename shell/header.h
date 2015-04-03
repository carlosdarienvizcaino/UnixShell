#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> 
#include  <sys/types.h>
#include <sys/wait.h>


/******GLOBAL CONSTANTS*******/
#define MAXARGS 50
#define OK 0
#define ERROR 1

/****************************/


/********GLOBAL STRUCTURES*******/
char input[1000];


/******************************/

/******STRUCTS*******/
typedef struct node{
   char* alias;
   char* value;
   struct node* next;
} alias_node;

typedef struct comargs{
	char* args[MAXARGS];

} ARGS;

typedef struct com{
	char* name;
	ARGS* args;
} COM;

/***********************************/

/*********EXTERNS************/
extern int yyparse();
extern char yytext[];
extern int yy_scan_string(const char*);

/*****************************/

/*********INITIALIZATIONS************/
ARGS args;
COM* command;

/***********************/


/******PROTOTYPES********/
extern char** environ;
alias_node *aliasNode;      //head of the alias list

static inline char* concat(char *s1, char *s2);
static inline void goToDirectory(char *s);
static inline char* getCurrentDirectory();
static inline int set(char* string, char* string1);
static inline char* get(char* string);
static inline int valid(char* string);
static inline void printPrompt();
static inline char* getCurrentDirectory();
static inline void printContentInCurrentDirectory();
static inline  void push(alias_node **head, char* alias, char* value);
static inline  char* retrieveValue(alias_node **head, char* alias);
static inline void alias_printList(alias_node *head);
static inline  int removeAlias(alias_node **head,char *alias);
static inline void flushArguments();
static inline void runLs(char* args);
static inline int getCommand();
static inline int perform();
static inline int performAlias();
static inline int processCommand(char *c);

/****************************/


/***********YACC**************/


void printPrompt(){
	printf(">");
}
/*******************************/






/*********FUNCTIONS***************/
char* get(char* string){
  char* s=getenv(string);
  printf("%s\n",s);
}

int valid(char* string){
   char* s=getenv(string);
   return s!=NULL? 1:0;
}

void goToDirectory(char *s){ //I dont think I need this.
	
	char *k=getCurrentDirectory();
	while ( k != '\0'){

		printf("%c", *k++);
	}
	//char *k = "hello";
	//char *c=concat(k,s);
	char *c = strcat(k,s);
	chdir(c);
}

int set(char* string, char* string1){ //also need to check the validity of the second string
    if(get(string)){
    	setenv(string,string1,1);
    	return 1;
    }
    else{
    	printf("Environment variable is not valid");
    	return 0;
    }
}

char* getCurrentDirectory(){  //test function to get current directory
	size_t size= sizeof(char) * 1024;
	char * buf= (char *)malloc(size);
	char * cwd;
	if((cwd = getcwd(buf,size))!=NULL){

		printf("%s",cwd);
    	 return cwd;
	}
	return NULL;
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

/* taken from stackoverflow */
/*
char* concat(char *s1, char *s2){

	printf("Before: malloc\n");
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    printf("After: malloc\n");
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
*/

/*************************************************************************/


/*****************LINKED LISTS***********************/


void push(alias_node **head, char* alias, char* value){
	alias_node* curr=*head;
        alias_node* newNode= (alias_node*)malloc(sizeof(alias_node));
        newNode->alias=alias;
        newNode->value=value;
	newNode->next=NULL;
	if(curr!=NULL){
       		 while((curr->next != NULL) && (strcmp(curr->alias,alias)!=0)){
        	  	curr=curr->next;
		 }
		 if(strcmp(curr->alias,alias)==0){
                      curr->value=value;
                      free(newNode);
                 }
                 else
                      curr->next=newNode;
       }
       else{
       		*head=newNode;
       }
}

char* retrieveValue(alias_node **head, char* alias){
	alias_node* curr=*head;
	while(curr!=NULL && strcmp(curr->alias,alias)!=0){
       		curr=curr->next;
        }
	if(strcmp(curr->alias,alias)==0){
		return curr->value;
	}

	return 0;
   
}

void alias_printList(alias_node *head){
	alias_node* curr=head;
	while(curr!=NULL){
		printf("ALIAS: %s VALUE: %s\n",curr->alias,curr->value);
		curr=curr->next;
	}
}

int removeAlias(alias_node **head,char *alias){
	alias_node* curr=*head;
	alias_node* prev=NULL;
	int ran=0;
        while(curr!=NULL && strcmp(curr->alias,alias)!=0){
		prev=curr;
		curr=curr->next;
		ran=1;
	}
	if(ran==0){
		free(*head);
		*head=curr->next;
		return 1;
	}
	if(strcmp(curr->alias,alias)==0 && curr->next!=NULL){
		prev->next=curr->next;
		//free(curr);  //check later. I think I can free the memory.
		return 1;
	}
	else{
		prev->next=NULL;
		return 1;	
	}

	return 0;
}

/*****************************************************************/


int getCommand(){
	fgets(input,sizeof(input),stdin);
	yy_scan_string(input);

	if(yyparse()){
		return ERROR;
	}
	else{
		return OK;
	}
}

int perform(){
	char* com= command->name;
	if(strcmp(com,"bye")==0) exit(0);

	if(strcmp(com,"cd")==0 && command->args->args[0]==NULL ){
		chdir(getenv("HOME"));
	}
	else{
		chdir(command->args->args[0]);
	}
	//add ls fork thing here


}

int performAlias(){
	push(&aliasNode,command->args->args[0],command->args->args[1]);
	return 1;
}



int processCommand(char *c){      //fix this. Kind of doing it right now but yeah. Maybe add more arguments. 
	char* temp;
	if(retrieveValue(&aliasNode,c))return retrieveValue(&aliasNode,c);
	else return 0;

}

	








#endif
