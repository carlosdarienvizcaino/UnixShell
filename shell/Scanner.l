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
[a-zA-Z0-9\-\*\.\/(\$\{.*\})]+ { yylval.str=yytext; return WORD; }
\n		{ return -1; }
[ \t]+         /* ignore whitespace */;

%%
