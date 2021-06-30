/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    OR = 267,
    NOT = 268,
    LOCAL = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    NOT_EQUALS = 273,
    EQUALS = 274,
    ASSIGN = 275,
    PLUS_PLUS = 276,
    MINUS_MINUS = 277,
    PLUS = 278,
    MINUS = 279,
    MULTI = 280,
    DIV = 281,
    MOD = 282,
    GREATER_OR_EQUAL = 283,
    LESS_OR_EQUAL = 284,
    GREATER_THAN = 285,
    LESS_THAN = 286,
    LEFT_CURLY = 287,
    RIGHT_CURLY = 288,
    LEFT_BRACKET = 289,
    RIGHT_BRACKET = 290,
    LEFT_PARENTHESIS = 291,
    RIGHT_PARENTHESIS = 292,
    SEMICOLON = 293,
    COMMA = 294,
    COLON = 295,
    SCOPE = 296,
    DOT = 297,
    DOUBLE_DOT = 298,
    SPACE = 299,
    LINE_COMMENT = 300,
    BLOCK_COMMENT_START = 301,
    BLOCK_COMMENT_END = 302,
    NEWLINE = 303,
    TAB = 304,
    INTCONST = 305,
    REALCONST = 306,
    STRING = 307,
    ID = 308,
    UMINUS = 309,
    LOWER_THAN_ELSE = 310
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define OR 267
#define NOT 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define NOT_EQUALS 273
#define EQUALS 274
#define ASSIGN 275
#define PLUS_PLUS 276
#define MINUS_MINUS 277
#define PLUS 278
#define MINUS 279
#define MULTI 280
#define DIV 281
#define MOD 282
#define GREATER_OR_EQUAL 283
#define LESS_OR_EQUAL 284
#define GREATER_THAN 285
#define LESS_THAN 286
#define LEFT_CURLY 287
#define RIGHT_CURLY 288
#define LEFT_BRACKET 289
#define RIGHT_BRACKET 290
#define LEFT_PARENTHESIS 291
#define RIGHT_PARENTHESIS 292
#define SEMICOLON 293
#define COMMA 294
#define COLON 295
#define SCOPE 296
#define DOT 297
#define DOUBLE_DOT 298
#define SPACE 299
#define LINE_COMMENT 300
#define BLOCK_COMMENT_START 301
#define BLOCK_COMMENT_END 302
#define NEWLINE 303
#define TAB 304
#define INTCONST 305
#define REALCONST 306
#define STRING 307
#define ID 308
#define UMINUS 309
#define LOWER_THAN_ELSE 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 36 "parser.y" /* yacc.c:1909  */

    int intNum;
    double doubleNum;
    char* id;
    struct stmt_t *stmt_tt;
    struct expr* expression;
    struct forstruct* forpref;
    struct call_t* s_call;
    struct SymbolTableEntry * symbol;

#line 175 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
