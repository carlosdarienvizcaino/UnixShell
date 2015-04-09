%{
#include <stdio.h>
#include "y.tab.h"
%}
     
%%
[^ \t\r\n;]*                                    {yylval.str= strdup(yytext); return WORD; }
\".*\"                            { yylval.str = strdup(yytext+1); yylval.str[strlen(yylval.str) - 1] = '\0'; return WORD; }
["\sa-zA-Z0-9\-\*\.\/(\$\{.*\})]+ { yylval.str=strdup(yytext); return WORD; }
\n              { return -1; }
[ \t]+         /* ignore whitespace */;
 
%%

