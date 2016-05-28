/*

	Analisador Sintático do GRINGO (Linguagem C)
	Parser of GRINGO (C Language)
*/

%{

	#include "visitor.hpp"
	//#include <stdio.h>
	//#include <stdlib.h>
	//#include <string.h>
	void yyerror(const char *isso) {/*printf("%s\n", isso);*/}
	extern int yylex();
	
	using namespace std;
	
	Operations *op = new Operations();

%}

%token CHAR;
%token LOG2;
%token EXP;
%token INT;
%token FLOAT;
%token DOUBLE;
%token VOID;
%token UNSIGNED;
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
%token BREAK;
%token FOR;
%token WHILE;
%token RETURN;
%token EXIT;
%token CONTINUE;
%token IDENTIFIER;
%token LITERAL_INT;
%token LITERAL_DOUBLE;
%token NEW_LINE;
%token CARRIAGE_RETURN;
%token TAB;
%token BACKSLASH;
%token BAR_ZERO;

%union {
	int int_value;
	double double_value;
	char char_value;
	class Value *value;
	class Exp *exp;
	class Factor *factor;
	class BinExpPlus *binexpplus;
};

%type<char_value> CHAR;
%type<int_value> LITERAL_INT;
%type<double_value> FLOAT;
%type<double_value> LITERAL_DOUBLE;
%type<value> Value;
%type<exp> Exp;
%type<factor> Factor;
%type<binexpplus> BinExpPlus;

//...

%%

 

Program : ExpList
;

ExpList : Command  
		|Commands
; 

Commands : ExpList NEW_LINE Command {} //Só uma produção complexa

Command : Atribuition //Relação "é"
		|Exp {}
;

Exp : BinExpPlus {} 
	 |BinExpMinus {} 
	 |Factor {}
;

BinExpPlus : Exp ADD Factor {
		BinExpPlus *fallen = new BinExpPlus($1,$3);
		fallen->accept(op);
		$$ = new BinExpPlus($1,$3);
	}
;  

BinExpMinus : Exp SUBTRACT Factor
;
  
Factor : FactorMUL {} 	
		|FactorDIV {}
		|UnExp {}
;

FactorMUL : Factor MUL UnExp{}
;		

FactorDIV : Factor DIV UnExp {}
;

UnExp : UnExpPlus {}     
        |UnExpMinus {}
		|UnExpLog {}
		|UnExpExp {}
		|Value {}
;

UnExpPlus : ADD Value{}
;

UnExpMinus : SUBTRACT Value{}
;

UnExpLog : LOG2 PAR_L Exp PAR_R{}
;

UnExpExp : EXP PAR_L Exp PAR_R{}			
;

Value : LITERAL_INT {
			IntValue *fallen = new IntValue($1);
			fallen->accept(op);
			$$ = new IntValue($1);
	}
		|LITERAL_DOUBLE{
			DoubleValue *fallen = new DoubleValue($1);
			fallen->accept(op);
			$$ = new DoubleValue($1);
	}
		|LparExpRpar{}
		|IDENTIFIER {}
;

LparExpRpar : PAR_L Exp PAR_R
; 

Atribuition : IDENTIFIER EQUAL Exp{
	
}
;
