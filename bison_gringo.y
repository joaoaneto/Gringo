/*

	Analisador Sintático do GRINGO (Linguagem C)
	Parser of GRINGO (C Language)
*/

%{

	#include "classes_gringo.hpp"
	#include <map>
	#include <iostream>
	#include <stdio.h>

	extern int yylex();

	void yyerror(const char *error) { 
		printf("Erro no lex: %s\n", error);
	}

	using namespace std;
	
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
	char *id_value;
	class Program *program;
	class ExpList *explist;
	class Command *command;
	class Value *value;
	class Exp *exp;
	class BinExpLessGreater *belg;
	class BinExpPlusMinus *bepm;
	class UnExp *unexp;
	class Factor *factor;
	class BinExpPlus *binexpplus;
	class BinExpMinus *binexpminus;
	class BinExpLessThen *binexplessthen;
	class BinExpGreaterThen *binexpgreaterthen;
	class FactorMul *factormul;
	class FactorDiv *factordiv;
	class UnExpPlus *unexpplus;
	class UnExpMinus *unexpminus;
	class UnExpLog *unexplog;
	class UnExpExp *unexpexp;
	class LparExpRpar *lparexprpar;
	class Assignment *assignment;
	class IfElseIf *ifelseif;
	class If *ift;
	class IfElse *ifelset;
	class While *wwhile;
};

%type<program> Program;
%type<explist> ExpList;
%type<command> Command;
%type<char_value> CHAR;
%type<int_value> LITERAL_INT;
%type<double_value> FLOAT;
%type<double_value> LITERAL_DOUBLE;
%type<id_value> IDENTIFIER;
%type<value> Value;
%type<exp> Exp;
%type<belg> BinExpLessGreater;
%type<bepm> BinExpPlusMinus;
%type<factor> Factor;
%type<unexp> UnExp;
%type<binexpplus> BinExpPlus;
%type<binexpminus> BinExpMinus;
%type<binexplessthen> BinExpLessThen;
%type<binexpgreaterthen> BinExpGreaterThen;
%type<factormul> FactorMul;
%type<factordiv> FactorDiv;
%type<unexpplus> UnExpPlus;
%type<unexpminus> UnExpMinus;
%type<unexplog> UnExpLog;
%type<unexpexp> UnExpExp;
%type<lparexprpar> LparExpRpar;
%type<assignment> Assignment;
%type<ifelseif> IfElseIf;
%type<ift> If;
%type<ifelset> IfElse;
%type<wwhile> While;
%%

Program : ExpList{
		$$ = $1;
		Context::getContext().setProgram($$);
	}
;

ExpList : Command {$$ = $1;}
;

Command : Assignment {$$ = $1;}
		|IfElseIf {$$ = $1;}
		|While {$$ = $1;}
		|Exp {$$ = $1;}
;

Exp: BinExpLessGreater { $$ = $1; }
	|BinExpPlusMinus { $$ = $1; }
	|Factor {$$ = $1;}
;

BinExpLessGreater: BinExpLessThen {$$ = $1;}
				|BinExpGreaterThen {$$ = $1;}

BinExpPlusMinus: BinExpPlus {$$ = $1;}
				|BinExpMinus {$$ = $1;}
;

IfElseIf : If {$$ = $1;}
		|IfElse {$$ = $1;}
;

If : IF PAR_L Exp PAR_R BRA_L ExpList BRA_R {
		$$ = new If($3, $6);
	}
; 

IfElse : IF PAR_L Exp PAR_R BRA_L ExpList BRA_R ELSE BRA_L ExpList BRA_R {
		$$ = new IfElse($3,$6,$10);
	}
;

While : WHILE PAR_L Exp PAR_R BRA_L ExpList BRA_R {
		$$ = new While($3, $6);
	}
;

BinExpPlus : Exp ADD Factor {
		$$ = new BinExpPlus($1,$3);
	}
;  

BinExpMinus : Exp SUBTRACT Factor {
		$$ = new BinExpMinus($1, $3);
	}
;

BinExpLessThen : Exp LESS_THEN Factor {
		$$ = new BinExpLessThen($1, $3);
	} 
;

BinExpGreaterThen : Exp GREATER_THEN Factor {
		$$ = new BinExpGreaterThen($1, $3);
	} 
;

Factor : FactorMul { $$ = $1; }
		|FactorDiv { $$ = $1; }
		|UnExp { $$ = $1; }
;

FactorMul : Factor MUL UnExp{
		$$ = new FactorMul($1, $3);
	}
;		

FactorDiv : Factor DIV UnExp {
		$$ = new FactorDiv($1, $3);
	}
;

UnExp : UnExpPlus { $$ = $1; }
        |UnExpMinus { $$ = $1; }
		|UnExpLog { $$ = $1; }
		|UnExpExp { $$ = $1; }
		|LparExpRpar { $$ = $1; }
		|Value { $$ = $1; }
;

UnExpPlus : ADD Value{
		$$ = new UnExpPlus($2);	
	}
;

UnExpMinus : SUBTRACT Value{
		$$ = new UnExpMinus($2);
	}
;

UnExpLog : LOG2 PAR_L Exp PAR_R{
		$$ = new UnExpLog($3);
	}
;

UnExpExp : EXP PAR_L Exp PAR_R{
		$$ = new UnExpExp($3);
	}			
;

Value : LITERAL_INT {		
		$$ = new IntValue($1);
	}
		|LITERAL_DOUBLE{
		$$ = new DoubleValue($1);
	}
		|IDENTIFIER { $$ = new IdValue($1); }
;	

LparExpRpar : PAR_L Exp PAR_R {
		$$ = new LparExpRpar($2);
	}
; 

Assignment : IDENTIFIER EQUAL Exp DOT_COMMA {
		IdValue *fallenId = new IdValue($1);
		$$ = new Assignment(fallenId,$3);
	}
;