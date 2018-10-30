%{
#include "yacc.h"
%}
%option     noyywrap
%option     nounput

COMMENT       "(*"([^\*]|(\*)*[^\*\)])*(\*)*"*)" 
NCOMMENT      "(*"([^\*]|(\*)*[^\*\)])*(\*)*""
LETTER        [a-zA-Z]
DIGIT         [0-9]
INTEGER       {DIGIT}+
MINTEGER      "-"{INTEGER}
REAL          {DIGIT}+"."{DIGIT}*
MREAL	      "-"{REAL}
WS            [ \t\n]+
RESERVE_W     (AND|ARRAY|BEGIN|BY|DIV|DO|ELSE|ELSIF|END|EXIT|FOR|IF|IN|IS|LOOP|MOD|NOT|OF|OR|OUT|PROCEDURE|PROGRAM|READ|RECORD|RETURN|THEN|TO|TYPE|VAR|WHILE|WRITE)
OPERATOR      ":="|"+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"="|"<>"
DELIMITER     ":"|";"|","|"."|"("|")"|"["|"]"|"{"|"}"|"[<"|">]"|"\\"
STRINGS       \"[^"\n\t]*\"
TL_STRINGS    (\"[^"]*\")
NSTRINGS      (\"[^"\n]*)   
IDENTIFIER    {LETTER}({LETTER}|{DIGIT})*
UNPRINTED     [\x00-\x08\x0A-\x1F\x7F]

%%
<<EOF>>		   return EOF;
{WS}               return WS;/*here you need to count the number of cols and rows of tokens,so you cannot simply skip them*/
{DELIMITER} 	   return DELIMITER;
{COMMENT}	   return COMMENT;
{NCOMMENT}	   return NCOMMENT;
{DELIMITER}	   return DELIMITER;
{OPERATOR}	   return OPERATOR;
{STRINGS}	   return STRINGS;
{TL_STRINGS}	   return TL_STRINGS;
{NSTRINGS}	   return NSTRINGS;
{RESERVE_W}	   return RESERVE_W;
{IDENTIFIER}       return IDENTIFIER;
{INTEGER}          return INTEGER;
{REAL}		   return REAL;
{MINTEGER}	   return MINTEGER;
{MREAL}		   return MREAL;
{UNPRINTED}	   return UNPRINTED;
%%
