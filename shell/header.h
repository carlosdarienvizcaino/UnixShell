#ifndef HEADER_H
#define HEADER_H


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













#endif
