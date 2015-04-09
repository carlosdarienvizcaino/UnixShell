#ifndef STRUCTURES_H
#define STRUCTURES_H

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

int n_commands;
int n_args;


/******STRUCTS*******/
typedef struct node{
   char* alias;
   char* value;
   struct node* next;
} alias_node;

typedef struct arguments{
	char* args[MAXARGS];

} ARGS;

typedef struct command{
	char* name;
	ARGS* args;
} COMMAND;


/****externs******/

alias_node *aliasNode;
COMMAND *commandTable;
extern int yyparse();
extern char yytext[];
extern int yy_scan_string(const char*);
extern char** environ;

/******************/


void push(alias_node **head, char* alias, char* value);
char* retrieveValue(alias_node **head, char* alias);
int aliasExists(alias_node **head,char *alias);
void alias_printList(alias_node *head);
int removeAlias(alias_node **head,char *alias);
int checkForInfiniteAlias(char *c);
char* returnNestedAlias(char *c);


#endif