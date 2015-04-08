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
alias		return ALIAS;
unalias		return UNALIAS;
test		return TEST;
"\""[*? ${}_,<>|&\"@!#%'=~.:/:A-Za-z0-9]+"\""  { yylval.str=strdup(yytext); yylval.str[strlen(yylval.str)-1] ='\0'; yylval.str[0]='\0';  yylval.str++;return WORD;}
["\sa-zA-Z0-9\-\*\.\/(\$\{.*\})]+ { yylval.str=strdup(yytext); return WORD; }
\n		{ return -1; }
[ \t]+         /* ignore whitespace */;

%%
