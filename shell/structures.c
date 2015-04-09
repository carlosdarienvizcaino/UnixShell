#include "structures.h"

char *builtInList[]={"setenv","printenv","unsetenv", "cd", "alias", "unalias","bye", "\0"};
char *commandList[]={"ls","\0"};

/**********************ALIAS LIST METHODS****************/

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


int aliasExists(alias_node **head,char *alias){
	alias_node* curr=*head;
	while(curr!=NULL){
		if(strcmp(curr->alias,alias)==0)
			return 1;
       curr=curr->next;
        }
return 0;

}

void alias_printList(alias_node *head){
	alias_node* curr=head;
	while(curr!=NULL){
		printf("%s = %s\n",curr->alias,curr->value);
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

int checkForInfiniteAlias(char *c){
	char* currVal;
	char* nextVal;
	if(aliasExists(&aliasNode,c)){
		currVal=retrieveValue(&aliasNode,c);
		if(aliasExists(&aliasNode,currVal)){
			nextVal=retrieveValue(&aliasNode,currVal);
		}
		if(strcmp(c,nextVal)==0) return 1;
	}
	return 0;
}

char* returnNestedAlias(char *c){
	char* currVal;
	if(aliasExists(&aliasNode,c)){
		currVal=retrieveValue(&aliasNode,c);
		if(aliasExists(&aliasNode,currVal)){
			return retrieveValue(&aliasNode,currVal);
		}
	}
	return 0;
}


		
/**************************************************************/
int checkForBuiltIn(char *c){
	int i=0;
	while(strcmp(builtInList[i],"\0") != 0){
		
		if(strcmp(c,builtInList[i])==0){
			return 1;
		}

	}
	return 0;
}
/**************************************************************/
int checkForCommand(char *c){
	int i=0;
	while( strcmp(commandList[i],"\0") != 0 ){
		
		if(strcmp(c,commandList[i])==0){
			
			return 1;
		}
		i++;
	}
	return 0;
}