/*

	Analisador Sintático do GRINGO (Linguagem C)
	Parser of GRINGO (C Language)
*/

%{

	void yyerror(const char *isso) {printf("%s\n", isso);}
	using namespace std;

	extern int yylex();

%}

%token CHAR;
%token INT;
%token FLOAT;
%token DOUBLE;
%token VOID;
%token UNSIGNED;
%token SIGNED;
%token SHORT;
%token LONG;
%token CONST;
%token VOLATILE;
%token EXTERN;
%token STATIC;
%token REGISTER;
%token AUTO;
%token SIZEOF;
%token EQUAL;
%token SUBTRACT;
%token ADD;
%token MUL;
%token DIV;
%token REST;
%token GREATER_THEN;
%token LESS_THEN;
%token NOT;
%token ECOMM;
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
%token NULL;
%token IDENTIFIER;
%token LITERAL_INT;
%token LITERAL_DOUBLE;
%token HEXADECIMAL;
%token OCTAL;
%token NEW_LINE;
%token CARRIAGE_RETURN;
%token TAB;
%token BACKSLASH;
%token BAR_ZERO;

%%
