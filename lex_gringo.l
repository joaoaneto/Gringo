/*

	Analisador Léxico do GRINGO (Linguagem C)
	Flex Scanner of GRINGO (C Language)
	
	Tokens sugeridos:
	Suggested tokens:
	
	CHAR, INT, FLOAT, DOUBLE, VOID, UNSIGNED, SIGNED, SHORT, LONG, CONST,
	VOLATILE, EXTERN, STATIC, REGISTER, AUTO, SIZEOF,
	
	EQUAL, SUBTRACT, ADD, MUL, DIV, REST, GREATER_THEN, LESS_THEN, NOT,
	ECOMM, XOR, TILDE, MARK, COMMA, DOT, TWO_DOTS, DOT_COMMA, PAR_L,
	PAR_R, COL_L, COL_R, BRA_L, BRA_R, QUOTE, DOUBLE_QUOTE,
	
	IF, ELSE, SWITCH, CASE, BREAK, DEFAULT, FOR, WHILE, DO, RETURN, EXIT,
	CONTINUE, NULL,
	
	IDENTIFIER, LITERAL_INT, LITERAL_DOUBLE, HEXADECIMAL, OCTAL,
	
	NEW_LINE, CARRIAGE_RETURN, TAB, BACKSLASH, BAR_ZERO

*/

%{

	#include "bison_gringo.hpp"

%}

%option noyywrap nodefault

%%

"char"		{ return CHAR; }
"int"		{ return INT; }
"float"		{ return FLOAT; }
"double"	{ return DOUBLE; }
"void"		{ return VOID; }
"unsigned"	{ return UNSIGNED; }
"const"		{ return CONST; }
"static" 	{ return STATIC; }
"log"		{return LOG2;}
"exp"	{return EXP;}
"="		{ return EQUAL; }
"-"		{ return SUBTRACT; }
"+"		{ return ADD; }
"*"		{ return MUL; }
"/"		{ return DIV; }
"%"		{ return REST; }
">"		{ return GREATER_THEN; }
"<"		{ return LESS_THEN; }
"!"		{ return NOT; }
"^"		{ return XOR; }
"sizeof"	{ return SIZEOF; }
","		{ return COMMA; }
"."		{ return DOT; }
":"		{ return TWO_DOTS; }
";"		{ return DOT_COMMA; }
"("		{ return PAR_L; }
")"		{ return PAR_R; }
"["		{ return COL_L; }
"]"		{ return COL_R; }
"{"		{ return BRA_L; }
"}"		{ return BRA_R; }
\'		{ return QUOTE; }
\"		{ return DOUBLE_QUOTE; }
"if"		{ return IF; }
"else"		{ return ELSE; }
"break"		{ return BREAK; }
"for"		{ return FOR; }
"while"		{ return WHILE; }
"return"	{ return RETURN; }
"exit"		{ return EXIT; }
"continue"	{ return CONTINUE; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.id_value = strdup(yytext); return IDENTIFIER; }
[0-9]+		{ yylval.int_value = atoi(yytext); return LITERAL_INT; }
[0-9]+[\.][0-9]+	{ yylval.double_value = atof(yytext); return LITERAL_DOUBLE; }
"\r"		{ return CARRIAGE_RETURN; }
"\t"		{ return TAB; }
[\\]		{ return BACKSLASH; }
"\0"		{ return BAR_ZERO; }
[\n\r\t ]	{}
.		{ printf("Caractere inválido: %s",yytext); exit(1); }
%%