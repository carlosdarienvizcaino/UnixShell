#ifndef COMMANDS_H
#define COMMANDS_H
#include "structures.h"

void printPrompt();
void execute();
void doLS();
void reset();
int aliasExecution();
int checkForMetaChar(char* c);
void createNewCommand(char* c);
void addArgToCurrentCommand(char* arg);
void addMetaCharToTable(char* arg);
void printCommandTable();

#endif 