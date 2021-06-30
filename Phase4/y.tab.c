/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

    #include <stdio.h>
    #include "symtable.h"
    #include "quads.h"
    #include "funcstack.h"
    #include "t_code_gen.h"

    #define STACK_SIZE 100

    int yyerror (char* yaccProvideMessage);
    int yylex (void);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    struct Stack* stack;
    int inFunct = 0;
    int local=0;
    int isCalledFunc = 0;
    int comingFromFuncdef = 0;
    int inLoop=0, inIF=0, inELSE=0;
    typedef enum lastCurlyUsedenum { E_FUNCTION, E_IF, E_ELSE, E_LOOP }lastCurlyUsedenum; // ALLAGI
    lastCurlyUsedenum lastCurlyUsed; // ALLAGI
    char *lastlvalue = ""; /* NEW */
    

    SymTable_T *symtab;

    funcStack *funcStackRoot = NULL;
    


#line 99 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 36 "parser.y" /* yacc.c:355  */

    int intNum;
    double doubleNum;
    char* id;
    struct stmt_t *stmt_tt;
    struct expr* expression;
    struct forstruct* forpref;
    struct call_t* s_call;
    struct SymbolTableEntry * symbol;

#line 260 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 275 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   539

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   113,   114,   117,   118,   119,   120,   121,
     122,   122,   132,   132,   142,   143,   144,   147,   148,   155,
     162,   169,   176,   183,   194,   205,   216,   227,   238,   249,
     256,   263,   266,   267,   275,   282,   300,   300,   319,   337,
     337,   355,   358,   358,   382,   386,   387,   388,   394,   397,
     426,   426,   447,   456,   459,   466,   474,   481,   484,   489,
     489,   505,   514,   515,   518,   528,   538,   539,   542,   543,
     546,   558,   575,   578,   579,   582,   585,   585,   605,   620,
     637,   655,   676,   676,   686,   694,   695,   696,   697,   698,
     701,   702,   705,   705,   711,   714,   714,   715,   718,   719,
     726,   735,   743,   752,   755,   763,   763,   777,   785,   788,
     791,   791,   801,   801
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT", "LOCAL", "TRUE",
  "FALSE", "NIL", "NOT_EQUALS", "EQUALS", "ASSIGN", "PLUS_PLUS",
  "MINUS_MINUS", "PLUS", "MINUS", "MULTI", "DIV", "MOD",
  "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "GREATER_THAN", "LESS_THAN",
  "LEFT_CURLY", "RIGHT_CURLY", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON", "COMMA", "COLON",
  "SCOPE", "DOT", "DOUBLE_DOT", "SPACE", "LINE_COMMENT",
  "BLOCK_COMMENT_START", "BLOCK_COMMENT_END", "NEWLINE", "TAB", "INTCONST",
  "REALCONST", "STRING", "ID", "UMINUS", "LOWER_THAN_ELSE", "$accept",
  "program", "statements", "stmt", "$@1", "$@2", "expr", "term", "$@3",
  "$@4", "assignexpr", "$@5", "primary", "lvalue", "$@6", "member", "call",
  "$@7", "callsuffix", "normcall", "methodcall", "elist", "elists",
  "objectdef", "indexed", "indexeds", "indexedelem", "block", "$@8",
  "funcdef", "funcprefix", "funcargs", "$@9", "funcbody", "const",
  "number", "idlist", "$@10", "idlists", "$@11", "ifstmt", "ifprefix",
  "elseprefix", "whilestmt", "whilestart", "whilecond", "forstmt", "$@12",
  "forprefix", "N", "M", "returnstmt", "$@13", "$@14", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

#define YYPACT_NINF -173

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-173)))

#define YYTABLE_NINF -113

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-113)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -173,    13,   146,  -173,   -28,  -173,   -21,   -36,   -14,  -173,
    -173,   187,  -173,  -173,  -173,  -173,     7,     7,   187,    -8,
      90,    15,  -173,   -15,  -173,  -173,  -173,  -173,  -173,   268,
    -173,  -173,  -173,   -16,  -173,    50,  -173,  -173,  -173,     6,
    -173,  -173,  -173,   146,  -173,    10,  -173,  -173,  -173,   187,
     187,  -173,   187,    16,    26,    32,  -173,    -9,    80,    19,
      50,    19,  -173,  -173,  -173,   187,   246,    53,    55,    54,
     331,    57,  -173,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,  -173,   187,    42,    75,
      77,    81,   -29,   187,   187,    47,  -173,    70,   111,   187,
     146,   187,   352,    78,   289,  -173,  -173,  -173,  -173,    82,
     146,   223,   187,  -173,  -173,  -173,    85,  -173,  -173,    84,
     494,   480,   508,   508,     8,     8,  -173,  -173,  -173,   189,
     189,   189,   189,   394,  -173,  -173,  -173,   187,   187,    65,
    -173,  -173,  -173,   415,    86,  -173,    68,  -173,  -173,  -173,
     146,   373,  -173,    88,  -173,  -173,  -173,    84,    94,   187,
     246,    54,   187,  -173,   459,    91,    93,  -173,  -173,  -173,
      96,  -173,  -173,  -173,   187,  -173,   436,  -173,  -173,    97,
    -173,   187,    98,  -173,  -173,   310,  -173,  -173,    99,    92,
    -173,   146,  -173,  -173,  -173,  -173,    98,  -173,  -173
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,   103,     0,    81,   110,    10,
      12,     0,    50,    88,    89,    87,     0,     0,     0,    76,
      67,     0,    16,     0,    90,    91,    86,    49,     3,     0,
      31,    17,    41,    44,    53,    45,    46,    14,    15,     0,
      48,    85,     6,     0,     7,     0,     8,   108,     9,     0,
      67,    80,     0,     0,     0,     0,    34,     0,     0,    35,
       0,    38,    33,    78,     4,     0,    69,     0,     0,    74,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,    67,     0,    82,     0,    98,     0,
       0,    67,     0,     0,     0,   113,    11,    13,    51,     0,
       0,     0,     0,    66,    70,    71,     0,    72,    32,    47,
      29,    30,    28,    27,    18,    19,    20,    21,    22,    24,
      26,    23,    25,     0,    54,    37,    40,     0,    67,     0,
      60,    62,    63,     0,     0,    56,    94,    84,    79,   101,
       0,     0,   102,     0,   100,   109,   111,     0,     3,     0,
      69,    74,    67,    55,    43,     0,     0,    57,    58,    92,
       0,    99,   104,   105,     0,    77,     0,    68,    73,     0,
      64,    67,    97,    83,   108,     0,    75,    61,     0,     0,
      93,     0,   107,    65,    95,   108,    97,   106,    96
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,    66,   -41,  -173,  -173,    -2,  -173,  -173,  -173,
    -173,  -173,  -173,    -6,  -173,  -173,    41,  -173,  -173,  -173,
    -173,   -49,   -22,  -173,  -173,   -17,    23,    49,  -173,   -18,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,   -38,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -172,
    -173,  -173,  -173,  -173
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    54,    55,    66,    30,    89,    90,
      31,    91,    32,    33,    57,    34,    35,    92,   140,   141,
     142,    67,   113,    36,    68,   117,    69,    37,    64,    38,
      39,    97,   146,   148,    40,    41,   170,   182,   190,   196,
      42,    43,   150,    44,    45,   100,    46,   184,    47,   101,
     174,    48,    52,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   103,    98,    71,   -42,   -36,   -39,   138,    49,    56,
      59,    61,   191,     3,   139,    50,    62,    51,    87,    70,
     -59,    12,     7,   197,  -112,    63,    88,   -59,    11,    12,
      13,    14,    15,    79,    80,    81,    16,    17,    72,    18,
     109,    29,    96,    58,   108,   144,    99,   102,    23,    20,
     104,    21,   153,    87,   105,   -59,    23,    60,    60,   152,
      27,    88,   -59,   111,   106,    24,    25,    26,    27,   158,
     107,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,    93,   133,    94,     7,   114,   165,
     115,   143,    95,   116,   119,   134,   135,   151,    29,   136,
     145,   137,    19,    11,    12,    13,    14,    15,    29,   171,
     160,    16,    17,   179,    18,   149,   155,    65,   166,   157,
     162,   169,    65,   168,    20,   173,    21,   175,   180,   181,
     110,    23,   188,   183,   187,   164,   193,   189,   177,   161,
      24,    25,    26,    27,   178,   194,   147,     0,    29,     4,
     195,     5,     6,     7,     8,     9,    10,   176,   198,    11,
      12,    13,    14,    15,     0,     0,     0,    16,    17,     0,
      18,     0,   185,     0,     0,     0,     0,     0,    19,     0,
      20,     0,    21,     0,    22,     0,     0,    23,     0,    29,
       0,     0,     0,     0,     0,     0,    24,    25,    26,    27,
      11,    12,    13,    14,    15,     0,     0,     0,    16,    17,
       0,    18,    77,    78,    79,    80,    81,  -113,  -113,  -113,
    -113,    20,     0,    21,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     0,    73,    74,     0,    24,    25,    26,
      27,    75,    76,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     0,     0,    73,    74,     0,
       0,     0,     0,   159,    75,    76,     0,     0,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,     0,    73,
      74,     0,     0,     0,     0,   112,    75,    76,     0,     0,
       0,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      73,    74,     0,     0,     0,     0,    86,    75,    76,     0,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    73,    74,     0,     0,     0,     0,   156,    75,    76,
       0,     0,     0,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    73,    74,     0,     0,     0,     0,   192,    75,
      76,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    73,    74,     0,     0,     0,   118,     0,
      75,    76,     0,     0,     0,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    73,    74,     0,     0,     0,   154,
       0,    75,    76,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    73,    74,     0,     0,     0,
     172,     0,    75,    76,     0,     0,     0,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    73,    74,     0,   163,
       0,     0,     0,    75,    76,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    73,    74,     0,
     167,     0,     0,     0,    75,    76,     0,     0,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,     0,   186,
      73,    74,     0,     0,     0,     0,     0,    75,    76,     0,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    73,     0,     0,     0,     0,     0,     0,    75,    76,
       0,     0,     0,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    75,    76,     0,     0,     0,    77,    78,    79,
      80,    81,    82,    83,    84,    85,  -113,  -113,     0,     0,
       0,    77,    78,    79,    80,    81,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       2,    50,    43,    21,    20,    21,    22,    36,    36,    11,
      16,    17,   184,     0,    43,    36,    18,    53,    34,    21,
      36,    14,     7,   195,    38,    33,    42,    43,    13,    14,
      15,    16,    17,    25,    26,    27,    21,    22,    53,    24,
      58,    43,    36,    36,    53,    94,    36,    49,    41,    34,
      52,    36,   101,    34,    38,    36,    41,    16,    17,   100,
      53,    42,    43,    65,    38,    50,    51,    52,    53,   110,
      38,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    34,    87,    36,     7,    35,   138,
      35,    93,    42,    39,    37,    53,    21,    99,   100,    22,
      53,    20,    32,    13,    14,    15,    16,    17,   110,   150,
     112,    21,    22,   162,    24,     4,    38,    32,    53,    37,
      36,    53,    32,    37,    34,    37,    36,    33,    37,    36,
      64,    41,   181,    37,    37,   137,    37,    39,   160,   116,
      50,    51,    52,    53,   161,    53,    97,    -1,   150,     3,
     191,     5,     6,     7,     8,     9,    10,   159,   196,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    21,    22,    -1,
      24,    -1,   174,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      34,    -1,    36,    -1,    38,    -1,    -1,    41,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    21,    22,
      -1,    24,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    11,    12,    -1,    50,    51,    52,
      53,    18,    19,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    40,    18,    19,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    11,
      12,    -1,    -1,    -1,    -1,    39,    18,    19,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      11,    12,    -1,    -1,    -1,    -1,    38,    18,    19,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    11,    12,    -1,    -1,    -1,    -1,    38,    18,    19,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    11,    12,    -1,    -1,    -1,    -1,    38,    18,
      19,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    11,    12,    -1,    -1,    -1,    37,    -1,
      18,    19,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    11,    12,    -1,    -1,    -1,    37,
      -1,    18,    19,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    11,    12,    -1,    -1,    -1,
      37,    -1,    18,    19,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    11,    12,    -1,    35,
      -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    11,    12,    -1,
      35,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      11,    12,    -1,    -1,    -1,    -1,    -1,    18,    19,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    18,    19,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    18,    19,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,     0,     3,     5,     6,     7,     8,     9,
      10,    13,    14,    15,    16,    17,    21,    22,    24,    32,
      34,    36,    38,    41,    50,    51,    52,    53,    59,    62,
      63,    66,    68,    69,    71,    72,    79,    83,    85,    86,
      90,    91,    96,    97,    99,   100,   102,   104,   107,    36,
      36,    53,   108,   109,    60,    61,    62,    70,    36,    69,
      72,    69,    62,    33,    84,    32,    62,    77,    80,    82,
      62,    85,    53,    11,    12,    18,    19,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    38,    34,    42,    64,
      65,    67,    73,    34,    36,    42,    36,    87,    59,    36,
     101,   105,    62,    77,    62,    38,    38,    38,    53,    85,
      58,    62,    39,    78,    35,    35,    39,    81,    37,    37,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    53,    21,    22,    20,    36,    43,
      74,    75,    76,    62,    77,    53,    88,    83,    89,     4,
      98,    62,    59,    77,    37,    38,    38,    37,    59,    40,
      62,    82,    36,    35,    62,    77,    53,    35,    37,    53,
      92,    59,    37,    37,   106,    33,    62,    78,    81,    77,
      37,    36,    93,    37,   103,    62,    33,    37,    77,    39,
      94,   105,    38,    37,    53,    59,    95,   105,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      60,    59,    61,    59,    59,    59,    59,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    63,    64,    63,    63,    65,
      63,    63,    67,    66,    68,    68,    68,    68,    68,    69,
      70,    69,    69,    69,    71,    71,    71,    71,    72,    73,
      72,    72,    74,    74,    75,    76,    77,    77,    78,    78,
      79,    79,    80,    81,    81,    82,    84,    83,    83,    85,
      86,    86,    88,    87,    89,    90,    90,    90,    90,    90,
      91,    91,    93,    92,    92,    95,    94,    94,    96,    96,
      97,    98,    99,   100,   101,   103,   102,   104,   105,   106,
     108,   107,   109,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       0,     3,     0,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     2,     2,     2,     0,     3,     2,     0,
       3,     1,     0,     4,     1,     1,     1,     3,     1,     1,
       0,     3,     2,     1,     3,     4,     3,     4,     4,     0,
       3,     6,     1,     1,     3,     5,     2,     0,     3,     0,
       3,     3,     2,     3,     0,     5,     0,     5,     2,     3,
       2,     1,     0,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     0,     0,     4,     0,     2,     4,
       4,     1,     3,     1,     3,     0,     8,     7,     0,     0,
       0,     4,     0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 110 "parser.y" /* yacc.c:1646  */
    {printf("\033[1;31mprogram\033[0m <- statements :line  \033[1;32m✓\033[0m\n", yylineno);}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 113 "parser.y" /* yacc.c:1646  */
    {printf("statements <- statements stmt :line  %d  \n", yylineno);}
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 114 "parser.y" /* yacc.c:1646  */
    {printf("statements <- empty :line  %d  \n", yylineno);}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 117 "parser.y" /* yacc.c:1646  */
    {resettemp();     printf("stmt <- expr; :line  %d  \n", yylineno);}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 118 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- ifstmt :line  %d  \n", yylineno);}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 119 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- whilestmt :line  %d  \n", yylineno);}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- forstmt :line  %d  \n", yylineno);}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 121 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- returnstmt :line  %d  \n", yylineno);}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 122 "parser.y" /* yacc.c:1646  */
    {
                                        if(inLoop == 0 || GlobalScope == 0){
                                                yyerror("Cannot break when not in loop.");
                                        }
                                }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 127 "parser.y" /* yacc.c:1646  */
    {
                                                        insertBrContList(nextquadlabel(), 0, 'b');
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("stmt <- break; :line  %d  \n", yylineno);
                                                }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 132 "parser.y" /* yacc.c:1646  */
    {
                                        if(inLoop == 0 || GlobalScope == 0){
                                                yyerror("Cannot continue when not in loop.");
                                        }
                                }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 137 "parser.y" /* yacc.c:1646  */
    {
                                                        insertBrContList(nextquadlabel(), 0, 'c');
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("stmt <- continue; :line  %d  \n", yylineno);
                                                }
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 142 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- block :line  %d  \n", yylineno);}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 143 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- funcdef :line  %d  \n", yylineno);}
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 144 "parser.y" /* yacc.c:1646  */
    {printf("stmt <- ; :line  %d  \n", yylineno);}
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 147 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("expr <- assignexpr :line  %d  \n", yylineno);}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 148 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(add, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);
                                                
                                                printf("expr <- expr + expr :line  %d  \n", yylineno);
                                        }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 155 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(sub, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);   
                                                
                                                printf("expr <- expr - expr :line  %d  \n", yylineno);
                                        }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(mul, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);

                                                printf("expr <- expr * expr :line  %d  \n", yylineno);
                                        }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 169 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(div_i, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);

                                                printf("expr <- expr DIV expr :line  %d  \n", yylineno);
                                        }
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 176 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(mod, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);        

                                                printf("expr <- expr MOD expr :line  %d  \n", yylineno);
                                        }
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 183 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_greater, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr > expr :line  %d  \n", yylineno);
                                        }
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 194 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_greatereq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);
                                                
                                                printf("expr <- expr >= expr :line  %d  \n", yylineno);
                                        }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 205 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_less, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);
                                                
                                                printf("expr <- expr < expr :line  %d  \n", yylineno);
                                        }
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 216 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_lesseq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr <= expr :line  %d  \n", yylineno);
                                        }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 227 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_eq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr == expr :line  %d  \n", yylineno);
                                        }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 238 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);

                                                emitQuad(if_noteq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), nextquadlabel()+3, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, (yyval.expression), newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr != expr :line  %d  \n", yylineno);
                                        }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 249 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(and, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);

                                                printf("expr <- expr AND expr :line  %d  \n", yylineno);
                                        }
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 256 "parser.y" /* yacc.c:1646  */
    {
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(or, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), -1, yylineno);

                                                printf("expr <- expr OR expr :line  %d  \n", yylineno);
                                        }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("expr <- term :line  %d  \n", yylineno);}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 266 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); printf("term <- ( expr ) :line  %d  \n", yylineno);}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 267 "parser.y" /* yacc.c:1646  */
    {
                                                                check_arith((yyvsp[0].expression));
                                                                (yyval.expression) = newexpr(arithexpr_e);
                                                                (yyval.expression)->sym = istempexpr((yyvsp[0].expression)) ? (yyvsp[0].expression)->sym :newtemp(symtab);
                                                                emitQuad(uminus,(yyval.expression), (yyvsp[0].expression), NULL, -1, yylineno);

                                                                printf("term <- -expr  :line  %d  \n", yylineno);
                                                        }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 275 "parser.y" /* yacc.c:1646  */
    {
                                                                (yyval.expression) = newexpr(boolexpr_e);
                                                                (yyval.expression)->sym = newtemp(symtab);
                                                                emitQuad(not, (yyval.expression), (yyvsp[0].expression), NULL, -1, yylineno);

                                                                printf("term <- NOT expr  :line  %d  \n", yylineno);
                                                        }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 282 "parser.y" /* yacc.c:1646  */
    {
                                if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1){
                                        yyerror("Cannot use function as lvalue");
                                }
                                
                                /*check_arith($2);*/
                                if((yyvsp[0].expression)->type == tableitem_e){
                                        (yyval.expression) = emit_iftableitem(symtab, (yyvsp[0].expression));
                                        emitQuad(add, (yyval.expression), (yyval.expression), newexpr_constint(1), -1, yylineno);
                                        emitQuad(tablesetelem, (yyvsp[0].expression), (yyvsp[0].expression)->index, (yyval.expression), -1, yylineno);
                                }else{
                                        emitQuad(add, (yyvsp[0].expression), (yyvsp[0].expression), newexpr_constint(1), -1, yylineno);
                                        (yyval.expression) = newexpr(arithexpr_e);
                                        (yyval.expression)->sym = newtemp(symtab);
                                        emitQuad(assign, (yyval.expression), (yyvsp[0].expression), NULL, -1, yylineno);
                                }
                                printf("term <- ++lvalue  :line  %d  \n", yylineno);
                        }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 300 "parser.y" /* yacc.c:1646  */
    {
                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)
                                yyerror("Cannot use function as lvalue");
                }
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 304 "parser.y" /* yacc.c:1646  */
    {
                                        /*check_arith($1);*/
                                        (yyval.expression) = newexpr(var_e);
                                        (yyval.expression)->sym = newtemp(symtab);
                                        if((yyvsp[-2].expression)->type == tableitem_e){
                                                expr* val = emit_iftableitem(symtab, (yyvsp[-2].expression));
                                                emitQuad(assign, (yyval.expression), val, NULL, -1, yylineno);
                                                emitQuad(add, val, val, newexpr_constint(1), -1,yylineno);
                                                emitQuad(tablesetelem, (yyvsp[-2].expression), (yyvsp[-2].expression)->index, val, -1, yylineno);
                                        }else{
                                                emitQuad(assign, (yyval.expression), (yyvsp[-2].expression), NULL, -1, yylineno);
                                                emitQuad(add, (yyvsp[-2].expression), (yyvsp[-2].expression), newexpr_constint(1), -1, yylineno);
                                        }
                                        printf("term <- lvalue++  :line  %d  \n", yylineno);
                                }
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 319 "parser.y" /* yacc.c:1646  */
    {
                                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1){
                                                yyerror("Cannot use function as lvalue");
                                        }
                                        
                                        /*check_arith($2);*/
                                        if((yyvsp[0].expression)->type == tableitem_e){
                                                (yyval.expression) = emit_iftableitem(symtab, (yyvsp[0].expression));
                                                emitQuad(sub, (yyval.expression), (yyval.expression), newexpr_constint(1), -1, yylineno);
                                                emitQuad(tablesetelem, (yyvsp[0].expression), (yyvsp[0].expression)->index, (yyval.expression), -1, yylineno);
                                        }else{
                                                emitQuad(sub, (yyvsp[0].expression), (yyvsp[0].expression), newexpr_constint(1), -1, yylineno);
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                emitQuad(assign, (yyval.expression), (yyvsp[0].expression), NULL, -1, yylineno);
                                        }
                                        printf("term <- --lvalue  :line  %d  \n", yylineno);
                                }
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 337 "parser.y" /* yacc.c:1646  */
    {
                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)
                                yyerror("Cannot use function as lvalue");
                }
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 340 "parser.y" /* yacc.c:1646  */
    {
                                                /*check_arith($1);*/
                                                (yyval.expression) = newexpr(var_e);
                                                (yyval.expression)->sym = newtemp(symtab);
                                                if((yyvsp[-2].expression)->type == tableitem_e){
                                                        expr* val = emit_iftableitem(symtab, (yyvsp[-2].expression));
                                                        emitQuad(assign, (yyval.expression), val, NULL, -1, yylineno);
                                                        emitQuad(sub, val, val, newexpr_constint(1), -1,yylineno);
                                                        emitQuad(tablesetelem, (yyvsp[-2].expression), (yyvsp[-2].expression)->index, val, -1, yylineno);
                                                }else{
                                                        emitQuad(assign, (yyval.expression), (yyvsp[-2].expression), NULL, -1, yylineno);
                                                        emitQuad(sub, (yyvsp[-2].expression), (yyvsp[-2].expression), newexpr_constint(1), -1, yylineno);
                                                }
                                                printf("term <- lvalue--  :line  %d  \n", yylineno);
                                        }
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 355 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("term <- primary  :line  %d  \n", yylineno);}
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 358 "parser.y" /* yacc.c:1646  */
    {
                                printf("lastlvalue: -- %s\n", lastlvalue);
                                if(local == 0 && (isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)){
                                        yyerror("Cannot use function as lvalue");
                                }
                                local=0;
                        }
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 364 "parser.y" /* yacc.c:1646  */
    {
                                                if((yyvsp[-3].expression)->type == tableitem_e){
                                                        emitQuad(tablesetelem, (yyvsp[-3].expression), (yyvsp[-3].expression)->index, (yyvsp[0].expression), -1, yylineno);
                                                        (yyval.expression) = emit_iftableitem(symtab, (yyvsp[-3].expression));
                                                        (yyval.expression)->type = assignexpr_e;
                                                }else{
                                                        emitQuad(assign, (yyvsp[-3].expression), (yyvsp[0].expression), NULL, -1, yylineno);
                                                        (yyval.expression) = newexpr(assignexpr_e);
                                                        (yyval.expression)->sym = newtemp(symtab);
                                                        if((yyval.expression)->sym == NULL){
                                                                printf("\nerorrrrrrrrr\n");
                                                        }
                                                        emitQuad(assign, (yyval.expression), (yyvsp[-3].expression), NULL, -1, yylineno);
                                                }
                                                printf("assignexpr <- lvalue = expr :line  %d  \n", yylineno);
                                        }
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 382 "parser.y" /* yacc.c:1646  */
    {
                                                                        (yyval.expression) = emit_iftableitem(symtab, (yyvsp[0].expression));
                                                                        printf("primary <- lvalue :line  %d  \n", yylineno);
                                                                }
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 386 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("primary <- call :line  %d  \n", yylineno);}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 387 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("primary <- objectdef :line  %d  \n", yylineno);}
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 388 "parser.y" /* yacc.c:1646  */
    {
                                                                        (yyval.expression) = newexpr(programfunc_e);
                                                                        (yyval.expression)->sym = (yyvsp[-1].symbol);

                                                                        printf("primary <- ( funcdef ) :line  %d  \n", yylineno);
                                                                }
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 394 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("primary <- const :line  %d  \n", yylineno);}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 397 "parser.y" /* yacc.c:1646  */
    {
                                        lastlvalue = strdup(yytext);
                                        SymbolTableEntry* sym;
                                        if(GlobalScope == 0){
                                                sym = insert(symtab, yytext, 0, yylineno, GLOBAL, currscopeoffset(), currscopespace());
                                                incurrscopeoffset();
                                                (yyval.expression) = lvalue_expr(sym);
                                                /*sym = RetLookup(yytext,0);
                                                if(sym == NULL){
                                                        sym = insert(symtab, yytext, 0, yylineno, GLOBAL, currscopeoffset(), currscopespace());
                                                        incurrscopeoffset();
                                                }
                                                $$ = lvalue_expr(sym);*/
                                        }else{
                                                sym =  insert(symtab, yytext, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
                                                incurrscopeoffset();
                                                (yyval.expression) = lvalue_expr(sym);
                                                /*sym = RetLookup(yytext,GlobalScope);
                                                if(sym == NULL){
                                                        sym =  insert(symtab, yytext, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
                                                        incurrscopeoffset();
                                                }
                                                $$ = lvalue_expr(sym);*/
                                        }
                                        if(GlobalScope>0 && inFunct>0){
                                                local=1;
                                        }
                                        printf("lvalue <- ID :line  %d  \n", yylineno);
                                }
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 426 "parser.y" /* yacc.c:1646  */
    {local=1;}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 426 "parser.y" /* yacc.c:1646  */
    {
                                                SymbolTableEntry* sym;
                                                if(GlobalScope == 0){
                                                        sym = RetLookupInScope(yytext,0);
                                                        if(sym == NULL){
                                                                sym = insert(symtab, yytext, 0, yylineno, GLOBAL, currscopeoffset(), currscopespace());
                                                                incurrscopeoffset();
                                                        }
                                                        (yyval.expression) = lvalue_expr(sym);
                                                }else{
                                                        sym = RetLookupInScope(yytext,GlobalScope);
                                                        if(sym == NULL){
                                                                localspecified=1;
                                                                sym = insert(symtab, yytext, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
                                                                localspecified = 0;
                                                                incurrscopeoffset();
                                                        }
                                                        (yyval.expression) = lvalue_expr(sym);
                                                }
                                                printf("lvalue <- LOCAL ID :line  %d  \n", yylineno);
                                        }
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 447 "parser.y" /* yacc.c:1646  */
    {
                                        SymbolTableEntry* sym;
                                        if(!lookupInScope(yytext, 0)){
                                                yyerror("Error : ID not found globaly");
                                        }
                                        sym = RetLookupInScope(yytext, 0);
                                        (yyval.expression) = lvalue_expr(sym);
                                        printf("lvalue <- :: ID :line  %d  \n", yylineno);
                                }
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("lvalue <- member :line  %d  \n", yylineno);}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 459 "parser.y" /* yacc.c:1646  */
    {
                                                                lastlvalue = strdup(yytext);

                                                                (yyval.expression) = member_item(symtab, (yyvsp[-2].expression), yylval.id);

                                                                printf("member <- lvalue.ID :line  %d  \n", yylineno);
                                                        }
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 466 "parser.y" /* yacc.c:1646  */
    {
                                                                (yyvsp[-3].expression) = emit_iftableitem(symtab, (yyvsp[-3].expression));
                                                                (yyval.expression) = newexpr(tableitem_e);
                                                                (yyval.expression)->sym = (yyvsp[-3].expression)->sym;
                                                                (yyval.expression)->index = (yyvsp[-1].expression);

                                                                printf("member <- lvalue[expr] :line  %d  \n", yylineno);
                                                        }
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 474 "parser.y" /* yacc.c:1646  */
    {
                                lastlvalue = strdup(yytext);
                                
                                (yyval.expression) = member_item(symtab, (yyvsp[-2].expression), yylval.id);

                                printf("member <- call.ID :line  %d  \n", yylineno);
                                }
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 481 "parser.y" /* yacc.c:1646  */
    {printf("member <- call[expr] :line  %d  \n", yylineno);}
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 484 "parser.y" /* yacc.c:1646  */
    {
                                                                                                        (yyval.expression) = make_call(symtab,(yyvsp[-3].expression), (yyvsp[-1].expression));

                                                                                                        printf("call <- call ( elist ) :line  %d  \n", yylineno);
                                                                                                }
#line 2216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 489 "parser.y" /* yacc.c:1646  */
    {isCalledFunc = 1;}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 489 "parser.y" /* yacc.c:1646  */
    {       
                                                                                                        isCalledFunc=0;
                                                                                                        
                                                                                                        (yyvsp[-2].expression) = emit_iftableitem(symtab, (yyvsp[-2].expression));
                                                                                                        if((yyvsp[0].s_call)->method){
                                                                                                                expr* t = (yyvsp[-2].expression);
                                                                                                                (yyvsp[-2].expression) = emit_iftableitem(symtab, member_item(symtab, t, (yyvsp[0].s_call)->name));
                                                                                                                
                                                                                                                t->next = (yyvsp[0].s_call)->elist;
                                                                                                                (yyvsp[0].s_call)->elist = t;
                                                                                                        }
                                                                                                        
                                                                                                        (yyval.expression) = make_call(symtab, (yyvsp[-2].expression), (yyvsp[0].s_call)->elist);

                                                                                                        printf("call <- lvalue callsuffix :line  %d  \n", yylineno);
                                                                                                }
#line 2243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 505 "parser.y" /* yacc.c:1646  */
    {
                                                                                                        expr* func = newexpr(programfunc_e);
                                                                                                        func->sym = (yyvsp[-4].symbol);
                                                                                                        (yyval.expression) = make_call(symtab,func, (yyvsp[-1].expression));

                                                                                                        printf("call <- ( funcdef ) ( elist ) :line  %d  \n", yylineno);
                                                                                                }
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 514 "parser.y" /* yacc.c:1646  */
    {(yyval.s_call) = (yyvsp[0].s_call); printf("callsuffix <- normcall :line  %d  \n", yylineno);}
#line 2261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 515 "parser.y" /* yacc.c:1646  */
    {(yyval.s_call) = (yyvsp[0].s_call); printf("callsuffix <- methodcall :line  %d  \n", yylineno);}
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 518 "parser.y" /* yacc.c:1646  */
    {
                                                                        (yyval.s_call) = (call_t *)malloc(sizeof(call_t));
                                                                        (yyval.s_call)->elist = (yyvsp[-1].expression);
                                                                        (yyval.s_call)->method = 0;
                                                                        (yyval.s_call)->name = NULL;

                                                                        printf("normcall <- ( elist ) :line  %d  \n", yylineno);
                                                                }
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 528 "parser.y" /* yacc.c:1646  */
    {
                                                                                (yyval.s_call) = (call_t *)malloc(sizeof(call_t));
                                                                                (yyval.s_call)->elist = (yyvsp[-1].expression);
                                                                                (yyval.s_call)->method = 1;
                                                                                (yyval.s_call)->name = (yyvsp[-3].id);

                                                                                printf("methodcall <- ..ID(elist) :line  %d  \n", yylineno);
                                                                        }
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 538 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); (yyval.expression)->next = (yyvsp[0].expression); printf("elist <- expr elists :line  %d  \n", yylineno);}
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 539 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = NULL; printf("elist <- empty :line  %d  \n", yylineno);}
#line 2305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 542 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); (yyval.expression)->next = (yyvsp[0].expression); printf("elists <- COMMA expr elists :line  %d  \n", yylineno);}
#line 2311 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 543 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = NULL; printf("elist <- empty :line  %d  \n", yylineno);}
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 546 "parser.y" /* yacc.c:1646  */
    {
                                                                expr* t = newexpr(newtable_e);
                                                                t->sym = newtemp(symtab);
                                                                emitQuad(tablecreate, NULL, t, NULL, -1, yylineno);
                                                                int i;
                                                                for(i=0; (yyvsp[-1].expression); (yyvsp[-1].expression) = (yyvsp[-1].expression)->next){
                                                                        emitQuad(tablesetelem, t, newexpr_constint(i++), (yyvsp[-1].expression), -1, yylineno);
                                                                }
                                                                (yyval.expression) = t;

                                                                printf("objectdef <- [elist] :line  %d  \n", yylineno);
                                                        }
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 558 "parser.y" /* yacc.c:1646  */
    {
                                                                expr* t = newexpr(newtable_e);
                                                                t->sym = newtemp(symtab);
                                                                emitQuad(tablecreate, t, NULL, NULL, -1, yylineno);
                                                                
                                                                expr *tmp = (yyvsp[-1].expression);
                                                                while(tmp!=NULL){
                                                                        emitQuad(tablesetelem, t, tmp->index, tmp, -1, yylineno);
                                                                        tmp = tmp->next;
                                                                }
                                                                
                                                                (yyval.expression) = t;

                                                                printf("objectdef <- [indexed] :line  %d  \n", yylineno);
                                                        }
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 575 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); (yyval.expression)->next = (yyvsp[0].expression); printf("indexed <- indexedelem indexeds :line  %d  \n", yylineno);}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 578 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); (yyval.expression)->next = (yyvsp[0].expression); printf("indexeds <- ,indexedelem indexeds :line  %d  \n", yylineno);}
#line 2366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 579 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = NULL; printf("indexeds <- empty :line  %d  \n", yylineno);}
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 582 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[-1].expression); (yyval.expression)->index = (yyvsp[-3].expression); printf("indexedelem <- { expr:expr } :line  %d  \n", yylineno);}
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 585 "parser.y" /* yacc.c:1646  */
    {
                                if(comingFromFuncdef==0){
                                        GlobalScope++;
                                }else if(lastCurlyUsed == E_ELSE || lastCurlyUsed == E_IF || lastCurlyUsed == E_LOOP){
                                        GlobalScope++;
                                }
                        }
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 591 "parser.y" /* yacc.c:1646  */
    {
                                                                hide(GlobalScope); 
                                                                GlobalScope--;
                                                                if(inFunct > 0 && lastCurlyUsed == E_FUNCTION) // ALLAGI
                                                                inFunct--;
                                                                else if(inIF>0 &&  lastCurlyUsed == E_FUNCTION)
                                                                inIF--;
                                                                else if(inELSE>0 && lastCurlyUsed == E_ELSE)
                                                                inELSE--;
                                                                else if(inLoop>0 && lastCurlyUsed == E_LOOP)
                                                                inLoop--;
                                                                comingFromFuncdef=0;
                                                                printf("block <- { statements stmt } :line  %d  \n", yylineno);
                                                        }
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 605 "parser.y" /* yacc.c:1646  */
    {      hide(GlobalScope);
                                        GlobalScope--;
                                        if(inFunct > 0 && lastCurlyUsed == E_FUNCTION) // ALLAGI
                                                inFunct--;
                                        else if(inIF>0 &&  lastCurlyUsed == E_FUNCTION)
                                                inIF--;
                                        else if(inELSE>0 && lastCurlyUsed == E_ELSE)
                                                inELSE--;
                                        else if(inLoop>0 && lastCurlyUsed == E_LOOP)
                                                inLoop--;
                                        comingFromFuncdef=0;
                                        printf("block <- { } :line %d  \n", yylineno);
                                }
#line 2427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 620 "parser.y" /* yacc.c:1646  */
    {
                                                exitscopespace();
                                                (yyvsp[-2].symbol)->totalLocals = (yyvsp[0].intNum);
                                                /* int offset= pop_and_top(scopeoffsetStack); */
                                                /* restorecurrscopeoffset(offset); */
                                                (yyval.symbol) = (yyvsp[-2].symbol);
                                                expr *tmp = (expr *)malloc(sizeof(expr));
                                                tmp = newexpr(programfunc_e);
                                                tmp->sym = (yyval.symbol);
                                                if(topFuncStack(funcStackRoot) > 0){
                                                        patchRetList(popFuncStack(&funcStackRoot), nextquadlabel());
                                                }
                                                emitQuad(funcend, NULL, tmp, NULL, -1, yylineno);
                                                patchJumpBeforeFuncStrt(nextquadlabel()); // NEWSTUFF
                                        }
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 637 "parser.y" /* yacc.c:1646  */
    {
                                        pushFuncStack(&funcStackRoot, nextquadlabel());
                                        (yyval.symbol) = insert(symtab, yytext, GlobalScope, yylineno, USERFUNC, currscopeoffset(), currscopespace());
                                        /* $$->iadress = nextquadlabel(); */
                                        expr *tmp = (expr *)malloc(sizeof(expr));
                                        tmp = newexpr(programfunc_e);
                                        tmp->sym = (yyval.symbol);

                                        // NEWSTUFF
                                        topJumpsArray = nextquadlabel();
                                        jumpsarray[topJumpsArray] = -1;
                                        emitQuad(jump, NULL, NULL, NULL, -1, yylineno);

                                        emitQuad(funcstart, NULL, tmp, NULL, -1, yylineno);
                                        /* push(scopeoffsetStack, currscopeoffset()); */
                                        enterscopespace();
                                        resetformalargoffset();
                                }
#line 2470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 655 "parser.y" /* yacc.c:1646  */
    {
                                        pushFuncStack(&funcStackRoot, nextquadlabel());
                                        (yyval.symbol) = insert(symtab, "", GlobalScope, yylineno, USERFUNC, currscopeoffset(), currscopespace());
                                        expr *tmp = (expr *)malloc(sizeof(expr));
                                        tmp = newexpr(programfunc_e);
                                        tmp->sym = (yyval.symbol);

                                        // NEWSTUFF
                                        topJumpsArray = nextquadlabel(); 
                                        jumpsarray[topJumpsArray] = -1;
                                        emitQuad(jump, NULL, NULL, NULL, -1, yylineno);

                                        
                                        /*$$->iadress = nextquadlabel();*/
                                        emitQuad(funcstart, NULL, tmp, NULL, -1, yylineno);
                                        /* push(scopeoffsetStack, currscopeoffset()); */
                                        enterscopespace();
                                        resetformalargoffset();
                                }
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 676 "parser.y" /* yacc.c:1646  */
    {       GlobalScope++;
                                        inFunct++;
                                        comingFromFuncdef=1;
                                        lastCurlyUsed = E_FUNCTION;
                                }
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 681 "parser.y" /* yacc.c:1646  */
    {
                                                                        enterscopespace();
                                                                        resetfuntionlocalsoffset();
                                                                }
#line 2513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 686 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.intNum) = currscopeoffset();
                                        exitscopespace();
                                        
                                        printf("funcdef <- FUNCTION (idlist) block :line  %d  \n", yylineno);
                                }
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 694 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = (yyvsp[0].expression); printf("const <- number :line  %d  \n", yylineno);}
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 695 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_conststring(yylval.id); printf("const <- STRING :line  %d  \n", yylineno);}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 696 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_constsnill(); printf("const <- NIL :line  %d  \n", yylineno);}
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 697 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_constbool(1); printf("const <- TRUE :line  %d  \n", yylineno);}
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 698 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_constbool(0); printf("const <- FALSE :line  %d  \n", yylineno);}
#line 2554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 701 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_constint(yylval.intNum); printf("number <- INTCONST :line  %d  \n", yylineno);}
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 702 "parser.y" /* yacc.c:1646  */
    {(yyval.expression) = newexpr_constreal(yylval.doubleNum); printf("number <- REALCONST :line  %d  \n", yylineno);}
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 705 "parser.y" /* yacc.c:1646  */
    {
                                if(inFunct>0){
                                        insert(symtab, yytext, GlobalScope, yylineno, FORMAL, currscopeoffset(), currscopespace()); insertFuncArgs(symtab, yytext, GlobalScope);
                                        } 
                                }
#line 2576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 710 "parser.y" /* yacc.c:1646  */
    {printf("idlist <- ID idlists :line  %d  \n", yylineno);}
#line 2582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 711 "parser.y" /* yacc.c:1646  */
    {printf("idlist <- empty :line  %d  \n", yylineno);}
#line 2588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 714 "parser.y" /* yacc.c:1646  */
    {if(inFunct>0) {insert(symtab, yytext, GlobalScope, yylineno, FORMAL, currscopeoffset(), currscopespace()); insertFuncArgs(symtab, yytext, GlobalScope);} }
#line 2594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 714 "parser.y" /* yacc.c:1646  */
    {printf("idlists <- ,ID idlists :line  %d  \n", yylineno);}
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 715 "parser.y" /* yacc.c:1646  */
    {printf("idlists <- empty :line  %d  \n", yylineno);}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 718 "parser.y" /* yacc.c:1646  */
    {patchlabel((yyval.intNum), nextquadlabel()); printf("if(expr) stmt :line  %d  \n", yylineno);}
#line 2612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 719 "parser.y" /* yacc.c:1646  */
    {
                                                                patchlabel((yyvsp[-3].intNum), (yyvsp[-1].intNum)+1);
                                                                patchlabel((yyvsp[-1].intNum), nextquadlabel());
                                                                printf("if(expr) stmt else stmt :line  %d  \n", yylineno);
                                                        }
#line 2622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 726 "parser.y" /* yacc.c:1646  */
    {
                                                                inIF++;
                                                                lastCurlyUsed = E_IF; /* ALLAGI */
                                                                emitQuad(if_eq,NULL, (yyvsp[-1].expression), newexpr_constbool(1), nextquadlabel()+2, yylineno);
                                                                (yyval.intNum) = nextquadlabel();
                                                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        }
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 735 "parser.y" /* yacc.c:1646  */
    {
                                inELSE++;
                                lastCurlyUsed = E_ELSE; /* ALLAGI */
                                (yyval.intNum) = nextquadlabel();
                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                        }
#line 2645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 743 "parser.y" /* yacc.c:1646  */
    {
                                                        emitQuad(jump, NULL, NULL, NULL, (yyvsp[-2].intNum), yylineno);
                                                        patchlabel((yyvsp[-1].intNum), nextquadlabel());
                                                        patchBrContList((yyvsp[-2].intNum), nextquadlabel());

                                                        printf("whilestmt <- while(expr) stmt :line  %d  \n", yylineno);
                                                }
#line 2657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 752 "parser.y" /* yacc.c:1646  */
    {(yyval.intNum) = nextquadlabel();}
#line 2663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 755 "parser.y" /* yacc.c:1646  */
    {
                                                                emitQuad(if_eq, NULL, (yyvsp[-1].expression), newexpr_constbool(1), nextquadlabel()+2, yylineno);
                                                                (yyval.intNum) = nextquadlabel();
                                                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                                inLoop++; lastCurlyUsed = E_LOOP; /* ALLAGI */
                                                        }
#line 2674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 763 "parser.y" /* yacc.c:1646  */
    {       inLoop++;
                                                        lastCurlyUsed = E_LOOP; /* ALLAGI */
                                                }
#line 2682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 766 "parser.y" /* yacc.c:1646  */
    {
                                                                        patchlabel((yyvsp[-7].forpref)->enter, (yyvsp[-2].intNum)+1);
                                                                        patchlabel((yyvsp[-6].intNum), nextquadlabel());
                                                                        patchlabel((yyvsp[-2].intNum), (yyvsp[-7].forpref)->test);
                                                                        patchlabel((yyvsp[0].intNum), (yyvsp[-6].intNum)+1);

                                                                        patchBrContList((yyvsp[-6].intNum)+1, nextquadlabel());
                                                                        printf("for(elist;expr;elist) stmt :line  %d  \n", yylineno);
                                                                }
#line 2696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 777 "parser.y" /* yacc.c:1646  */
    {
                                                                                (yyval.forpref) = (struct forstruct *) malloc (sizeof(forstruct));
                                                                                (yyval.forpref)->test = (yyvsp[-2].intNum);
                                                                                (yyval.forpref)->enter = nextquadlabel();
                                                                                emitQuad(if_eq, NULL, (yyvsp[-1].expression), newexpr_constbool(1), 0, yylineno);
                                                                        }
#line 2707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 785 "parser.y" /* yacc.c:1646  */
    {(yyval.intNum) = nextquadlabel(); emitQuad(jump, NULL, NULL, NULL, 0, yylineno);}
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 788 "parser.y" /* yacc.c:1646  */
    {(yyval.intNum) = nextquadlabel();}
#line 2719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 791 "parser.y" /* yacc.c:1646  */
    {
                                if(inFunct == 0 ||/* ALLAGI */ GlobalScope==0){
                                        yyerror("Cannot return when not in Function.");
                                }
                        }
#line 2729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 795 "parser.y" /* yacc.c:1646  */
    {
                                                        emitQuad(ret, (yyvsp[-1].expression), NULL, NULL, -1, yylineno);
                                                        insertRetList(nextquadlabel(), 0);
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("returnstmt <- return expr; :line  %d  \n", yylineno);
                                                }
#line 2740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 801 "parser.y" /* yacc.c:1646  */
    {
                                if(inFunct == 0 ||/* ALLAGI */ GlobalScope==0){
                                        yyerror("Cannot return when not in Function.");
                                }
                        }
#line 2750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 805 "parser.y" /* yacc.c:1646  */
    {
                                                        emitQuad(ret, NULL, NULL, NULL, -1, yylineno);
                                                        insertRetList(nextquadlabel(), 0);
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("returnstmt <- return; :line  %d  \n", yylineno);
                                                }
#line 2761 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2765 "y.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 813 "parser.y" /* yacc.c:1906  */



int yyerror (char* yaccProvideMessage){
        if(strcmp(yaccProvideMessage,"Cannot use function as lvalue")==0){
                fprintf(stderr, "\033[1;31mCannot use function \"%s\" as lvalue at :line %d\033[0m\n",lastlvalue,yylineno);
        }else if(strcmp(yaccProvideMessage,"syntax error")==0){
                fprintf(stderr, "\033[1;31mGrammar Error : Function call \"%s\" is not lvalue at :line %d\033[0m\n",lastlvalue,yylineno);
        }else{
                fprintf(stderr, "\033[1;31m%s \"%s\" at :line %d\033[0m\n",yaccProvideMessage,yytext,yylineno);
        }
        exit(EXIT_FAILURE);
}


int main(){
        stack = (struct Stack*)createStack(STACK_SIZE);
        symtab = SymTable_new();
        emitFirstDummyQuad();
        yyparse();
        printSymbolTable();
        PrintListOfArgs(symtab);
        printf("\033[1;31m------------------------------PhaseC------------------------------\033[0m\n");
        printf("\033[1;31m                        (Intermediate Code)\033[0m\n");
        printQuads();
        
        printf("\033[1;31m------------------------------PhaseD------------------------------\033[0m\n");
        printf("\033[1;31m                     (Target Code Generation)\033[0m\n");
        generate_gen();
        patchdemjumps();
        printInstructions();
        printBinary();
}
