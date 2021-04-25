/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE char *
int yylex();
void if1();
void if2();
void if3();
void for1();
void for2();
void for3();
void for4();
void codegen();
void codegen_assign();
void codegen_arraytemp();
void codegen_arrayassign();
void codegen_syns();
void codgen_un();
void showSt();
void codegen_call();
void codegen_param();
void codegen_return();
void yyerror(const char *s);


typedef struct quadruples{
    char op[100];
    char arg1[20];
    char arg2[20];
    char res[20];
    struct quadruples *next;
} quad;
quad *quad_head=NULL;
quad *quad_tail=NULL;

void insert_quad(char *op,char *arg1,char *arg2,char *res)
{
    quad *new=(quad *)malloc(sizeof(quad));
    strcpy(new->op,op);
    if(arg1!=NULL)
        strcpy(new->arg1,arg1);
    //new->arg2=NULL;
    if(arg2!=NULL)
        strcpy(new->arg2,arg2);
    if(res!=NULL)
        strcpy(new->res,res);
    new->next=NULL;
    if(quad_head==NULL)
    {
        quad_head=new;
        quad_tail=quad_head;
    }
    else
    {
        quad_tail->next=new;
        quad_tail=quad_tail->next;
    }
}

void display_quad()
{
    quad *temp1;
    temp1=quad_head;
    printf("Quadruple table:\n");
    printf("opeator arg1\targ2\tresult\n");
    while(temp1!=NULL)
    {
        printf("%s\t%s\t%s\t%s\n ",temp1->op,temp1->arg1,temp1->arg2,temp1->res);
        temp1=temp1->next;
    }
}


typedef struct node{
      int scope;
      char value[1000];
      char name[100];
      char dtype[50];
      int line_num;
      int valid;
}node;

typedef struct table{
      node* head;
}table;
// int count = 0;
extern node symTable[1000];

void push();
int sym[26];
extern int yylineno;
int valid=1;
extern int SymTable[100];


extern int scope;
extern int count;
extern void displaySymTable();
extern int find(int  scope, char *yytext);
extern void update(char* name, char* value, int scope);
extern int insert(int* idx, int scope, char* dtype, char* val, int line_num);
extern void decrScope();
extern void incrScope();
extern char tdType[50];
extern char op[50];
char val[50];
int val1, val2;
int val1i, val2i;
float val1f, val2f;
char ddtype[50];
char set[4];
int flag = 0;
int top = 0;


#line 187 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  296

#define YYUNDEFTOK  2
#define YYMAXUTOK   330


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   125,   125,   128,   129,   132,   133,   136,   137,   138,
     139,   140,   143,   144,   145,   146,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   177,
     177,   177,   177,   180,   181,   185,   188,   196,   205,   215,
     223,   226,   226,   229,   229,   230,   230,   231,   231,   231,
     232,   236,   237,   238,   239,   240,   244,   245,   246,   247,
     248,   249,   253,   253,   253,   261,   261,   268,   269,   272,
     273,   274,   275,   276,   280,   290,   298,   298,   298,   306,
     310,   310,   436,   436,   436,   465,   465,   465,   493,   496,
     496,   496,   523,   523,   523,   552,   554,   574,   588,   589,
     592,   593,   596,   596,   596,   596,   599,   600,   601,   602,
     605,   608,   627,   671,   672,   672,   776,   819,   862,   869,
     875,   878,   879,   880,   883,   883,   883,   886,   887,   890,
     890,   891,   891,   892,   892,   893,   894,   895,   901,   925,
     949,   973,   999,  1000,  1003,  1004,  1005,  1008,  1009,  1010,
    1011,  1012,  1013,  1016,  1017,  1018,  1019,  1020,  1021,  1022,
    1023,  1026,  1027
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_MAIN", "T_INT", "T_FLOAT", "T_DOUBLE",
  "T_CHAR", "T_VOID", "T_Terminator", "T_INC", "T_DEC", "T_EQ", "T_NE",
  "T_GT", "T_LT", "T_GTE", "T_LTE", "T_AND", "T_OR", "T_NOT", "T_BAND",
  "T_BOR", "T_BXOR", "T_ADDEQ", "T_MULEQ", "T_DIVEQ", "T_MODEQ", "T_LSEQ",
  "T_RSEQ", "T_ANDEQ", "T_XOREQ", "T_OREQ", "T_H", "T_B", "T_OB", "T_SB",
  "T_CSB", "T_OSB", "T_CB", "T_OCB", "T_ID", "T_ENDL", "T_CIN", "T_COUT",
  "T_RETURN", "T_FOR", "T_IF", "T_ELSE", "T_OUT", "T_IN", "T_NUM",
  "T_SUBEQ", "T_COMMA", "T_BREAK", "T_CONTINUE", "T_OFB", "T_CFB",
  "T_VMAIN", "T_STR", "T_STRING", "T_STRIN", "T_STROUT", "T_DEQ",
  "T_INCLUDE", "T_TRUE", "T_FALSE", "T_CLASS", "T_PUBLIC", "T_PRIVATE",
  "T_PROTECTED", "T_ARRAY", "T_ADD", "T_SUB", "T_MUL", "T_DIV", "$accept",
  "S", "START", "Prog", "BODY", "CLASS_STMT", "STMT", "ARRAYASSGN", "$@1",
  "$@2", "$@3", "VALUE", "FUNC", "PARAMLIST", "FUNCALL", "$@4",
  "F_PARAMLIST", "$@5", "$@6", "$@7", "$@8", "INOUT", "TYPE", "DECL",
  "$@9", "$@10", "$@11", "ARRELE", "VARLIST", "$@12", "$@13",
  "ASSIGN_EXPR", "$@14", "E", "$@15", "$@16", "$@17", "$@18", "T", "$@19",
  "$@20", "$@21", "$@22", "F", "FORSTMT", "$@23", "$@24", "$@25",
  "INITFOR", "COND", "OPERATION", "@26", "ITRCHANGE", "SELECTSTMT", "$@27",
  "$@28", "ELSEBODY", "JUMPSTMT", "$@29", "$@30", "$@31", "UNARYEXP",
  "LOGICOP", "BITOP", "RELOP", "ASSIGNOP", "BOOL", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330
};
# endif

#define YYPACT_NINF (-201)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-115)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     196,   -38,  -201,  -201,  -201,  -201,  -201,    -6,  -201,   230,
      12,    72,  -201,  -201,  -201,   230,   -29,   230,   348,   348,
    -201,    27,  -201,  -201,    48,    31,    46,  -201,    51,    77,
      26,     5,    93,    95,    55,    55,   103,   139,   348,    98,
     348,   348,   348,   348,   348,   348,   348,   348,   166,   119,
      18,   117,   323,   168,   -24,  -201,   125,  -201,  -201,  -201,
    -201,   147,   152,   359,  -201,  -201,  -201,  -201,   358,   274,
     148,    81,   181,   182,  -201,  -201,   136,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,   348,  -201,   348,   348,
     348,   140,   262,   170,   164,   251,  -201,   171,   198,    53,
      40,    41,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
     251,   208,   210,   211,  -201,   212,   -26,  -201,  -201,  -201,
     285,   251,   132,  -201,  -201,  -201,  -201,   260,    71,  -201,
     183,  -201,  -201,  -201,  -201,    55,    55,    55,   348,   348,
     348,  -201,    18,    18,    18,   230,   213,   185,   173,   245,
      89,     7,  -201,   174,   177,   188,  -201,  -201,  -201,  -201,
     190,   200,     2,  -201,  -201,  -201,  -201,   235,   274,   251,
     123,    -5,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,   176,   186,   251,   251,   251,   184,   189,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,   251,   323,   348,   251,  -201,   -24,  -201,   244,    53,
      53,   256,   243,    41,   275,   282,  -201,   284,   143,   251,
    -201,  -201,  -201,    89,    89,    33,  -201,  -201,   249,    94,
    -201,   242,    94,   292,   251,  -201,  -201,  -201,   294,  -201,
      41,   295,  -201,  -201,   251,    89,   251,   251,   145,   251,
     251,   348,  -201,  -201,  -201,  -201,    89,    40,  -201,   251,
      66,     0,    71,    71,   251,  -201,  -201,   253,   -24,  -201,
      89,   132,  -201,  -201,  -201,  -201,   227,  -201,  -201,   299,
      41,   273,   251,   265,  -201,  -201,   258,    89,   263,  -201,
     348,   348,   261,   267,  -201,  -201
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,    56,    57,    59,    58,    60,     0,    61,    11,
       0,     0,     2,     4,     6,    11,     0,    11,    28,    28,
       3,     0,     1,    10,     0,    65,     0,     5,     0,     0,
      80,     0,     0,     0,    55,    55,     0,     0,    28,     0,
      28,    28,    28,    28,    28,    28,    28,    28,     0,     0,
      15,     0,    40,     0,    79,    67,     0,   138,   140,   139,
     141,     0,     0,     0,   135,   129,   131,   133,     0,   120,
       0,     0,     0,     0,   137,   136,     0,     7,    27,    25,
      26,    16,    17,    20,    21,    22,    28,     8,    28,    28,
      28,     0,     0,     0,     0,     0,    75,     0,     0,    73,
       0,    50,   153,   154,   155,   156,   157,   158,   159,   160,
       0,     0,     0,     0,   109,    80,     0,   108,   107,   102,
       0,     0,    96,    97,   101,   161,   162,   119,    88,    95,
       0,   110,   100,    99,    51,    55,    55,    55,    28,    28,
      28,    24,    15,    15,    15,    11,     0,     0,     0,    40,
      63,    76,    66,    71,    72,     0,    33,    34,    30,    45,
       0,     0,    82,   130,   132,   134,   106,    65,   120,     0,
     118,    82,   152,   149,   148,   150,   151,   143,   142,   144,
     145,   146,   147,     0,     0,     0,     0,     0,     0,     0,
     124,    52,    53,    54,    19,    18,    23,    12,    13,    14,
       9,     0,    40,    28,     0,    36,    79,    74,     0,    73,
      73,     0,     0,    50,    43,     0,    81,     0,    82,     0,
      98,    83,    86,   111,   113,   112,    90,    93,     0,    40,
      39,     0,    40,     0,     0,    69,    70,    68,     0,    46,
      50,     0,    42,   103,     0,   117,     0,     0,     0,     0,
       0,    28,    38,    35,    37,    64,    77,     0,    44,     0,
     123,    82,    84,    87,     0,    91,    94,     0,    79,    31,
      48,    80,   122,   104,   121,   116,    82,   125,    78,     0,
      50,     0,     0,   128,    32,    49,     0,   115,     0,   126,
      28,    28,     0,     0,   105,   127
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,   313,   -11,   -17,   -19,  -201,  -201,  -201,
    -201,    78,    32,  -139,  -201,  -201,  -200,  -201,  -201,  -201,
    -201,   -27,   -14,    35,  -201,  -201,  -201,   -39,  -144,  -201,
    -201,   -66,  -201,   -90,  -201,  -201,  -201,  -201,   -74,  -201,
    -201,  -201,  -201,   -71,  -201,  -201,  -201,  -201,  -201,   169,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,   -36,    90,  -201,  -161,  -201,  -201
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    91,    39,    40,    61,   212,
     279,   158,    41,    93,    42,    62,   161,   240,   213,   241,
     280,    72,    16,    43,    53,   206,    54,   155,    98,   208,
     268,    44,    63,   127,   183,   246,   184,   247,   128,   188,
     249,   189,   250,   129,    45,   168,   260,   281,   119,   130,
     131,   248,   273,    46,   228,   283,   289,    47,   111,   112,
     113,    48,   185,   186,   187,   110,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    24,   118,    24,    23,   150,    27,   207,    73,   219,
     205,   216,    25,   239,    64,   167,   -79,    96,    18,    76,
     162,    78,    79,    80,    81,    82,    83,    84,    85,    97,
     170,   171,    15,   132,   220,    17,    59,    60,    94,   275,
     258,    15,    26,   -62,    17,    26,    65,    15,    96,    15,
      19,  -114,  -114,    21,   116,    55,    66,   244,    56,   132,
      97,   -41,   233,   230,   -29,    67,    52,   141,   -85,   142,
     143,   144,    22,   -85,   132,   -85,    28,    29,   147,   218,
     285,   156,   159,    50,   132,   132,    88,    89,    90,    51,
     252,   157,    57,   254,   160,   223,   224,   225,     2,     3,
       4,     5,     6,   117,   153,   -82,   -85,   271,   191,   192,
     193,   229,    74,   154,   232,   282,    70,    71,    58,   194,
     195,   196,   135,   136,   278,   197,   198,   199,    68,   245,
      69,    24,   132,   132,   200,    94,   172,   173,   174,   175,
     176,   137,    59,    60,   256,   -89,   -92,    92,    75,   132,
     132,   132,    52,     8,   261,    77,   172,   173,   174,   175,
     176,   -82,   -85,   177,   178,   132,   -82,   -85,   132,   270,
     235,   236,   262,   263,   276,    86,    87,    15,   265,   266,
      95,    99,   220,   132,   231,   100,   182,   101,    94,   134,
     138,   139,   287,   140,   272,   -82,   -85,   145,   132,     1,
       2,     3,     4,     5,     6,   149,   182,   152,   132,   148,
     132,   132,   151,   132,   132,    94,   -85,   163,    94,   164,
     165,   166,   190,   132,   274,   201,   202,   209,   132,   203,
     210,   214,   267,     1,     2,     3,     4,     5,     6,   215,
     172,   173,   174,   175,   176,   211,   132,   -62,   221,     2,
       3,     4,     5,     6,     7,     8,   234,   204,   226,   222,
       9,    28,    29,    10,   227,   237,     2,     3,     4,     5,
       6,   292,   293,   172,   173,   174,   175,   176,   177,   178,
     238,   179,   180,   181,    28,    29,   121,   -47,     7,     8,
     182,   242,   122,   243,   120,    28,    29,    10,    92,   253,
     -85,   255,   123,   146,     8,   251,   257,   259,   284,   121,
     277,   124,   286,   288,   290,   122,   125,   126,   294,   291,
     169,     8,    20,   182,   295,   123,   122,     2,     3,     4,
       5,     6,   -82,   -85,   124,   269,   123,   217,   264,   125,
     126,     0,     0,     0,     0,   124,     0,     0,     0,     0,
     125,   126,     2,     3,     4,     5,     6,     0,    28,    29,
       0,     0,     2,     3,     4,     5,     6,   114,     0,     0,
       0,   102,     0,     0,     0,     0,    92,     0,     0,     0,
       0,     0,     8,   103,   104,   105,   106,   107,   108,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,   115,
       0,     0,    36,    37,    38,     0,     0,     8,     0,     0,
       0,   109,     0,     0,     0,     0,     0,     8
};

static const yytype_int16 yycheck[] =
{
      19,    15,    68,    17,    15,    95,    17,   151,    35,   170,
     149,     9,    41,   213,     9,    41,     9,    41,    56,    38,
     110,    40,    41,    42,    43,    44,    45,    46,    47,    53,
     120,   121,     0,    69,    39,     0,    10,    11,    52,    39,
     240,     9,    71,    12,     9,    71,    41,    15,    41,    17,
      56,    18,    19,    41,    68,     9,    51,   218,    12,    95,
      53,    35,   206,   202,    38,    60,    35,    86,    73,    88,
      89,    90,     0,    73,   110,    73,    10,    11,    92,   169,
     280,    41,    41,    56,   120,   121,    68,    69,    70,    41,
     229,    51,    41,   232,    53,   185,   186,   187,     4,     5,
       6,     7,     8,    68,    51,    72,    73,    41,   135,   136,
     137,   201,     9,    60,   204,   276,    61,    62,    41,   138,
     139,   140,    41,    42,   268,   142,   143,   144,    35,   219,
      35,   145,   168,   169,   145,   149,    13,    14,    15,    16,
      17,    60,    10,    11,   234,    74,    75,    53,     9,   185,
     186,   187,    35,    59,   244,    57,    13,    14,    15,    16,
      17,    72,    73,    18,    19,   201,    72,    73,   204,   259,
     209,   210,   246,   247,   264,     9,    57,   145,   249,   250,
      12,    56,    39,   219,   203,    38,    63,    35,   202,    41,
       9,     9,   282,    57,   260,    72,    73,    57,   234,     3,
       4,     5,     6,     7,     8,    41,    63,     9,   244,    39,
     246,   247,    41,   249,   250,   229,    73,     9,   232,     9,
       9,     9,    39,   259,   260,    12,    41,    53,   264,    56,
      53,    41,   251,     3,     4,     5,     6,     7,     8,    39,
      13,    14,    15,    16,    17,    57,   282,    12,    72,     4,
       5,     6,     7,     8,    58,    59,    12,    12,    74,    73,
      64,    10,    11,    67,    75,     9,     4,     5,     6,     7,
       8,   290,   291,    13,    14,    15,    16,    17,    18,    19,
      37,    21,    22,    23,    10,    11,    35,    12,    58,    59,
      63,     9,    41,     9,    20,    10,    11,    67,    53,    57,
      73,     9,    51,    41,    59,    56,    12,    12,     9,    35,
      57,    60,    39,    48,    56,    41,    65,    66,    57,    56,
      35,    59,     9,    63,    57,    51,    41,     4,     5,     6,
       7,     8,    72,    73,    60,   257,    51,   168,   248,    65,
      66,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      65,    66,     4,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    59,    24,    25,    26,    27,    28,    29,    41,
      -1,    -1,    -1,    45,    46,    47,    -1,    49,    50,    41,
      -1,    -1,    54,    55,    56,    -1,    -1,    59,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    58,    59,    64,
      67,    77,    78,    79,    80,    88,    98,    99,    56,    56,
      79,    41,     0,    80,    98,    41,    71,    80,    10,    11,
      41,    45,    46,    47,    49,    50,    54,    55,    56,    82,
      83,    88,    90,    99,   107,   120,   129,   133,   137,    82,
      56,    41,    35,   100,   102,     9,    12,    41,    41,    10,
      11,    84,    91,   108,     9,    41,    51,    60,    35,    35,
      61,    62,    97,    97,     9,     9,    82,    57,    82,    82,
      82,    82,    82,    82,    82,    82,     9,    57,    68,    69,
      70,    81,    53,    89,    98,    12,    41,    53,   104,    56,
      38,    35,    12,    24,    25,    26,    27,    28,    29,    52,
     141,   134,   135,   136,     9,    41,    98,    99,   107,   124,
      20,    35,    41,    51,    60,    65,    66,   109,   114,   119,
     125,   126,   137,   142,    41,    41,    42,    60,     9,     9,
      57,    82,    82,    82,    82,    57,    41,    98,    39,    41,
     109,    41,     9,    51,    60,   103,    41,    51,    87,    41,
      53,    92,   109,     9,     9,     9,     9,    41,   121,    35,
     109,   109,    13,    14,    15,    16,    17,    18,    19,    21,
      22,    23,    63,   110,   112,   138,   139,   140,   115,   117,
      39,    97,    97,    97,    82,    82,    82,    81,    81,    81,
      80,    12,    41,    56,    12,    89,   101,   104,   105,    53,
      53,    57,    85,    94,    41,    39,     9,   125,   109,   140,
      39,    72,    73,   109,   109,   109,    74,    75,   130,   109,
      89,    82,   109,   104,    12,   103,   103,     9,    37,    92,
      93,    95,     9,     9,   140,   109,   111,   113,   127,   116,
     118,    56,    89,    57,    89,     9,   109,    12,    92,    12,
     122,   109,   114,   114,   138,   119,   119,    82,   106,    87,
     109,    41,   107,   128,   137,    39,   109,    57,   104,    86,
      96,   123,   140,   131,     9,    92,    39,   109,    48,   132,
      56,    56,    82,    82,    57,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    84,
      85,    86,    83,    87,    87,    88,    89,    89,    89,    89,
      89,    91,    90,    93,    92,    94,    92,    95,    96,    92,
      92,    97,    97,    97,    97,    97,    98,    98,    98,    98,
      98,    98,   100,   101,    99,   102,    99,    99,    99,   103,
     103,   103,   103,   103,   104,   104,   105,   106,   104,   104,
     108,   107,   110,   111,   109,   112,   113,   109,   109,   115,
     116,   114,   117,   118,   114,   114,   119,   119,   119,   119,
     119,   119,   121,   122,   123,   120,   124,   124,   124,   124,
     125,   126,   126,   126,   127,   126,   126,   126,   126,   126,
     126,   128,   128,   128,   130,   131,   129,   132,   132,   134,
     133,   135,   133,   136,   133,   133,   133,   133,   137,   137,
     137,   137,   138,   138,   139,   139,   139,   140,   140,   140,
     140,   140,   140,   141,   141,   141,   141,   141,   141,   141,
     141,   142,   142
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     4,     4,     6,
       2,     0,     3,     3,     3,     0,     2,     2,     4,     4,
       2,     2,     2,     4,     3,     2,     2,     2,     0,     0,
       0,     0,    10,     1,     1,     8,     3,     5,     5,     4,
       0,     0,     6,     0,     4,     0,     3,     0,     0,     7,
       0,     2,     3,     3,     3,     0,     1,     1,     1,     1,
       1,     1,     0,     0,     8,     0,     5,     3,     7,     3,
       3,     1,     1,     0,     3,     1,     0,     0,     7,     0,
       0,     5,     0,     0,     5,     0,     0,     5,     1,     0,
       0,     5,     0,     0,     5,     1,     1,     1,     3,     1,
       1,     1,     0,     0,     0,    13,     2,     1,     1,     1,
       1,     3,     3,     3,     0,     8,     6,     4,     2,     1,
       0,     1,     1,     0,     0,     0,    10,     4,     0,     0,
       4,     0,     4,     0,     4,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 125 "parser.y"
         {printf("\n\nPROGRAM IS VALID\n\n"); display_quad(); displaySymTable(); exit(0);}
#line 1808 "y.tab.c"
    break;

  case 29:
#line 177 "parser.y"
                 {push(yyvsp[0]); top++;}
#line 1814 "y.tab.c"
    break;

  case 30:
#line 177 "parser.y"
                                                {codegen_arraytemp();}
#line 1820 "y.tab.c"
    break;

  case 31:
#line 177 "parser.y"
                                                                                        {codegen_arrayassign();}
#line 1826 "y.tab.c"
    break;

  case 33:
#line 180 "parser.y"
            {push(yyvsp[0]);}
#line 1832 "y.tab.c"
    break;

  case 34:
#line 181 "parser.y"
       {push(yyvsp[0]);}
#line 1838 "y.tab.c"
    break;

  case 35:
#line 185 "parser.y"
                                                     {}
#line 1844 "y.tab.c"
    break;

  case 36:
#line 188 "parser.y"
                              { 
    
    if(!insert(&count, scope + 1, yyvsp[-2], yyvsp[-1], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 1857 "y.tab.c"
    break;

  case 37:
#line 196 "parser.y"
                            {
     
    if(!insert(&count, scope + 1, yyvsp[-4], yyvsp[-3], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update(yyvsp[-3], val, scope + 1);
}
#line 1871 "y.tab.c"
    break;

  case 38:
#line 206 "parser.y"
{
    
    if(!insert(&count, scope + 1, tdType, yyvsp[-3], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update(yyvsp[-3], val, scope);
}
#line 1885 "y.tab.c"
    break;

  case 39:
#line 215 "parser.y"
                             {
    
    if(!insert(&count, scope+1, yyvsp[-2], yyvsp[-1], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 1898 "y.tab.c"
    break;

  case 41:
#line 226 "parser.y"
              {push(yyvsp[0]);}
#line 1904 "y.tab.c"
    break;

  case 42:
#line 226 "parser.y"
                                                              {codegen_call();}
#line 1910 "y.tab.c"
    break;

  case 43:
#line 229 "parser.y"
                          { push(yyvsp[0]); codegen_param(); }
#line 1916 "y.tab.c"
    break;

  case 45:
#line 230 "parser.y"
      { push(yyvsp[0]); codegen_param(); }
#line 1922 "y.tab.c"
    break;

  case 47:
#line 231 "parser.y"
              {push(yyvsp[0]);}
#line 1928 "y.tab.c"
    break;

  case 48:
#line 231 "parser.y"
                                 {codegen_assign(); codegen_param();}
#line 1934 "y.tab.c"
    break;

  case 56:
#line 244 "parser.y"
            {strcpy(tdType,yyvsp[0]);}
#line 1940 "y.tab.c"
    break;

  case 57:
#line 245 "parser.y"
         {strcpy(tdType,yyvsp[0]);}
#line 1946 "y.tab.c"
    break;

  case 58:
#line 246 "parser.y"
        {strcpy(tdType,yyvsp[0]);}
#line 1952 "y.tab.c"
    break;

  case 59:
#line 247 "parser.y"
          {strcpy(tdType,yyvsp[0]);}
#line 1958 "y.tab.c"
    break;

  case 60:
#line 248 "parser.y"
        {strcpy(tdType,yyvsp[0]);}
#line 1964 "y.tab.c"
    break;

  case 61:
#line 249 "parser.y"
       {strcpy(tdType,yyvsp[0]);}
#line 1970 "y.tab.c"
    break;

  case 62:
#line 253 "parser.y"
                {push(yyvsp[0]);}
#line 1976 "y.tab.c"
    break;

  case 63:
#line 253 "parser.y"
                                   {codegen_assign();}
#line 1982 "y.tab.c"
    break;

  case 64:
#line 253 "parser.y"
                                                                             {
    if(!insert(&count, scope, yyvsp[-7], yyvsp[-6], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update(yyvsp[-6], val, scope);    
}
#line 1995 "y.tab.c"
    break;

  case 65:
#line 261 "parser.y"
            {push(yyvsp[0]); push("0"); codegen_assign();}
#line 2001 "y.tab.c"
    break;

  case 66:
#line 261 "parser.y"
                                                                          {
    if(!insert(&count, scope, yyvsp[-4], yyvsp[-3], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 2013 "y.tab.c"
    break;

  case 74:
#line 280 "parser.y"
                              {
    if(!insert(&count, scope, tdType, yyvsp[-1], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    push(yyvsp[-1]);
    push("0");
    codegen_assign();
}
#line 2028 "y.tab.c"
    break;

  case 75:
#line 290 "parser.y"
      {
    if(!insert(&count, scope, tdType, yyvsp[0], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    
}
#line 2041 "y.tab.c"
    break;

  case 76:
#line 298 "parser.y"
              {push(yyvsp[0]);}
#line 2047 "y.tab.c"
    break;

  case 77:
#line 298 "parser.y"
                                 {codegen_assign();}
#line 2053 "y.tab.c"
    break;

  case 78:
#line 298 "parser.y"
                                                             {
    if(!insert(&count, scope, tdType, yyvsp[-5], yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update(yyvsp[-5], val, scope);
}
#line 2066 "y.tab.c"
    break;

  case 80:
#line 310 "parser.y"
                  {push(yyvsp[0]);}
#line 2072 "y.tab.c"
    break;

  case 81:
#line 310 "parser.y"
                                                      {
        if(find(scope, yyvsp[-4]) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        int idx1 = find(scope, yyvsp[-4]);
        char val2[100];
        
        char* id_type = symTable[idx1].dtype;

        if(!strcmp(op, "=")){
            update(yyvsp[-4], yyvsp[-1], scope);
            codegen_assign();
        }
        else if(!strcmp(op, "+=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 += atof(yyvsp[-1]);
                else
                    val1 += atoi(yyvsp[-1]);
                
                sprintf(val2, "%f", val1);
                update(yyvsp[-4], val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 += atoi(yyvsp[-1]);
                
                sprintf(val2, "%d", val1);
                update(yyvsp[-4], val2, scope);
            }
            codegen_syns();
        }
        else if(!strcmp(op, "-=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 -= atof(yyvsp[-1]);
                else
                    val1 -= atoi(yyvsp[-1]);
                
                sprintf(val2, "%f", val1);
                update(yyvsp[-4], val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 -= atoi(yyvsp[-1]);
                
                sprintf(val2, "%d", val1);
                update(yyvsp[-4], val2, scope);
            }
            
            codegen_syns();
        }
        else if(!strcmp(op, "*=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 *= atof(yyvsp[-1]);
                else
                    val1 *= atoi(yyvsp[-1]);
                
                sprintf(val2, "%f", val1);
                update(yyvsp[-4], val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 *= atoi(yyvsp[-1]);
                
                sprintf(val2, "%d", val1);
                update(yyvsp[-4], val2, scope);
            }

            codegen_syns();
        }
        else if(!strcmp(op, "/=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 /= atof(yyvsp[-1]);
                else
                    val1 /= atoi(yyvsp[-1]);
                
                sprintf(val2, "%f", val1);
                update(yyvsp[-4], val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 /= atoi(yyvsp[-1]);
                
                sprintf(val2, "%d", val1);
                update(yyvsp[-4], val2, scope);
            }
            codegen_syns();
        }
        else if(!strcmp(op, "%=")){
            int val1 = atoi(symTable[idx1].value);
            val1 %= atoi(yyvsp[-1]);
            sprintf(val2, "%d", val1);
            update(yyvsp[-4], val2, scope);
            codegen_syns();
        }
        else if(!strcmp(op, ">>=")){
            int val1 = atoi(symTable[idx1].value);
            val1 >>= atoi(yyvsp[-1]);
            sprintf(val2, "%d", val1);
            update(yyvsp[-4], val2, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "<<=")){
            int val1 = atoi(symTable[idx1].value);
            val1 <<= atoi(yyvsp[-1]);
            sprintf(val2, "%d", val1);
            update(yyvsp[-4], val2, scope);
            codegen_syns();
        }
        else{
            yyerror("Invalid operation");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
      }
#line 2201 "y.tab.c"
    break;

  case 82:
#line 436 "parser.y"
     {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}}
#line 2207 "y.tab.c"
    break;

  case 83:
#line 436 "parser.y"
                                                                                                 {push("+");}
#line 2213 "y.tab.c"
    break;

  case 84:
#line 436 "parser.y"
                                                                                                                {
    if(flag){
        val2f = atof(val);
        float val1 = val1f+val2f;
        sprintf(yyval, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f+val2f;
            sprintf(yyval, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i+val2i;
            sprintf(yyval, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }

    
    codegen();
}
#line 2247 "y.tab.c"
    break;

  case 85:
#line 465 "parser.y"
   {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}}
#line 2253 "y.tab.c"
    break;

  case 86:
#line 465 "parser.y"
                                                                                               {push("-");}
#line 2259 "y.tab.c"
    break;

  case 87:
#line 465 "parser.y"
                                                                                                              {
    if(flag){
        val2f = atof(val);
        float val1 = val1f-val2f;
        sprintf(yyval, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f-val2f;
            sprintf(yyval, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i-val2i;
            sprintf(yyval, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }

    codegen();
}
#line 2292 "y.tab.c"
    break;

  case 88:
#line 493 "parser.y"
   {yyval = yyvsp[0];}
#line 2298 "y.tab.c"
    break;

  case 89:
#line 496 "parser.y"
     {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}}
#line 2304 "y.tab.c"
    break;

  case 90:
#line 496 "parser.y"
                                                                                                 {push("*");}
#line 2310 "y.tab.c"
    break;

  case 91:
#line 496 "parser.y"
                                                                                                                {
    if(flag){
        val2f = atof(val);
        float val1 = val1f*val2f;
        sprintf(yyval, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f*val2f;
            sprintf(yyval, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i*val2i;
            sprintf(yyval, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }
    codegen();
}
#line 2342 "y.tab.c"
    break;

  case 92:
#line 523 "parser.y"
   {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}}
#line 2348 "y.tab.c"
    break;

  case 93:
#line 523 "parser.y"
                                                                                               {push("/");}
#line 2354 "y.tab.c"
    break;

  case 94:
#line 523 "parser.y"
                                                                                                              {

    if(flag){
        val2f = atof(val);
        float val1 = val1f/val2f;
        sprintf(yyval, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f/val2f;
            sprintf(yyval, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i/val2i;
            sprintf(yyval, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }
    
    codegen();
}
#line 2388 "y.tab.c"
    break;

  case 95:
#line 552 "parser.y"
   {yyval = yyvsp[0];}
#line 2394 "y.tab.c"
    break;

  case 96:
#line 554 "parser.y"
        {
        if(find(scope, yyvsp[0]) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push(yyvsp[0]);
        int idx = find(scope, yyvsp[0]);
        
        if(!strcmp(symTable[idx].dtype, "float")){
            sprintf(yyval, "%f", atof(symTable[idx].value));
            sprintf(val, "%f", atof(symTable[idx].value));
            strcpy(ddtype, "float");
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            sprintf(yyval, "%d", atoi(symTable[idx].value));
            sprintf(val, "%d", atoi(symTable[idx].value));
            strcpy(ddtype, "int");
        }
      }
#line 2419 "y.tab.c"
    break;

  case 97:
#line 574 "parser.y"
       {strcpy(val, yyvsp[0]); yyval = yyvsp[0]; push(yyvsp[0]);
        char *position_ptr = strchr(val, '.');
        if(position_ptr != NULL){
            if(!(strcmp(tdType, "int")))
            {
                yyerror("Mismatched Datatype");
                printf("PROGRAM INVALID\n");
                display_quad(); displaySymTable(); exit(0);
            }
            strcpy(ddtype, "float");
        }
        else
            strcpy(ddtype, "int");
}
#line 2438 "y.tab.c"
    break;

  case 98:
#line 588 "parser.y"
              {yyval = yyvsp[-1];}
#line 2444 "y.tab.c"
    break;

  case 99:
#line 589 "parser.y"
       {
        yyval = yyvsp[0]; push(yyvsp[0]);
      }
#line 2452 "y.tab.c"
    break;

  case 101:
#line 593 "parser.y"
          {push(yyvsp[0]);}
#line 2458 "y.tab.c"
    break;

  case 102:
#line 596 "parser.y"
                            {for1();}
#line 2464 "y.tab.c"
    break;

  case 103:
#line 596 "parser.y"
                                                        {for2();}
#line 2470 "y.tab.c"
    break;

  case 104:
#line 596 "parser.y"
                                                                            {for3();}
#line 2476 "y.tab.c"
    break;

  case 105:
#line 596 "parser.y"
                                                                                                            {for4(); scope--;}
#line 2482 "y.tab.c"
    break;

  case 111:
#line 608 "parser.y"
                       {
    if(!strcmp(yyvsp[-1], "&&")){
        if(yyvsp[-2] && yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], "||")){
        if(yyvsp[-2] || yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 2506 "y.tab.c"
    break;

  case 112:
#line 627 "parser.y"
            {
    if(!strcmp(yyvsp[-1], "==")){
        if(yyvsp[-2] == yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], ">=")){
        if(yyvsp[-2] >= yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], "<")){
        if(yyvsp[-2] < yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], ">")){
        if(yyvsp[-2] > yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], "<=")){
        if(yyvsp[-2] <= yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-1], "!=")){
        if(yyvsp[-2] != yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    
}
#line 2555 "y.tab.c"
    break;

  case 114:
#line 672 "parser.y"
           {
    if(!strcmp(yyvsp[-1], "==")){
        if(yyvsp[-2] == yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp(yyvsp[-1], ">=")){
        if(yyvsp[-2] >= yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp(yyvsp[-1], "<")){
        if(yyvsp[-2] < yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp(yyvsp[-1], ">")){
        if(yyvsp[-2] > yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp(yyvsp[-1], "<=")){
        if(yyvsp[-2] <= yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp(yyvsp[-1], "!=")){
        if(yyvsp[-2] != yyvsp[0])
            val1 = 1;
        else
            val1 = 0;
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 2603 "y.tab.c"
    break;

  case 115:
#line 714 "parser.y"
                    {
    if(!strcmp(yyvsp[-2], "==")){
        if(yyvsp[-3] == yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp(yyvsp[-2], ">=")){
        if(yyvsp[-3] >= yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp(yyvsp[-2], "<")){
        if(yyvsp[-3] < yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp(yyvsp[-2], ">")){
        if(yyvsp[-3] > yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp(yyvsp[-2], "<=")){
        if(yyvsp[-3] <= yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp(yyvsp[-2], "!=")){
        if(yyvsp[-3] != yyvsp[-1])
            val2 = 1;
        else
            val2 = 0;
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }

    if(!strcmp(yyvsp[-4], "&&")){
        if(val1 && val2)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp(yyvsp[-4], "||")){
        if(val1 || val2)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }

}
#line 2670 "y.tab.c"
    break;

  case 116:
#line 776 "parser.y"
                           {
        if(!strcmp(yyvsp[-2], "==")){
        if(yyvsp[-3] == yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-2], ">=")){
        if(yyvsp[-3] >= yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-2], "<")){
        if(yyvsp[-3] < yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-2], ">")){
        if(yyvsp[-3] > yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-2], "<=")){
        if(yyvsp[-3] <= yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-2], "!=")){
        if(yyvsp[-3] != yyvsp[-1])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 2718 "y.tab.c"
    break;

  case 117:
#line 819 "parser.y"
                 {
    if(!strcmp(yyvsp[-1], "==")){
        if(yyvsp[-2] == yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-1], ">=")){
        if(yyvsp[-2] >= yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-1], "<")){
        if(yyvsp[-2] < yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-1], ">")){
        if(yyvsp[-2] > yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-1], "<=")){
        if(yyvsp[-2] <= yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp(yyvsp[-1], "!=")){
        if(yyvsp[-2] != yyvsp[0])
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else{
        yyerror("Invalid operation");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
#line 2766 "y.tab.c"
    break;

  case 118:
#line 863 "parser.y"
    {
    if(!yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
}
#line 2777 "y.tab.c"
    break;

  case 119:
#line 869 "parser.y"
   {
    if(yyvsp[0])
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
}
#line 2788 "y.tab.c"
    break;

  case 124:
#line 883 "parser.y"
                                {if1();}
#line 2794 "y.tab.c"
    break;

  case 125:
#line 883 "parser.y"
                                                          {if2();}
#line 2800 "y.tab.c"
    break;

  case 126:
#line 883 "parser.y"
                                                                            {if3();}
#line 2806 "y.tab.c"
    break;

  case 129:
#line 890 "parser.y"
                        {push(yyvsp[0]); codegen_return();}
#line 2812 "y.tab.c"
    break;

  case 131:
#line 891 "parser.y"
                 {push(yyvsp[0]); codegen_return();}
#line 2818 "y.tab.c"
    break;

  case 133:
#line 892 "parser.y"
                    {push(yyvsp[0]); codegen_return();}
#line 2824 "y.tab.c"
    break;

  case 138:
#line 901 "parser.y"
                     {
        if(find(scope, yyvsp[0]) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push(yyvsp[-1]);
        push(yyvsp[0]);
        codgen_un();
        int idx = find(scope, yyvsp[0]);
        
        if(!symTable[idx].dtype, "float"){
            float v = atof(symTable[idx].value);
            ++v;
            sprintf(yyval, "%f", v);
        }    
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            ++v;
            sprintf(yyval, "%d", v);
        }

        update(yyvsp[0], yyval, scope);
    }
#line 2853 "y.tab.c"
    break;

  case 139:
#line 925 "parser.y"
             {
        if(find(scope, yyvsp[-1]) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push(yyvsp[-1]);
        push(yyvsp[0]);
        codgen_un();
        int idx = find(scope, yyvsp[-1]);

        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            v++;
            sprintf(yyval, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            v++;
            sprintf(yyval, "%d", v);
        }
        
        update(yyvsp[-1], yyval, scope);
    }
#line 2882 "y.tab.c"
    break;

  case 140:
#line 949 "parser.y"
             {
        if(find(scope, yyvsp[0]) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push(yyvsp[-1]);
        push(yyvsp[0]);
        codgen_un();
        int idx = find(scope, yyvsp[0]);

        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            --v;
            sprintf(yyval, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            --v;
            sprintf(yyval, "%d", v);
        }

        update(yyvsp[0], yyval, scope);
    }
#line 2911 "y.tab.c"
    break;

  case 141:
#line 973 "parser.y"
             {
        if(find(scope, yyvsp[-1]) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push(yyvsp[-1]);
        push(yyvsp[0]);
        codgen_un();
        int idx = find(scope, yyvsp[-1]);
        
        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            v--;
            sprintf(yyval, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            v--;
            sprintf(yyval, "%d", v);
        }

        update(yyvsp[-1], yyval, scope);
    }
#line 2940 "y.tab.c"
    break;

  case 142:
#line 999 "parser.y"
              {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2946 "y.tab.c"
    break;

  case 143:
#line 1000 "parser.y"
        {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2952 "y.tab.c"
    break;

  case 144:
#line 1003 "parser.y"
              {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2958 "y.tab.c"
    break;

  case 145:
#line 1004 "parser.y"
        {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2964 "y.tab.c"
    break;

  case 146:
#line 1005 "parser.y"
         {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2970 "y.tab.c"
    break;

  case 147:
#line 1008 "parser.y"
             {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2976 "y.tab.c"
    break;

  case 148:
#line 1009 "parser.y"
       {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2982 "y.tab.c"
    break;

  case 149:
#line 1010 "parser.y"
       {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2988 "y.tab.c"
    break;

  case 150:
#line 1011 "parser.y"
        {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 2994 "y.tab.c"
    break;

  case 151:
#line 1012 "parser.y"
        {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 3000 "y.tab.c"
    break;

  case 152:
#line 1013 "parser.y"
       {yyval = yyvsp[0]; push(yyvsp[0]);}
#line 3006 "y.tab.c"
    break;

  case 153:
#line 1016 "parser.y"
               {strcpy(op,yyvsp[0]); yyval = yyvsp[0];}
#line 3012 "y.tab.c"
    break;

  case 154:
#line 1017 "parser.y"
          { strcpy(op,yyvsp[0]); push("+="); yyval = yyvsp[0];}
#line 3018 "y.tab.c"
    break;

  case 155:
#line 1018 "parser.y"
          {strcpy(op,yyvsp[0]); push("*="); yyval = yyvsp[0];}
#line 3024 "y.tab.c"
    break;

  case 156:
#line 1019 "parser.y"
          {strcpy(op,yyvsp[0]); push("/="); yyval = yyvsp[0];}
#line 3030 "y.tab.c"
    break;

  case 157:
#line 1020 "parser.y"
          {strcpy(op,yyvsp[0]); push("%="); yyval = yyvsp[0];}
#line 3036 "y.tab.c"
    break;

  case 158:
#line 1021 "parser.y"
         {strcpy(op,yyvsp[0]); push("<<="); yyval = yyvsp[0];}
#line 3042 "y.tab.c"
    break;

  case 159:
#line 1022 "parser.y"
         {strcpy(op,yyvsp[0]); push(">>="); yyval = yyvsp[0];}
#line 3048 "y.tab.c"
    break;

  case 160:
#line 1023 "parser.y"
          {strcpy(op,yyvsp[0]); push("-="); yyval = yyvsp[0];}
#line 3054 "y.tab.c"
    break;

  case 161:
#line 1026 "parser.y"
             {yyval = "1"; push(yyvsp[0]);}
#line 3060 "y.tab.c"
    break;

  case 162:
#line 1027 "parser.y"
          {yyval = "0"; push(yyvsp[0]);}
#line 3066 "y.tab.c"
    break;


#line 3070 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1030 "parser.y"

#include <ctype.h>


void yyerror(const char *s) {
    printf("\nERROR: %s on line %d\n",s, yylineno);
}

char st[100][20];

int lnum = 0;
int ltop = 0;
int label[25];
char i_[3]="00";
char temp[2]="t";
int paramCall = 0;
char call[5] = "call";
char param[6] = "param";




void push(char* val){
    strcpy(st[top++], val);
}

void codegen_arrayassign(){
    printf("%s[%s] = %s \n",st[top-3],st[top-2],st[top-1]);
    insert_quad("[]=",st[top-3],st[top-2],st[top-1]);
    top-=2;
}

void codegen_arraytemp(){
    strcpy(temp,"t");
	strcat(temp,i_);
    printf("%s = 4 * %s\n",temp,st[top-1]);
    insert_quad("*","4",st[top-1],temp);
    top-=1;
	strcpy(st[top-1],temp);
	if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
}

void codegen_return(){
    printf("return %s\n", st[top-1]);
    insert_quad("return",st[top-1],NULL,NULL);
    top-=1;
}

void codegen_call(){
    printf("call(%s, %d)\n", st[top-1], paramCall);
    char temp[100];
    sprintf(temp, "%d", paramCall);
    insert_quad("call",st[top-1],temp,NULL);
    paramCall = 0;
    top-=1;
}

void codegen_param(){
    printf("param %s\n", st[top-1]);
    insert_quad(param,st[top-1],NULL,NULL);
    top-=1;
    paramCall += 1;
}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    insert_quad(st[top-2],st[top-3],st[top-1],temp);

	
    top-=2;
	strcpy(st[top-1],temp);
	if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
}

void codgen_un()
{
	strcpy(temp,"t");
	strcat(temp,i_);
      
    if((!strcmp(st[top - 2],"++")) || (!strcmp(st[top - 2],"--"))){
    printf(" %s = %s %c %d\n", temp, st[top-1], st[top-2][0], 1);

    char *ptr = malloc(2*sizeof(char));
    ptr[0] = st[top-2][0];
    ptr[1] = '\0';

    insert_quad(ptr,st[top-1],"1",temp);
    insert_quad("=",temp,NULL,st[top-1]);
    printf("%s = %s\n", st[top - 1], temp);

    free(ptr);

    }
    else if((!strcmp(st[top - 1],"++")) || (!strcmp(st[top - 1],"--"))){
    printf(" %s = %s %c %d\n", temp, st[top-2], st[top-1][0], 1);

    char *ptr = malloc(2*sizeof(char));
    ptr[0] = st[top-1][0];
    ptr[1] = '\0';

    insert_quad(ptr,st[top-2],"1",temp);
    insert_quad("=",temp,NULL,st[top-2]);
    printf("%s = %s\n", st[top - 2], temp);

    free(ptr);
    }
    else
        printf(" %s = %s%s\n", temp, st[top-2], st[top-1]);
    top = top - 1;
    strcpy(st[top - 1], temp);
    if(i_[1]!='9')
        i_[1]++;
    else
    {
        i_[1] = '0';
        i_[0]++;
    }
}

//done
void codegen_syns(){
  printf("%s %c %s %c %s\n", st[top-3], st[top-2][1], st[top-3], st[top-2][0], st[top - 1]);

  char *ptr = malloc(2*sizeof(char));
  ptr[0] = st[top-2][0];
  ptr[1] = '\0';
  insert_quad(ptr,st[top-3],st[top-1],st[top-3]);

  free(ptr);
  
  top = top - 2;
}


void codegen_assign(){
  printf("%s = %s\n", st[top-2], st[top-1]);
  insert_quad("=",st[top-1],NULL,st[top-2]);
  

  top = top - 2;
}

void showSt(){
  printf("\nprinting the stack contents\n");
  int temp = top;
  while(temp != -1){
    printf("%s ", st[temp--]);

  }
  printf("\nstack over \n---------------------------\n");
}

//for
void for1() //mainly for getting labels ready
{
      label[ltop++] = ++lnum; // label after (for(int i = 0;)) i.e. after declaring i = 0; => i = 0; label1: .... [Most important: label for checking condition]
      printf("L%d : \n",label[ltop - 1]);
      char lab[26] = "L";
      char temp1[100];
      sprintf(temp1, "%d", label[ltop - 1]);
      strcat(lab, temp1);

      insert_quad("Label",NULL,NULL,lab);
      label[ltop++] = ++lnum; //label for incrementing
      label[ltop++] = ++lnum; //label for body of for loop
      label[ltop++] = ++lnum; //label for statements outside for loop
}

void for2() //ICG for condition check
{
	strcpy(temp,"t");
	strcat(temp,i_);	
    printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    char temp1[50] = "not ";
    strcat(temp1, st[top-2]);
    insert_quad(temp1,st[top-3],st[top-1],temp);

    top -= 2;
	
    printf("if %s goto L%d\n",temp,label[ltop - 1]);

    char lab2[26] = "L";
    char temp2[100];
    sprintf(temp2, "%d", label[ltop - 1]);
    strcat(lab2, temp2);
    insert_quad("if",temp,NULL,temp2);
	
    if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
	printf("goto L%d\n", label[ltop - 3]);
  printf("L%d :\n", label[ltop - 2]);

}

void for3() //incrementing and executing loop again
{
  printf("goto L%d\n", label[ltop - 4]);
  char lab[26] = "L";
  char temp1[100];
  sprintf(temp1, "%d", label[ltop - 4]);
  strcat(lab, temp1);
  insert_quad("goto",NULL,NULL,lab);
  
  printf("L%d :\n", label[ltop - 3]);
  char lab2[26] = "L";
  char temp2[100];
  sprintf(temp2, "%d", label[ltop - 3]);
  strcat(lab2, temp2);
  insert_quad("Label",NULL,NULL,lab2);
}

void for4() //go to autoincrement and print label after loop
{
	printf("goto L%d \n",label[ltop - 2]);
    char lab[26] = "L";
    char temp1[100];
    sprintf(temp1, "%d", label[ltop - 4]);
    strcat(lab, temp1);
    insert_quad("goto",NULL,NULL,lab);
	
    printf("L%d : \n",label[ltop - 1]);
    char lab2[26] = "L";
    char temp2[100];
    sprintf(temp2, "%d", label[ltop - 3]);
    strcat(lab2, temp2);

    ltop = ltop - 4;
}

//if
void if1()
{
 lnum++;
 strcpy(temp,"t");
 strcat(temp,i_);
 printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
 char temp1[50] = "not ";
 strcat(temp1, st[top-2]);
 insert_quad(temp1,st[top-3],st[top-1],temp);
 top -= 2;
 
 printf("if %s goto L%d\n",temp,lnum);
 char lab2[26] = "L";
 char temp2[100];
 sprintf(temp2, "%d", lnum);
 strcat(lab2, temp2);
 insert_quad("if",temp,NULL,temp2);

 i_[0]++;
 label[++ltop]=lnum;
}

void if2()
{
int x;
lnum++;
x=label[ltop--];

char lab2[26] = "L";
char temp2[100];
sprintf(temp2, "%d", x);
insert_quad("goto",NULL,NULL,temp2);
printf("goto L%d\n",lnum);

printf("L%d: \n",x);
char lab[26] = "L";
char temp1[100];
sprintf(temp1, "%d", x);
strcat(lab, temp1);

insert_quad("Label",NULL,NULL,lab);
label[++ltop]=lnum;
}

//if-else
void if3()
{
int y;
y=label[ltop--];
printf("L%d: \n",y);
char lab[26] = "L";
char temp1[100];
sprintf(temp1, "%d", y);
strcat(lab, temp1);

insert_quad("Label",NULL,NULL,lab);

}


int main()
{
    //printf("LINE\tTOKENS\n");
    yyparse();
    
    /*quad *current=quad_head;
    quad *next=NULL;
    while(current!=NULL)
    {
        next=current->next;
        free(current);
        current=next;
    }
    quad_head=NULL;*/
    return 0;

}
