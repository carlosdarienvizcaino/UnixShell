#ifndef COMMANDS_H
#define COMMANDS_H
#include "structures.h"
#include "glob.h"
char input[500];

void printPrompt();
void execute();
void runBuiltIn();
void doLS();
void reset();
int doAlias(int i);
int checkForMetaChar(char* c);
void createNewCommand(char* c);
void addArgToCurrentCommand(char* arg);
void addMetaCharToTable(char* arg);
void runCommand(int i);
void printCommandTable();
char* getCurrentDirectory();
void printContentInCurrentDirectory();
void runPipe(int i);
void GodsHelper();
void God(int i);
char** matchPattern(char** a, char** patternBuffer, int count);
void environmentExpansion(int i);
void clearInput();


#endif 