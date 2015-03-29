#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct node{
   char* alias;
   char* value;
   struct node* next;
} alias_node;

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




#endif
