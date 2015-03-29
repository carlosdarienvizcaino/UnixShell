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
[A-Z]+		yylval.str=yytext; return WORD;
[$][a-zA-Z]+	yylval.str=yytext; return WORD; //not fully correct 
alias		return ALIAS;
unalias		return UNALIAS;
test		return TEST;
\n
[ \t]+         /* ignore whitespace */;

%%
