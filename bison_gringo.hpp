/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_GRINGO_HPP_INCLUDED
# define YY_YY_BISON_GRINGO_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    LOG2 = 259,
    EXP = 260,
    INT = 261,
    FLOAT = 262,
    DOUBLE = 263,
    VOID = 264,
    UNSIGNED = 265,
    CONST = 266,
    STATIC = 267,
    SIZEOF = 268,
    EQUAL = 269,
    SUBTRACT = 270,
    DOC_PARAM = 271,
    ADD = 272,
    MUL = 273,
    DIV = 274,
    REST = 275,
    GREATER_THEN = 276,
    LESS_THEN = 277,
    NOT = 278,
    XOR = 279,
    COMMA = 280,
    DOT = 281,
    TWO_DOTS = 282,
    DOT_COMMA = 283,
    PAR_L = 284,
    PAR_R = 285,
    COL_L = 286,
    COL_R = 287,
    BRA_L = 288,
    BRA_R = 289,
    QUOTE = 290,
    DOUBLE_QUOTE = 291,
    IF = 292,
    ELSE = 293,
    BREAK = 294,
    FOR = 295,
    WHILE = 296,
    RETURN = 297,
    EXIT = 298,
    CONTINUE = 299,
    IDENTIFIER = 300,
    LITERAL_INT = 301,
    LITERAL_DOUBLE = 302,
    NEW_LINE = 303,
    CARRIAGE_RETURN = 304,
    TAB = 305,
    BACKSLASH = 306,
    BAR_ZERO = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 73 "bison_gringo.y" /* yacc.c:1909  */

	int int_value;
	double double_value;
	char char_value;
	class Value *value;
	class Exp *exp;
	class Factor *factor;
	class BinExpPlus *binexpplus;

#line 117 "bison_gringo.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_GRINGO_HPP_INCLUDED  */
