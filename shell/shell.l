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
ls		return LS;
[a-zA-Z]+		return WORD;
alias		return ALIAS;
unalias		return UNALIAS;
test		return TEST;
\n
[ \t]+         /* ignore whitespace */;

%%
