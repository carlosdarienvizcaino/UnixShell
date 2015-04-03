#include "header.h"




int main(){
aliasNode=NULL;
command = (COM*)malloc(sizeof(COM));
command->args= (ARGS *)malloc(sizeof(ARGS));

while(1){
    printPrompt();
    getCommand();
  }

} 
