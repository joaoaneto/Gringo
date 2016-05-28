/*

	Analisador Sintático do GRINGO (Linguagem C)
	Parser of GRINGO (C Language)
*/

%{

	#include "visitor.hpp"

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
	class UnExp *unexp;
	class Factor *factor;
	class BinExpPlus *binexpplus;
	class BinExpMinus *binexpminus;
	class FactorMul *factormul;
	class FactorDiv *factordiv;
	class UnExpPlus *unexpplus;
	class UnExpMinus *unexpminus;
	class UnExpLog *unexplog;
	class UnExpExp *unexpexp;
};

%type<char_value> CHAR;
%type<int_value> LITERAL_INT;
%type<double_value> FLOAT;
%type<double_value> LITERAL_DOUBLE;
%type<value> Value;
%type<exp> Exp;
%type<factor> Factor;
%type<unexp> UnExp;
%type<binexpplus> BinExpPlus;
%type<binexpminus> BinExpMinus;
%type<factormul> FactorMul;
%type<factordiv> FactorDiv;
%type<unexpplus> UnExpPlus;
%type<unexpminus> UnExpMinus;
%type<unexplog> UnExpLog;
%type<unexpexp> UnExpExp;

%%

 

Program : ExpList
;

ExpList : Command {

		Value *total = op->getTotal();

		if(total->getType() == Value::INT){
			printf("%d\n\n", static_cast <IntValue*> (total)->getValue());
		} else if(total->getType() == Value::DOUBLE){
			printf("%lf\n\n", static_cast <DoubleValue*> (total)->getValue());
		}
	}
		|Commands{}
; 

Commands : ExpList NEW_LINE Command {} //Só uma produção complexa

Command : Atribuition //Relação "é"
		|Exp
;

Exp : BinExpPlus{}
	 |BinExpMinus {}
	 |Factor{}
;

BinExpPlus : Exp ADD Factor {
		BinExpPlus *fallen = new BinExpPlus($1,$3);
		fallen->accept(op);
		$$ = new BinExpPlus($1,$3);
	}
;  

BinExpMinus : Exp SUBTRACT Factor {
		BinExpMinus *fallen = new BinExpMinus($1, $3);
		fallen->accept(op);
		$$ = new BinExpMinus($1, $3);
	}
;
  
Factor : FactorMul{}
		|FactorDiv{}
		|UnExp{}
;

FactorMul : Factor MUL UnExp{
		FactorMul *fallen = new FactorMul($1, $3);
		fallen->accept(op);
		$$ = new FactorMul($1, $3);
	}
;		

FactorDiv : Factor DIV UnExp {
		FactorDiv *fallen = new FactorDiv($1, $3);
		fallen->accept(op);
		$$ = new FactorDiv($1, $3);
	}
;

UnExp : UnExpPlus{}     
        |UnExpMinus{}
		|UnExpLog{}
		|UnExpExp{}
		|Value{}
;

UnExpPlus : ADD Value{
		UnExpPlus *fallen = new UnExpPlus($2);
		fallen->accept(op);
		$$ = new UnExpPlus($2);	
	}
;

UnExpMinus : SUBTRACT Value{
		UnExpMinus *fallen = new UnExpMinus($2);
		fallen->accept(op);
		$$ = new UnExpMinus($2);
	}
;

UnExpLog : LOG2 PAR_L Exp PAR_R{
		UnExpLog *fallen = new UnExpLog($3);
		fallen->accept(op);
		$$ = new UnExpLog($3);
	}
;

UnExpExp : EXP PAR_L Exp PAR_R{
		UnExpExp *fallen = new UnExpExp($3);
		fallen->accept(op);
		$$ = new UnExpExp($3);
	}			
;

Value : LITERAL_INT {
			/*IntValue *fallen = new IntValue($1);
			fallen->accept(op);*/
			$$ = new IntValue($1);
	}
		|LITERAL_DOUBLE{
			/*DoubleValue *fallen = new DoubleValue($1);
			fallen->accept(op);*/
			$$ = new DoubleValue($1);
	}
		|LparExpRpar{}
		|IDENTIFIER {
			//$$ = new IdValue($1);
	}
;	

LparExpRpar : PAR_L Exp PAR_R{}
; 

Atribuition : IDENTIFIER EQUAL Exp{}
;
