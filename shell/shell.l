/*
///space
*/


%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
bye		return BYE;
setenv		return SETENV;
unsetenv 	return UNSETENV;
printenv	return PRINTENV;
cd		return CD;
[$][a-zA-Z]+	return WORD; //not fully correct
[ \t]+         /* ignore whitespace */;

%%
