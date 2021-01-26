/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

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

#include "visitor/AstNodeVisitor.hpp"
#include "AST/AstDumper.hpp"
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

struct _id{
	char * name;
	int i,j;
};

struct _type{
	int scalartype;
	std::vector<int> *arr;
};

struct _constant{
	int intconstant; // type=0
	double doubleconstant;  // type=1
	char * str;  // type=2
	int type;
};

struct _argulist{
	AstNode *node;
	std::vector<int> *arr;
};

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static AstNode *root;
static AstDumper vi;


extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

#line 145 "parser.cpp" /* yacc.c:339  */

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
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 80 "parser.y" /* yacc.c:355  */

    class AstNode;

#line 179 "parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    SEMICOLON = 259,
    COLON = 260,
    L_PARENTHESIS = 261,
    R_PARENTHESIS = 262,
    L_BRACKET = 263,
    R_BRACKET = 264,
    ASSIGN = 265,
    OR = 266,
    AND = 267,
    NOT = 268,
    LESS = 269,
    LESS_OR_EQUAL = 270,
    EQUAL = 271,
    GREATER = 272,
    GREATER_OR_EQUAL = 273,
    NOT_EQUAL = 274,
    PLUS = 275,
    MINUS = 276,
    MULTIPLY = 277,
    DIVIDE = 278,
    MOD = 279,
    UNARY_MINUS = 280,
    ARRAY = 281,
    BOOLEAN = 282,
    INTEGER = 283,
    REAL = 284,
    STRING = 285,
    END = 286,
    BEGIN_ = 287,
    DO = 288,
    ELSE = 289,
    FOR = 290,
    IF = 291,
    THEN = 292,
    WHILE = 293,
    DEF = 294,
    OF = 295,
    TO = 296,
    RETURN = 297,
    VAR = 298,
    FALSE = 299,
    TRUE = 300,
    PRINT = 301,
    READ = 302,
    ID = 303,
    INT_LITERAL = 304,
    REAL_LITERAL = 305,
    STRING_LITERAL = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 85 "parser.y" /* yacc.c:355  */

    /* basic semantic value */
    char *identifier;
    int intvalue;
	double doublevalue;
	std::vector<_id> *list;
	std::vector<_type> *typelist;
	std::vector<_argulist> *arglist;
	std::vector<AstNode *> *li;
    AstNode *node;
	_type ty;
	_constant con;
	_argulist arg;

#line 258 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 289 "parser.cpp" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   148,   148,   171,   175,   179,   188,   193,   203,   207,
     216,   221,   231,   233,   237,   256,   278,   282,   286,   295,
     300,   310,   342,   349,   362,   366,   376,   394,   440,   445,
     451,   453,   455,   457,   461,   468,   473,   480,   487,   492,
     499,   503,   509,   514,   520,   528,   533,   544,   546,   548,
     550,   552,   554,   556,   560,   579,   585,   593,   601,   615,
     619,   629,   638,   651,   661,   664,   668,   676,   699,   705,
     709,   722,   726,   735,   740,   751,   755,   764,   769,   780,
     782,   789,   796,   803,   810,   817,   824,   831,   838,   845,
     852,   859,   866,   873,   880,   887,   897,   902,   906,   912
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMA", "SEMICOLON", "COLON",
  "L_PARENTHESIS", "R_PARENTHESIS", "L_BRACKET", "R_BRACKET", "ASSIGN",
  "OR", "AND", "NOT", "LESS", "LESS_OR_EQUAL", "EQUAL", "GREATER",
  "GREATER_OR_EQUAL", "NOT_EQUAL", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MOD", "UNARY_MINUS", "ARRAY", "BOOLEAN", "INTEGER", "REAL", "STRING",
  "END", "BEGIN_", "DO", "ELSE", "FOR", "IF", "THEN", "WHILE", "DEF", "OF",
  "TO", "RETURN", "VAR", "FALSE", "TRUE", "PRINT", "READ", "ID",
  "INT_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "$accept", "Program",
  "ProgramName", "DeclarationList", "Declarations", "FunctionList",
  "Functions", "Function", "FunctionDeclaration", "FunctionDefinition",
  "FunctionName", "FormalArgList", "FormalArgs", "FormalArg", "IdList",
  "ReturnType", "Declaration", "Type", "ScalarType", "ArrType", "ArrDecl",
  "LiteralConstant", "NegOrNot", "StringAndBoolean", "IntegerAndReal",
  "Statement", "CompoundStatement", "Simple", "VariableReference",
  "ArrRefList", "ArrRefs", "Condition", "ElseOrNot", "While", "For",
  "Return", "FunctionCall", "FunctionInvocation", "ExpressionList",
  "Expressions", "StatementList", "Statements", "Expression", "Epsilon", YY_NULLPTR
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
     305,   306
};
# endif

#define YYPACT_NINF -60

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-60)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,   -60,    35,    33,   -60,    -5,    -9,    -7,    -5,   -60,
     -60,   -60,    10,   -60,    16,    -7,   -60,   -60,   -60,    52,
     -60,   -60,    11,    59,    -5,    45,   -60,    -9,   -60,   -60,
      28,   -60,   -60,   -60,   -60,   -60,   -60,   -60,    74,   -60,
     -60,    27,    75,   -30,   -60,   -60,    70,   -60,    76,    77,
     -60,    13,   -60,    42,   -60,    41,   -60,   -60,   -60,   -60,
      43,     1,     1,     1,     1,    44,    24,   -60,   -60,   -60,
      84,   -60,   -60,   -60,   -60,   -60,    92,    67,    70,   -60,
      94,    -9,   122,   -60,    60,    91,     1,     1,     1,   -60,
     -60,   -60,   -60,   -60,   -60,   110,   155,   178,   199,   101,
     107,     1,     1,   -60,   105,   -60,     1,   -60,   -60,   -60,
      -4,     4,   -60,   -60,   -60,   -60,    65,   238,   121,   -60,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,    16,    16,   -60,   -60,   -60,   108,   120,
     284,   -60,   254,     1,   220,   -60,   -60,   115,   112,   -60,
     297,   121,   139,   139,   139,   139,   139,   139,   -13,   -13,
     -60,   -60,   -60,   130,   123,   -60,     1,   -60,   270,   -60,
     -60,   106,    16,   125,   -60,   132,   284,   -60,   147,   -60,
     145,   -60,    16,   -60,   152,   151,   -60
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,    99,     0,    99,     5,     6,
       4,    22,     0,    16,     0,     9,    10,    12,    13,     0,
       8,     7,     0,    99,    99,     0,    11,    99,    23,    41,
       0,    33,    30,    31,    32,    44,    43,    42,     0,    28,
      29,     0,     0,     0,    39,    40,    99,     2,     0,    18,
      19,     0,    17,     0,    26,     0,    34,    27,    37,    38,
       0,     0,     0,     0,     0,     0,    99,    77,    47,    48,
       0,    49,    50,    51,    52,    53,     0,     0,    76,    75,
      99,     0,     0,    35,     0,     0,     0,     0,     0,    45,
      46,    96,    95,    97,    98,     0,     0,     0,     0,    99,
       0,    99,     0,    58,    60,    59,     0,    69,    54,    78,
       0,     0,    25,    20,    21,    36,     0,     0,    92,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,    56,    57,     0,    72,
      73,    71,     0,     0,     0,    24,    14,     0,     0,    79,
      94,    93,    86,    87,    90,    88,    89,    91,    84,    85,
      81,    82,    83,    99,     0,    70,     0,    61,     0,    55,
      15,     0,     0,     0,    65,     0,    74,    62,     0,    64,
       0,    66,     0,    63,     0,     0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   161,   -60,   -60,   -60,   171,   -60,   -60,
     -60,   -60,   -60,   124,   181,   -60,   183,   126,   -35,   -60,
     -60,   -60,   -60,   184,   -60,   128,   -14,   -60,   -34,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -44,   -60,   -60,
     -60,   -60,   -59,    -6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    14,    15,    16,    17,    18,
      19,    48,    49,    50,    51,   111,     9,    38,    39,    40,
      41,    42,    43,    91,    92,    67,    68,    69,    93,   103,
     104,    71,   173,    72,    73,    74,    75,    94,   138,   139,
      77,    78,    95,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    20,    76,    96,    97,    98,    56,    86,   146,   130,
     131,   132,    70,    22,    87,    23,    22,    45,    82,    58,
      59,    52,    88,    31,    32,    33,    34,   117,   118,   119,
     101,   100,   102,     1,    76,     4,    24,     5,     6,    11,
      79,    13,   140,   142,    70,    35,    36,   144,    24,    66,
      89,    90,    37,    55,    31,    32,    33,    34,    27,    28,
     105,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   112,   145,    47,    53,    54,    57,
      29,    81,    83,    80,   168,    30,    31,    32,    33,    34,
      84,    85,    99,   105,   106,   141,   107,   147,   108,   110,
     115,   116,    24,    35,    36,    60,    61,   176,    62,   102,
      37,   137,    63,   143,   148,   165,    64,    65,    66,   163,
     164,   120,   121,   166,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   170,   133,    30,    31,
      32,    33,    34,   171,   175,   178,   180,   174,   179,   128,
     129,   130,   131,   132,   172,   181,   120,   121,   184,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     182,   183,   135,   185,   186,    46,    26,    12,   134,   120,
     121,    21,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   136,     0,   113,   109,    44,   114,     0,
     120,   121,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   169,     0,     0,     0,     0,     0,
       0,   120,   121,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   149,     0,     0,     0,   120,
     121,     0,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   167,     0,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   177,
       0,   120,   121,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   121,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132
};

static const yytype_int16 yycheck[] =
{
      14,     7,    46,    62,    63,    64,    41,     6,     4,    22,
      23,    24,    46,     3,    13,     5,     3,    23,     5,    49,
      50,    27,    21,    27,    28,    29,    30,    86,    87,    88,
       6,    65,     8,    48,    78,     0,    32,     4,    43,    48,
      46,    48,   101,   102,    78,    44,    45,   106,    32,    48,
      49,    50,    51,    26,    27,    28,    29,    30,     6,    48,
      66,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,    80,   110,    31,    49,     4,     4,
      21,     4,    40,     7,   143,    26,    27,    28,    29,    30,
      49,    48,    48,    99,    10,   101,     4,   111,    31,     5,
      40,    10,    32,    44,    45,    35,    36,   166,    38,     8,
      51,     4,    42,     8,    49,     7,    46,    47,    48,   133,
     134,    11,    12,     3,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    31,    37,    26,    27,
      28,    29,    30,    41,    31,    49,    31,   163,   172,    20,
      21,    22,    23,    24,    34,    33,    11,    12,   182,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      33,    36,     4,    31,    33,    24,    15,     6,    33,    11,
      12,     8,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     4,    -1,    81,    78,    23,    82,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     7,    -1,    -1,    -1,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     9,    -1,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     9,
      -1,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    53,    54,     0,     4,    43,    55,    56,    68,
      95,    48,    66,    48,    57,    58,    59,    60,    61,    62,
      95,    68,     3,     5,    32,    78,    59,     6,    48,    21,
      26,    27,    28,    29,    30,    44,    45,    51,    69,    70,
      71,    72,    73,    74,    75,    95,    55,    31,    63,    64,
      65,    66,    95,    49,     4,    26,    70,     4,    49,    50,
      35,    36,    38,    42,    46,    47,    48,    77,    78,    79,
      80,    83,    85,    86,    87,    88,    89,    92,    93,    95,
       7,     4,     5,    40,    49,    48,     6,    13,    21,    49,
      50,    75,    76,    80,    89,    94,    94,    94,    94,    48,
      80,     6,     8,    81,    82,    95,    10,     4,    31,    77,
       5,    67,    95,    65,    69,    40,    10,    94,    94,    94,
      11,    12,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    37,    33,     4,     4,     4,    90,    91,
      94,    95,    94,     8,    94,    70,     4,    78,    49,     7,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    78,    78,     7,     3,     9,    94,     4,
      31,    41,    34,    84,    95,    31,    94,     9,    49,    78,
      31,    33,    33,    36,    78,    31,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    61,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    71,    72,    72,    73,    73,    73,
      74,    74,    75,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    79,    79,    80,    81,
      81,    82,    82,    83,    84,    84,    85,    86,    87,    88,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     6,     7,     1,     1,     1,     1,
       3,     3,     1,     3,     2,     1,     5,     5,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     3,     3,     2,     1,
       1,     3,     4,     7,     2,     1,     6,    10,     3,     2,
       4,     1,     1,     1,     3,     1,     1,     1,     2,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     1,     1,     1,     1,     0
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 152 "parser.y" /* yacc.c:1646  */
    {
        root = new ProgramNode((yylsp[-5]).first_line, (yylsp[-5]).first_column,
                               (yyvsp[-5].identifier));       
		//free($1);
		if((yyvsp[-3].li)!=NULL){
			for(auto i: *((yyvsp[-3].li))){
				root->add_child(i);
			}
		}
		if((yyvsp[-2].li)!=NULL){
			for(auto i: *((yyvsp[-2].li))){
				root->add_child(i);
			}
		}
		root->add_child((yyvsp[-1].node));
    }
#line 1642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 175 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=NULL;
	}
#line 1650 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 179 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[0].li))){
			(yyval.li)->push_back(i);
		}
	}
#line 1661 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 188 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 1670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 193 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[-1].li))){
			(yyval.li)->push_back(i);
		}
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 203 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=NULL;
	}
#line 1690 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 207 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[0].li))){
			(yyval.li)->push_back(i);
		}
	}
#line 1701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 216 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 1710 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 221 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[-1].li))){
			(yyval.li)->push_back(i);
		}
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 1722 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 237 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node)= new FunctionNode((yylsp[-5]).first_line,(yylsp[-5]).first_column,(yyvsp[-5].identifier),(yyvsp[-1].intvalue));
				
		if((yyvsp[-3].arglist)!=NULL){		
			for(auto i:*((yyvsp[-3].arglist))){
				(yyval.node)->add_de(i.node);
				//i.node->print();
				for(auto j: *(i.arr)){
					(yyval.node)->add_arg(j);
					//printf("%d\n",j);
				}
			}
			//printf("\n");
		}
		//$$->print();
	}
#line 1743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 258 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node)= new FunctionNode((yylsp[-6]).first_line,(yylsp[-6]).first_column,(yyvsp[-6].identifier),(yyvsp[-2].intvalue));
				
		if((yyvsp[-4].arglist)!=NULL){		
			for(auto i:*((yyvsp[-4].arglist))){
				(yyval.node)->add_de(i.node);
				//i.node->print();
				for(auto j: *(i.arr)){
					(yyval.node)->add_arg(j);
					//printf("%d\n",j);
				}
			}
			//printf("\n");
		}
		(yyval.node)->add_compoundstatement((yyvsp[-1].node));
		//$$->print();
	}
#line 1765 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 282 "parser.y" /* yacc.c:1646  */
    {
		(yyval.arglist)=NULL;
	}
#line 1773 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 286 "parser.y" /* yacc.c:1646  */
    {
		(yyval.arglist)=new std::vector<_argulist>;
		for(auto i : *((yyvsp[0].arglist))){
			(yyval.arglist)->push_back(i);
		}
	}
#line 1784 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 295 "parser.y" /* yacc.c:1646  */
    {
		(yyval.arglist)=new std::vector<_argulist>;
		(yyval.arglist)->push_back((yyvsp[0].arg));
	}
#line 1793 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 300 "parser.y" /* yacc.c:1646  */
    {
		(yyval.arglist)=new std::vector<_argulist>;
		for(auto i : *((yyvsp[-2].arglist))){
			(yyval.arglist)->push_back(i);
		}
		(yyval.arglist)->push_back((yyvsp[0].arg));
	}
#line 1805 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 310 "parser.y" /* yacc.c:1646  */
    {
		AstNode *ne,*ne1;
		ne = new DeclNode((yylsp[-2]).first_line,(yylsp[-2]).first_column);
		(yyval.arg).arr= new std::vector<int>;
		for(auto i: *((yyvsp[-2].list))){
			ne1= new VariableNode(i.i, i.j, i.name,(yyvsp[0].ty).scalartype,(yyvsp[0].ty).arr,0,0,NULL);		
			ne->add_child(ne1);	
			(yyval.arg).arr->push_back((yyvsp[0].ty).scalartype);
			(yyval.arg).arr->push_back(-1);
			for(auto j: *((yyvsp[0].ty).arr)){
				(yyval.arg).arr->push_back(j);				
				//printf("%d ",j);
				//printf("\n");
			}
			(yyval.arg).arr->push_back(-1);						
		}		
		//printf("\n");
		//printf("%d ",$3.scalartype);
		//for(auto i: *($3.arr)){
		//	printf(" %d",i);
		//}
		//printf("\n");
		//ne->print();		
		(yyval.arg).node=ne;
		//$$.node->print();
		//for(auto i: *($$.arr)){
		//	printf("%d\n",i);
		//}
	}
#line 1839 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 342 "parser.y" /* yacc.c:1646  */
    {
			(yyval.list)=new std::vector<_id>;
			_id a;
			a.name=(yyvsp[0].identifier); a.i=(yylsp[0]).first_line; a.j=(yylsp[0]).first_column;
			(yyval.list)->push_back(a);			
	}
#line 1850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 349 "parser.y" /* yacc.c:1646  */
    {
		(yyval.list)=new std::vector<_id>;
		for(auto i : *((yyvsp[-2].list))){
			(yyval.list)->push_back(i);
		}
		_id a;
		a.name=(yyvsp[0].identifier); a.i=(yylsp[0]).first_line; a.j=(yylsp[0]).first_column;
		(yyval.list)->push_back(a);
		//free($1);
	}
#line 1865 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 362 "parser.y" /* yacc.c:1646  */
    {
		(yyval.intvalue)=(yyvsp[0].intvalue);
	}
#line 1873 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 366 "parser.y" /* yacc.c:1646  */
    {
		(yyval.intvalue)=4;
	}
#line 1881 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 376 "parser.y" /* yacc.c:1646  */
    {			
			(yyval.node) = new DeclNode((yylsp[-4]).first_line,(yylsp[-4]).first_column);		
			AstNode *ne;
			
			for(auto i: *((yyvsp[-3].list))){
				ne= new VariableNode(i.i, i.j, i.name,(yyvsp[-1].ty).scalartype,(yyvsp[-1].ty).arr,0,0,NULL);		
				(yyval.node)->add_child(ne);		
				//std::cout << i.name << " " << i.i << " " << i.j << std::endl;			
			}
			//std::cout << $4.scalartype ;
			//for(auto i: *($4.arr)){
			//	std::cout  << " " << i;			
			//}
			//std::cout << std::endl;
			
	}
#line 1902 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 394 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = new DeclNode((yylsp[-4]).first_line,(yylsp[-4]).first_column);			
			AstNode *ne;
			AstNode *ne1;			
			for(auto i: *((yyvsp[-3].list))){
				if((yyvsp[-1].con).type==0){
					ne= new VariableNode(i.i, i.j, i.name,(yyvsp[-1].con).type,NULL,(yyvsp[-1].con).intconstant,0,NULL);
					ne1= new ConstantValueNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].con).type,(yyvsp[-1].con).intconstant,0,NULL);
					ne->add_child(ne1);
					(yyval.node)->add_child(ne);
				}
				else if((yyvsp[-1].con).type==1){
					ne= new VariableNode(i.i, i.j, i.name,(yyvsp[-1].con).type,NULL,0,(yyvsp[-1].con).doubleconstant,NULL);
					ne1= new ConstantValueNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].con).type,0,(yyvsp[-1].con).doubleconstant,NULL);
					ne->add_child(ne1);
					(yyval.node)->add_child(ne);
				}
				else if((yyvsp[-1].con).type==2){
					if(strcmp((yyvsp[-1].con).str,"true")==0||strcmp((yyvsp[-1].con).str,"false")==0){
						ne= new VariableNode(i.i, i.j, i.name,3,NULL,0,0,(yyvsp[-1].con).str);
						ne1= new ConstantValueNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,2,0,0,(yyvsp[-1].con).str);
						ne->add_child(ne1);
					}
					else{
						ne= new VariableNode(i.i, i.j, i.name,2,NULL,0,0,(yyvsp[-1].con).str);
						ne1= new ConstantValueNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,3,0,0,(yyvsp[-1].con).str);
						ne->add_child(ne1);
					}
					(yyval.node)->add_child(ne);
				}	
			}
			//if($4.type==0){
				//printf("%d %d %d\n",$4.intconstant,@4.first_line,@4.first_column);
				//std::cout << $4.intconstant << " " << @4.first_line << " " << @4.first_column << std::endl;
			//}
			//if($4.type==1){
				//printf("%f %d %d\n",$4.doubleconstant,@4.first_line,@4.first_column);
			//}
			//if($4.type==2){
				//std::cout << $4.str << " " << @4.first_line << " " << @4.first_column << std::endl;
			//}
			//std::cout << std::endl;
	}
#line 1950 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 440 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ty).scalartype=(yyvsp[0].intvalue);
		(yyval.ty).arr=new std::vector<int>;	
	}
#line 1959 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 445 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ty)=(yyvsp[0].ty);
	}
#line 1967 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 451 "parser.y" /* yacc.c:1646  */
    { (yyval.intvalue)=0;}
#line 1973 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 453 "parser.y" /* yacc.c:1646  */
    { (yyval.intvalue)=1;}
#line 1979 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 455 "parser.y" /* yacc.c:1646  */
    { (yyval.intvalue)=2;}
#line 1985 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 457 "parser.y" /* yacc.c:1646  */
    { (yyval.intvalue)=3;}
#line 1991 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 461 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ty)=(yyvsp[-1].ty);
		(yyval.ty).scalartype=(yyvsp[0].intvalue);
	}
#line 2000 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 468 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ty).arr=new std::vector<int>;
		(yyval.ty).arr->push_back((yyvsp[-1].intvalue));
	}
#line 2009 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 473 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ty)=(yyvsp[-3].ty);
		(yyval.ty).arr->push_back((yyvsp[-1].intvalue));
	}
#line 2018 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 480 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).intconstant=(yyvsp[-1].intvalue)*(yyvsp[0].intvalue);
		(yyloc).first_line=(yylsp[0]).first_line;
		(yyloc).first_column=(yylsp[0]).first_column;
		(yyval.con).type=0;
	}
#line 2029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 487 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).doubleconstant=(yyvsp[-1].intvalue)*(yyvsp[0].doublevalue);
		(yyval.con).type=1;
	}
#line 2038 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 492 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).str=(yyvsp[0].con).str;
		(yyval.con).type=2;
	}
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 499 "parser.y" /* yacc.c:1646  */
    {
		(yyval.intvalue)=1;
	}
#line 2055 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 503 "parser.y" /* yacc.c:1646  */
    {
		(yyval.intvalue)=-1;
	}
#line 2063 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 509 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).type=2;
		(yyval.con).str=(yyvsp[0].identifier);
	}
#line 2072 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 514 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).type=3;
		(yyval.con).str=(yyvsp[0].identifier);

	}
#line 2082 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 520 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).type=3;
		(yyval.con).str=(yyvsp[0].identifier);

	}
#line 2092 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 528 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).type=0;
		(yyval.con).intconstant=(yyvsp[0].intvalue);
    	}
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 533 "parser.y" /* yacc.c:1646  */
    {
		(yyval.con).type=1;
		(yyval.con).doubleconstant=(yyvsp[0].doublevalue);
	}
#line 2110 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 563 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new CompoundStatementNode((yylsp[-3]).first_line,(yylsp[-3]).first_column);
		if((yyvsp[-2].li)!=NULL){
			for(auto i: *((yyvsp[-2].li))){
				(yyval.node)->add_de(i);
			}
		}
		if((yyvsp[-1].li)!=NULL){
			for(auto i: *((yyvsp[-1].li))){
				(yyval.node)->add_st(i);
			}
		}  
	}
#line 2128 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 579 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new AssignmentNode((yylsp[-2]).first_line,(yylsp[-2]).first_column,(yyvsp[-3].node),(yyvsp[-1].node));
		//$$ -> print();
		//printf("\n");
	}
#line 2138 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 585 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].node)!=NULL){
			//$2->print();
			(yyval.node) = new PrintNode((yylsp[-2]).first_line,(yylsp[-2]).first_column,(yyvsp[-1].node));
			//$$->print();
		}
	}
#line 2150 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 593 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].node)!=NULL){
			(yyval.node)= new ReadNode((yylsp[-2]).first_line,(yylsp[-2]).first_column,(yyvsp[-1].node));
		}
	}
#line 2160 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 601 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node)= new VariableReferenceNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier));
		if((yyvsp[0].li)!=NULL){
			for(auto i : *((yyvsp[0].li))){
				//i->print();
				(yyval.node)->add_child(i);
			}
		}
		
		//$$->print();
	}
#line 2176 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 615 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=NULL;
	}
#line 2184 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 619 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[0].li))){
			(yyval.li)->push_back(i);
			//i->print();
		}
	}
#line 2196 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 629 "parser.y" /* yacc.c:1646  */
    {
		//if($2!=NULL) $2->print();
		(yyval.li)=new std::vector<AstNode *>;
		if((yyvsp[-1].node)!=NULL){
			(yyval.li)->push_back((yyvsp[-1].node));
			//$2->print();
		}	
	}
#line 2209 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 638 "parser.y" /* yacc.c:1646  */
    {
		//if($3!=NULL) $3->print();
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[-3].li))){
			(yyval.li)->push_back(i);
		}
		if((yyvsp[-1].node)!=NULL)
			(yyval.li)->push_back((yyvsp[-1].node));
			//$3->print();
	}
#line 2224 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 654 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new IfNode((yylsp[-6]).first_line,(yylsp[-6]).first_column,(yyvsp[-5].node),(yyvsp[-3].node),(yyvsp[-2].node));
		//$$->print();
	}
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 662 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node);}
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 664 "parser.y" /* yacc.c:1646  */
    {(yyval.node)=NULL;}
#line 2245 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 670 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new WhileNode((yylsp[-5]).first_line,(yylsp[-5]).first_column,(yyvsp[-4].node),(yyvsp[-2].node));
	}
#line 2253 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 678 "parser.y" /* yacc.c:1646  */
    {
		AstNode *ne,*ne1;
		ne= new DeclNode((yylsp[-8]).first_line,(yylsp[-8]).first_column); // decl
		ne1= new VariableNode((yylsp[-8]).first_line,(yylsp[-8]).first_column,(yyvsp[-8].identifier),NULL,0,0,0,NULL);  // var
		ne->add_child(ne1);
		//ne->print();
		AstNode *ne2,*ne3,*ne4;
		ne2= new VariableReferenceNode((yylsp[-8]).first_line,(yylsp[-8]).first_column,(yyvsp[-8].identifier));  // varref
		ne3 = new  ConstantValueNode((yylsp[-6]).first_line,(yylsp[-6]).first_column,0,(yyvsp[-6].intvalue),0,NULL);  // const
		ne4 = new AssignmentNode((yylsp[-7]).first_line,(yylsp[-7]).first_column,ne2,ne3); // assign
		//ne4->print();
		AstNode *ne5;
		ne5 = new ConstantValueNode((yylsp[-4]).first_line,(yylsp[-4]).first_column,0,(yyvsp[-4].intvalue),0,NULL);  // const
		//ne5->print();
		//$8->print();
		(yyval.node) = new ForNode((yylsp[-9]).first_line,(yylsp[-9]).first_column,ne,ne4,ne5,(yyvsp[-2].node));
		//$$->print();
	}
#line 2276 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 699 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new ReturnNode((yylsp[-2]).first_line,(yylsp[-2]).first_column,(yyvsp[-1].node));
	}
#line 2284 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 709 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node)=new FunctionInvocationNode((yylsp[-3]).first_line,(yylsp[-3]).first_column,(yyvsp[-3].identifier));
		if((yyvsp[-1].li)!=NULL){
			for(auto i: *((yyvsp[-1].li))){
				//i->print();
				(yyval.node)->add_child(i);
			}
		}
		//$$->print();
	}
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 722 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=NULL;
	}
#line 2307 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 726 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[0].li))){
			(yyval.li)->push_back(i);
		}
	}
#line 2318 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 735 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 2327 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 740 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[-2].li))){
			(yyval.li)->push_back(i);
		}
		if((yyvsp[0].node)!=NULL)
			(yyval.li)->push_back((yyvsp[0].node));
	}
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 751 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=NULL;
	}
#line 2348 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 755 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[0].li))){
			(yyval.li)->push_back(i);
		}
	}
#line 2359 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 764 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		(yyval.li)->push_back((yyvsp[0].node));
	}
#line 2368 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 769 "parser.y" /* yacc.c:1646  */
    {
		(yyval.li)=new std::vector<AstNode *>;
		for(auto i : *((yyvsp[-1].li))){
			(yyval.li)->push_back(i);
		}
		if((yyvsp[0].node)!=NULL)
			(yyval.li)->push_back((yyvsp[0].node));
	}
#line 2381 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 780 "parser.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[-1].node);}
#line 2387 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 782 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].identifier)!=NULL){		
			(yyval.node) = new UnaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,"neg",(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2398 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 789 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2409 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 796 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2420 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 803 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2431 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 810 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2442 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 817 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2453 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 824 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2464 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 831 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2475 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 838 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2486 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 845 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2497 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 852 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2508 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 859 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2519 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 866 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].identifier)!=NULL){		
			(yyval.node) = new UnaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,"not",(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2530 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 873 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2541 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 880 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].node)!=NULL&&(yyvsp[0].node)!=NULL){		
			(yyval.node) = new BinaryOperatorNode((yylsp[-1]).first_line,(yylsp[-1]).first_column,(yyvsp[-1].identifier),(yyvsp[-2].node),(yyvsp[0].node));
			//$$->print();
		}		
	}
#line 2552 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 887 "parser.y" /* yacc.c:1646  */
    { 
	if((yyvsp[0].con).type==0){
		(yyval.node) = new ConstantValueNode((yylsp[0]).first_line,(yylsp[0]).first_column,(yyvsp[0].con).type,(yyvsp[0].con).intconstant,0,NULL);
	}
	else if((yyvsp[0].con).type==1){
		(yyval.node) = new ConstantValueNode((yylsp[0]).first_line,(yylsp[0]).first_column,(yyvsp[0].con).type,0,(yyvsp[0].con).doubleconstant,NULL);
	}	
		//$$->print(); 
	}
#line 2566 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 897 "parser.y" /* yacc.c:1646  */
    { 
	(yyval.node) = new ConstantValueNode((yylsp[0]).first_line,(yylsp[0]).first_column,(yyvsp[0].con).type,0,0,(yyvsp[0].con).str);	
	//$$->print();	
	}
#line 2575 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 902 "parser.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node); 
	//$1->print();
	}
#line 2583 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 906 "parser.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2589 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2593 "parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 914 "parser.y" /* yacc.c:1906  */


void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.");

    yyparse();
	

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        //root->print();
	root->accept(vi);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
