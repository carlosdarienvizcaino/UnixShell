#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

char* get(char* string){
  char* s=getenv(string);
  printf("%s\n",s);
}

int valid(char* string){
   char* s=getenv(string);
   return s!=NULL? 1:0;
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

char* getDirectory(){  //test function to get current directory
	size_t size= sizeof(char) * 1024;
	char * buf= (char *)malloc(size);
	char * cwd;
	if((cwd = getcwd(buf,size))!=NULL){
    	 return cwd;
	}
	return;
}

void printContentInCurrentDirectory(){
	
	printf("Inside the function\n");
	char* currentDirectory = getDirectory();
	DIR* dirp = opendir( getDirectory() );
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL){
		printf("%s ",dp->d_name);
		dp++;
	}
	printf("\n");
}
#endif
