/*

	Analisador Léxico do GRINGO (Linguagem C)

	Tokens sugeridos:

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

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "bison_gringo.hpp"

	extern int yyparse();
	
%}

%option yynowrap nodefault

%%

"char"		{ return CHAR; }
"int"		{ return INT; }
"float"		{ return FLOAT; }
"double"	{ return DOUBLE; }
"void"		{ return VOID; }
"unsigned"	{ return UNSIGNED; }
"signed"	{ return SIGNED; }
"short"		{ return SHORT; }
"long"		{ return LONG; }
"const"		{ return CONST; }
"volatile"	{ return VOLATILE; }
"extern"	{ return EXTERN; }
"static" 	{ return STATIC; }
"register"	{ return REGISTER; }
"auto"		{ return AUTO; }
"="			{ return EQUAL; }
"-"			{ return SUBTRACT; }
"+"			{ return ADD; }
"*"			{ return MUL; }
"/"			{ return DIV; }
"%"			{ return REST; }
">"			{ return GREATER_THEN; }
"<"			{ return LESS_THEN; }
"!"			{ return NOT; }
"&"			{ return ECOMM; }
"^"			{ return XOR; }
"~" 		{ return TILDE; }
"?"			{ return MARK; }
"sizeof"	{ return SIZEOF; }
","			{ return COMMA; }
"."			{ return DOT; }
":"			{ return TWO_DOTS; }
";"			{ return DOT_COMMA; }
"("			{ return PAR_L; }
")"			{ return PAR_R; }
"["			{ return COL_L; }
"]"			{ return COL_R; }
"{"			{ return BRA_L; }
"}"			{ return BRA_R; }
\'			{ return QUOTE; }
\"			{ return DOUBLE_QUOTE; }
"if"		{ return IF; }
"else"		{ return ELSE; }
"switch"	{ return SWITCH; }
"case"		{ return CASE; }
"break"		{ return BREAK; }
"default"	{ return DEFAULT; }
"for"		{ return FOR; }
"while"		{ return WHILE; }
"do"		{ return DO; }
"return"	{ return RETURN; }
"exit"		{ return EXIT; }
"continue"	{ return CONTINUE; }
"NULL"		{ return NULL; }

[a-zA-Z_][a-zA-Z0-9_]*	{ return IDENTIFIER; }
[-]?[0-9]+				{ return LITERAL_INT; }
[-]?[0-9]+[\.][0-9]+	{ return LITERAL_DOUBLE; }
[0][x][0-9a-f]+			{ return HEXADECIMAL; }
[0][0-8]+				{ return OCTAL; }
"\n"		{ return NEW_LINE; }
"\r"		{ return CARRIAGE_RETURN; }
"\t"		{ return TAB; }
"\"			{ return BACKSLASH; }
"\0"		{ return BAR_ZERO; }
[\n\r\t ]	{}
.			{ printf("Caractere inválido: %s",yytext); exit(1); }

%%

int main(int argc, char ** argv){
		
	yyin = fopen (argv[1],"r"); /*Arquivo de entrada */
	
	if(argc != 2){
		printf("Tem que ter o nome do arquivo\n\n");
			return 1;
	}

	if(yyparse()){
		printf("Error!!\n");
		return 1;
	}

	return 0;
}	