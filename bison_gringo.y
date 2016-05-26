/*

	Analisador Sintático do GRINGO (Linguagem C)
	Parser of GRINGO (C Language)
*/

%{

	#include "classes_gringo.hpp"
	//#include <stdio.h>
	//#include <stdlib.h>
	//#include <string.h>
	void yyerror(const char *isso) {printf("%s\n", isso);}
	using namespace std;

	extern int yylex();

%}

%token CHAR;
%token LOG2;
%token EXP;
%token INT;
%token FLOAT;
%token DOUBLE;
%token VOID;
%token UNSIGNED;
%token SIGNED;
%token SHORT;
%token LONG;
%token CONST;
%token STATIC;
%token SIZEOF;
%token EQUAL;
%token SUBTRACT;
%token DOC_PARAM;
%token ADD;
%token MUL;
%token DIV;
%token REST;
%token GREATER_THEN;
%token LESS_THEN;
%token NOT;
%token XOR;
%token MARK;
%token COMMA;
%token DOT;
%token TWO_DOTS;
%token DOT_COMMA;
%token PAR_L;
%token PAR_R;
%token COL_L;
%token COL_R;
%token BRA_L;
%token BRA_R;
%token QUOTE;
%token DOUBLE_QUOTE;
%token IF;
%token ELSE;
%token SWITCH;
%token CASE;
%token BREAK;
%token DEFAULT;
%token FOR;
%token WHILE;
%token DO;
%token RETURN;
%token EXIT;
%token CONTINUE;
%token IDENTIFIER;
%token LITERAL_INT;
%token LITERAL_DOUBLE;
%token NEW_LINE;
%token CARRIAGE_RETURN;
%token TAB;
%token TILDE;
%token BACKSLASH;
%token BAR_ZERO;

%union {
	int int_value;
	double double_value;
	char char_value;
	class Value *value;
};

%type<char_value> CHAR;
%type<int_value> LITERAL_INT;
%type<double_value> FLOAT;
%type<double_value> LITERAL_DOUBLE;
%type<value> Value;
//...

%%

 

Program : ExpList; 

ExpList : Command  
		  |Commands; 

Commands : ExpList NEW_LINE Command {} //Só uma produção complexa

Command : Atribuition //Relação "é"
		|Exp {}

Exp : BinExpPlus {} 

	 |BinExpMinus {} 

	 |Factor {};

BinExpPlus : Exp ADD Factor; // Token pode ignorar pois é ele sempre 

BinExpMinus : Exp SUBTRACT Factor;
  
Factor : FactorMUL {} 	
		|FactorDIV {} 
		|UnExp {};

FactorMUL : Factor MUL UnExp{}		

FactorDIV : Factor DIV UnExp {}

UnExp : UnExpPlus {}     
        |UnExpMinus {}
		|UnExpLog {}
		|UnExpExp {}
		|Value {};

UnExpPlus : ADD Value{}

UnExpMinus : SUBTRACT Value{}

UnExpLog : LOG2 PAR_L Exp PAR_R{}

UnExpExp : EXP PAR_L Exp PAR_R{}			

Value : LITERAL_INT {
		IntValue *fallen = new IntValue($1);
		Operations *op;
		op = new Operations();
		fallen->accept(op);
		$$ = new IntValue($1);
		printf("Valor int passado na producao Valor : %d\n\n", static_cast <IntValue*> ($$)->getValue());
	}
		|LITERAL_DOUBLE{}
		|LparExpRpar{}
		|IDENTIFIER {};

LparExpRpar : PAR_L Exp PAR_R 

Atribuition : IDENTIFIER EQUAL Exp

