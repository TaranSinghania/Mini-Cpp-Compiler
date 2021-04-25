/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    T_MAIN = 258,
    T_INT = 259,
    T_FLOAT = 260,
    T_DOUBLE = 261,
    T_CHAR = 262,
    T_VOID = 263,
    T_Terminator = 264,
    T_INC = 265,
    T_DEC = 266,
    T_EQ = 267,
    T_NE = 268,
    T_GT = 269,
    T_LT = 270,
    T_GTE = 271,
    T_LTE = 272,
    T_AND = 273,
    T_OR = 274,
    T_NOT = 275,
    T_BAND = 276,
    T_BOR = 277,
    T_BXOR = 278,
    T_ADDEQ = 279,
    T_MULEQ = 280,
    T_DIVEQ = 281,
    T_MODEQ = 282,
    T_LSEQ = 283,
    T_RSEQ = 284,
    T_ANDEQ = 285,
    T_XOREQ = 286,
    T_OREQ = 287,
    T_H = 288,
    T_B = 289,
    T_OB = 290,
    T_SB = 291,
    T_CSB = 292,
    T_OSB = 293,
    T_CB = 294,
    T_OCB = 295,
    T_ID = 296,
    T_ENDL = 297,
    T_CIN = 298,
    T_COUT = 299,
    T_RETURN = 300,
    T_FOR = 301,
    T_IF = 302,
    T_ELSE = 303,
    T_OUT = 304,
    T_IN = 305,
    T_NUM = 306,
    T_SUBEQ = 307,
    T_COMMA = 308,
    T_BREAK = 309,
    T_CONTINUE = 310,
    T_OFB = 311,
    T_CFB = 312,
    T_VMAIN = 313,
    T_STR = 314,
    T_STRING = 315,
    T_STRIN = 316,
    T_STROUT = 317,
    T_DEQ = 318,
    T_INCLUDE = 319,
    T_TRUE = 320,
    T_FALSE = 321,
    T_CLASS = 322,
    T_PUBLIC = 323,
    T_PRIVATE = 324,
    T_PROTECTED = 325,
    T_ARRAY = 326,
    T_ADD = 327,
    T_SUB = 328,
    T_MUL = 329,
    T_DIV = 330
  };
#endif
/* Tokens.  */
#define T_MAIN 258
#define T_INT 259
#define T_FLOAT 260
#define T_DOUBLE 261
#define T_CHAR 262
#define T_VOID 263
#define T_Terminator 264
#define T_INC 265
#define T_DEC 266
#define T_EQ 267
#define T_NE 268
#define T_GT 269
#define T_LT 270
#define T_GTE 271
#define T_LTE 272
#define T_AND 273
#define T_OR 274
#define T_NOT 275
#define T_BAND 276
#define T_BOR 277
#define T_BXOR 278
#define T_ADDEQ 279
#define T_MULEQ 280
#define T_DIVEQ 281
#define T_MODEQ 282
#define T_LSEQ 283
#define T_RSEQ 284
#define T_ANDEQ 285
#define T_XOREQ 286
#define T_OREQ 287
#define T_H 288
#define T_B 289
#define T_OB 290
#define T_SB 291
#define T_CSB 292
#define T_OSB 293
#define T_CB 294
#define T_OCB 295
#define T_ID 296
#define T_ENDL 297
#define T_CIN 298
#define T_COUT 299
#define T_RETURN 300
#define T_FOR 301
#define T_IF 302
#define T_ELSE 303
#define T_OUT 304
#define T_IN 305
#define T_NUM 306
#define T_SUBEQ 307
#define T_COMMA 308
#define T_BREAK 309
#define T_CONTINUE 310
#define T_OFB 311
#define T_CFB 312
#define T_VMAIN 313
#define T_STR 314
#define T_STRING 315
#define T_STRIN 316
#define T_STROUT 317
#define T_DEQ 318
#define T_INCLUDE 319
#define T_TRUE 320
#define T_FALSE 321
#define T_CLASS 322
#define T_PUBLIC 323
#define T_PRIVATE 324
#define T_PROTECTED 325
#define T_ARRAY 326
#define T_ADD 327
#define T_SUB 328
#define T_MUL 329
#define T_DIV 330

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
