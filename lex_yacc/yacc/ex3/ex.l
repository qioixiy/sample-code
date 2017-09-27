%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
zone       				printf("zone\n"); return  ZONETOK;
file           			printf("file:%s\n", yytext); return FILETOK;
[a-zA-Z][a-zA-Z0-9]*   	printf("WORD:%s\n", yytext); yylval = strdup(yytext); return  WORD;
[a-zA-Z0-9\/.-]+      	printf("FILENAME:%s\n", yytext); yylval = strdup(yytext); return  FILENAME;
\"         				printf("QUOTE\n"); return  QUOTE;
\{         				printf("OBRACE\n"); return  OBRACE;
\}         				printf("EBRACE\n"); return  EBRACE ;
;              			printf("SEMICOLON\n"); return SEMICOLON;
[ \t]+     				/* ignore whitespace */;
\n         				printf("enter\n");/* ignore EOL */;
%%
