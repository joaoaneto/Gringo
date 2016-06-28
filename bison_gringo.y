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

%token MAIN;
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
%token DOUBLE_EQUAL;
%token DIFFERENT;
%token GREATER_THEN;
%token GREATER_EQUAL_THEN;
%token LESS_THEN;
%token LESS_EQUAL_THEN;
%token NOT;
%token XOR;
%token COMMA;
%token DOT;
%token TWO_DOTS;
%token SEMICOLON;
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
	int type;
	double double_value;
	char char_value;
	char *id_value;
	class Program *program;
	class StatementList *statementlist;
	class VarDeclarationList *vardeclarationlist;
	class FuncDefinitionList *funcdefinitionlist;
	class FuncDefinition *funcdefinition;
	class FuncDefinitions *funcdefinitions;
	class FunctionPar *funcPar;
	class FunctionCall *funcCall;
	class FunctionNonPar *funcNonPar;
	class VarDeclaration *vardeclaration;
	class VarDeclarations *vardeclarations;
	class ParameterList *parList;
	class Parameter *param;
	class Parameters *params;
	class Command *command;
	class Value *value;
	class Exp *exp;
	class Block *block;
	class BinExpEqualDiff *beed;
	class BinExpLessGreater *belg;
	class BinExpPlusMinus *bepm;
	class UnExp *unexp;
	class Factor *factor;
	class BinExpPlus *binexpplus;
	class BinExpMinus *binexpminus;
	class BinExpLessThen *binexplessthen;
	class BinExpLessEqualThen *belet;
	class BinExpGreaterThen *binexpgreaterthen;
	class BinExpGreaterEqualThen *beget;
	class BinExpEqual *binexpequal;
	class BinExpDiff *binexpdiff;
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
	class Commands *commandst;
	class CommandsList *commandslist;
	class IfElse *ifelset;
	class While *wwhile;
	class LValue *lvalue;
	class NameList *namelist;
	class Name *name;
	class Names *names;
	class NameID *nameID;
	class BlockVarCommands *blockVarCommands;
	class BlockCommands *blockCommands;
	class BlockVar *blockVar;
	class NameAssignment *nameAss;

};

%type<program> Program;
%type<parList> ParameterList;
%type<nameID> NameID;
%type<nameAss> NameAssignment;
%type<param> Parameter;
%type<params> Parameters;
%type<int_value> Type;
%type<statementlist> StatementList;
%type<vardeclarationlist> VarDeclarationList;
%type<funcdefinitionlist> FuncDefinitionList;
%type<funcdefinition> FuncDefinition;
%type<funcdefinitions> FuncDefinitions;
%type<funcPar> FunctionPar;
%type<funcNonPar> FunctionNonPar;
%type<funcCall> FunctionCall;
%type<vardeclaration> VarDeclaration;
%type<vardeclarations> VarDeclarations;
%type<command> Command;
%type<char_value> CHAR;
%type<int_value> LITERAL_INT;
%type<double_value> FLOAT;
%type<double_value> LITERAL_DOUBLE;
%type<id_value> IDENTIFIER;
%type<value> Value;
%type<exp> Exp;
%type<block> Block;
%type<blockVarCommands> BlockVarCommands;
%type<blockCommands> BlockCommands;
%type<blockVar> BlockVar;
%type<belg> BinExpLessGreater;
%type<bepm> BinExpPlusMinus;
%type<beed> BinExpEqualDiff;
%type<factor> Factor;
%type<unexp> UnExp;
%type<binexpequal> BinExpEqual;
%type<binexpdiff> BinExpDiff;
%type<binexpplus> BinExpPlus;
%type<binexpminus> BinExpMinus;
%type<binexplessthen> BinExpLessThen;
%type<belet> BinExpLessEqualThen;
%type<binexpgreaterthen> BinExpGreaterThen;
%type<beget> BinExpGreaterEqualThen;
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
%type<commandst> Commands;
%type<commandslist> CommandsList;
%type<ifelset> IfElse;
%type<wwhile> While;
%type<lvalue> LValue;
%type<namelist> NameList;
%type<name> Name;
%type<names> Names;
%%

Program : StatementList {
		$$ = $1;
		Context::getContext().setProgram($$);
		Context::getContext().setAtualScope(new Scope());
	}
;

Type : INT {}
	  |DOUBLE {}
	  |FLOAT {}
	  |VOID{}	
;

StatementList : VarDeclarationList {}
		  	  |FuncDefinitionList {}		
;

VarDeclarationList : VarDeclaration {}
					|VarDeclarations {}
;

VarDeclarations: VarDeclarationList VarDeclaration { $$ = new VarDeclarations($1, $2); }
;

VarDeclaration : Type NameList SEMICOLON { $$ = new VarDeclaration($1, $2); }
;

NameList : Name {}
		  |Names {}
;

Names: NameList COMMA Name { $$ = new Names($1, $3); }
;

Name : NameID  {}
	  |NameAssignment {}	
;

NameID : IDENTIFIER { $$ = new NameID (new IdValue($1)); }
;

NameAssignment : Assignment {$$ = new NameAssignment ($1); }
;

FuncDefinitionList : FuncDefinition {}
					|FuncDefinitions {}
;

FuncDefinitions: FuncDefinitionList FuncDefinition { $$ = new FuncDefinitions($1, $2); }
;

FuncDefinition : FunctionPar {}
				|FunctionNonPar {}
;	

FunctionPar : Type IDENTIFIER PAR_L ParameterList PAR_R Block { $$ = new FunctionPar($1, new IdFunction($2), $6); }
;

FunctionNonPar : Type IDENTIFIER PAR_L PAR_R Block { $$ = new FunctionNonPar($1, new IdFunction($2), $5); }

ParameterList : Parameter {}
				|Parameters {}
;

Parameters: ParameterList COMMA Parameter { $$ = new Parameters($1, $3); }
;

Parameter : Type IDENTIFIER { $$ = new Parameter(new IdValue($2), $1); }
;	 

Block : BlockVarCommands {}
	   |BlockCommands {}
	   |BlockVar {}
;

BlockVarCommands : BRA_L VarDeclarationList Commands BRA_R { $$ = new BlockVarCommands($2,$3); }
;

BlockCommands : BRA_L Commands BRA_R { $$ = new BlockCommands($2); }
;

BlockVar : BRA_L VarDeclarationList BRA_R { $$ = new BlockVar($2); }

Commands : Command {}
		  |CommandsList {}
;

CommandsList : Commands Command { $$ = new CommandsList($1,$2); }

Command : IfElseIf {}
		 |While {}
		 |Exp SEMICOLON {}
		 |FunctionCall SEMICOLON {}
;

FunctionCall : IDENTIFIER PAR_L PAR_R {	$$ = new FunctionCall(new IdFunction($1)); }
;

IfElseIf : If {$$ = $1;}
		  |IfElse {$$ = $1;}
;

If : IF PAR_L Exp PAR_R Block { $$ = new If($3, $5); }
; 

IfElse : IF PAR_L Exp PAR_R Block ELSE Block { $$ = new IfElse($3,$5,$7); }
;

While : WHILE PAR_L Exp PAR_R Block { $$ = new While($3, $5); }
;

Exp: LValue {$$ = $1;}
	|Assignment {$$ = $1;}
;

LValue: BinExpEqualDiff { $$ = $1; }
	   |BinExpLessGreater { $$ = $1; }
	   |BinExpPlusMinus { $$ = $1; }
	   |Factor { $$ = $1; }
;	

BinExpEqualDiff: BinExpEqual { $$ = $1; }
				|BinExpDiff { $$ = $1; }
;

BinExpLessGreater: BinExpLessThen { $$ = $1; }
				  |BinExpLessEqualThen { $$ = $1; }
				  |BinExpGreaterThen { $$ = $1; }
				  |BinExpGreaterEqualThen { $$ = $1; }
;

BinExpPlusMinus: BinExpPlus { $$ = $1; }
				|BinExpMinus { $$ = $1; }
;

BinExpPlus : LValue ADD Factor { $$ = new BinExpPlus($1,$3); }
;  

BinExpMinus : LValue SUBTRACT Factor {
		$$ = new BinExpMinus($1, $3);
	}
;

BinExpLessThen : LValue LESS_THEN Factor {
		$$ = new BinExpLessThen($1, $3);
	} 
;

BinExpLessEqualThen : LValue LESS_EQUAL_THEN Factor {
		$$ = new BinExpLessEqualThen($1, $3);
	} 
;

BinExpGreaterThen : LValue GREATER_THEN Factor {
		$$ = new BinExpGreaterThen($1, $3);
	} 
;

BinExpGreaterEqualThen : LValue GREATER_EQUAL_THEN Factor {
		$$ = new BinExpGreaterEqualThen($1, $3);
	} 
;

BinExpEqual: LValue DOUBLE_EQUAL Factor {
		$$ = new BinExpEqual($1, $3);
	}
;

BinExpDiff: LValue DIFFERENT Factor {
		$$ = new BinExpDiff($1, $3);
	}
;

Factor : FactorMul { $$ = $1; }
		|FactorDiv { $$ = $1; }
		|UnExp { $$ = $1; }
;

FactorMul : Factor MUL UnExp {
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

Assignment : IDENTIFIER EQUAL Exp {
		$$ = new Assignment(new IdValue(string($1)),$3);
	}
;
