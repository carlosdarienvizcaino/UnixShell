#ifndef COMMANDS_H
#define COMMANDS_H
#include "structures.h"

void printPrompt();
void execute();
void runBuiltIn();
void doLS();
void reset();
int aliasExecution();
int checkForMetaChar(char* c);
void createNewCommand(char* c);
void addArgToCurrentCommand(char* arg);
void addMetaCharToTable(char* arg);
void runCommand(int i);
void printCommandTable();
char* getCurrentDirectory();
void printContentInCurrentDirectory();

#endif 