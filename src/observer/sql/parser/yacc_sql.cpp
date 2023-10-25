/* A Bison parser, made by GNU Bison 3.7.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 115 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_INNER = 33,                     /* INNER  */
  YYSYMBOL_JOIN = 34,                      /* JOIN  */
  YYSYMBOL_WHERE = 35,                     /* WHERE  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_SET = 37,                       /* SET  */
  YYSYMBOL_ON = 38,                        /* ON  */
  YYSYMBOL_LOAD = 39,                      /* LOAD  */
  YYSYMBOL_DATA = 40,                      /* DATA  */
  YYSYMBOL_INFILE = 41,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 42,                   /* EXPLAIN  */
  YYSYMBOL_NOT = 43,                       /* NOT  */
  YYSYMBOL_LIKE = 44,                      /* LIKE  */
  YYSYMBOL_MAX = 45,                       /* MAX  */
  YYSYMBOL_MIN = 46,                       /* MIN  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_AVG = 48,                       /* AVG  */
  YYSYMBOL_SUM = 49,                       /* SUM  */
  YYSYMBOL_EQ = 50,                        /* EQ  */
  YYSYMBOL_LT = 51,                        /* LT  */
  YYSYMBOL_GT = 52,                        /* GT  */
  YYSYMBOL_LE = 53,                        /* LE  */
  YYSYMBOL_GE = 54,                        /* GE  */
  YYSYMBOL_NE = 55,                        /* NE  */
  YYSYMBOL_NUMBER = 56,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_DATE_STR = 58,                  /* DATE_STR  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_SSS = 60,                       /* SSS  */
  YYSYMBOL_61_ = 61,                       /* '+'  */
  YYSYMBOL_62_ = 62,                       /* '-'  */
  YYSYMBOL_63_ = 63,                       /* '*'  */
  YYSYMBOL_64_ = 64,                       /* '/'  */
  YYSYMBOL_UMINUS = 65,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_commands = 67,                  /* commands  */
  YYSYMBOL_command_wrapper = 68,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 69,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 70,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 71,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 72,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 73,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 74,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 75,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 76,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 77,           /* desc_table_stmt  */
  YYSYMBOL_ind_list = 78,                  /* ind_list  */
  YYSYMBOL_create_index_stmt = 79,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 80,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 81,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 82,             /* attr_def_list  */
  YYSYMBOL_attr_def = 83,                  /* attr_def  */
  YYSYMBOL_number = 84,                    /* number  */
  YYSYMBOL_type = 85,                      /* type  */
  YYSYMBOL_insert_stmt = 86,               /* insert_stmt  */
  YYSYMBOL_value_list = 87,                /* value_list  */
  YYSYMBOL_value = 88,                     /* value  */
  YYSYMBOL_join_expr = 89,                 /* join_expr  */
  YYSYMBOL_on_condition_exprs = 90,        /* on_condition_exprs  */
  YYSYMBOL_join_table = 91,                /* join_table  */
  YYSYMBOL_join_tables = 92,               /* join_tables  */
  YYSYMBOL_delete_stmt = 93,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 94,               /* update_stmt  */
  YYSYMBOL_select_stmt = 95,               /* select_stmt  */
  YYSYMBOL_calc_stmt = 96,                 /* calc_stmt  */
  YYSYMBOL_expression_list = 97,           /* expression_list  */
  YYSYMBOL_expression = 98,                /* expression  */
  YYSYMBOL_select_attr = 99,               /* select_attr  */
  YYSYMBOL_aggr_op = 100,                  /* aggr_op  */
  YYSYMBOL_select_aggr_attr = 101,         /* select_aggr_attr  */
  YYSYMBOL_aggr_func = 102,                /* aggr_func  */
  YYSYMBOL_aggr_func_list = 103,           /* aggr_func_list  */
  YYSYMBOL_rel_attr = 104,                 /* rel_attr  */
  YYSYMBOL_attr_list = 105,                /* attr_list  */
  YYSYMBOL_rel_list = 106,                 /* rel_list  */
  YYSYMBOL_where = 107,                    /* where  */
  YYSYMBOL_condition_list = 108,           /* condition_list  */
  YYSYMBOL_condition = 109,                /* condition  */
  YYSYMBOL_comp_op = 110,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 111,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 112,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 113,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 114             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   193

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    63,    61,     2,    62,     2,    64,     2,     2,
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
      55,    56,    57,    58,    59,    60,    65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   198,   198,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   229,   235,   240,   246,   252,   258,   264,
     271,   277,   285,   288,   300,   320,   330,   349,   352,   365,
     373,   383,   386,   387,   388,   389,   392,   408,   411,   422,
     426,   430,   436,   444,   449,   457,   460,   466,   474,   485,
     494,   497,   510,   522,   538,   558,   583,   614,   624,   629,
     640,   643,   646,   649,   652,   656,   659,   667,   674,   686,
     689,   692,   695,   698,   703,   713,   719,   725,   737,   740,
     752,   757,   767,   770,   784,   787,   800,   803,   809,   812,
     817,   824,   836,   848,   860,   875,   876,   877,   878,   879,
     880,   881,   882,   886,   899,   907,   917,   918
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "INNER", "JOIN", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "NOT", "LIKE", "MAX", "MIN", "COUNT", "AVG", "SUM", "EQ",
  "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "DATE_STR", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "ind_list", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "number", "type",
  "insert_stmt", "value_list", "value", "join_expr", "on_condition_exprs",
  "join_table", "join_tables", "delete_stmt", "update_stmt", "select_stmt",
  "calc_stmt", "expression_list", "expression", "select_attr", "aggr_op",
  "select_aggr_attr", "aggr_func", "aggr_func_list", "rel_attr",
  "attr_list", "rel_list", "where", "condition_list", "condition",
  "comp_op", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
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
     315,    43,    45,    42,    47,   316
};
#endif

#define YYPACT_NINF (-172)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      84,     7,    13,    -5,    18,   -54,     3,  -172,     5,    22,
     -22,  -172,  -172,  -172,  -172,  -172,    17,    31,    84,    80,
      79,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,    25,    26,    27,    32,    -5,  -172,  -172,  -172,  -172,
      -5,  -172,  -172,    -3,  -172,  -172,  -172,  -172,  -172,    63,
    -172,    69,    85,    71,    91,    94,  -172,  -172,    61,    65,
      88,    72,    90,  -172,  -172,  -172,  -172,   115,    95,  -172,
      96,   -14,  -172,    -5,    -5,    -5,    -5,    -5,    76,    77,
     -52,    78,   -20,  -172,    81,  -172,   107,   106,    83,    12,
      86,    89,    92,    93,  -172,  -172,   -25,   -25,  -172,  -172,
    -172,   -10,   -12,   121,   124,    91,    94,   127,   -26,  -172,
      97,  -172,   119,   104,   126,   133,  -172,    98,   120,  -172,
      99,    45,   106,  -172,   100,  -172,   106,  -172,  -172,    12,
      64,    64,  -172,   117,    12,   149,  -172,  -172,  -172,  -172,
     139,    89,   142,   102,   124,  -172,   125,    45,   106,  -172,
     144,  -172,   145,   122,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,   -26,   -26,   -26,   106,   110,   109,   126,  -172,   151,
    -172,   -26,  -172,  -172,  -172,    12,   153,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,   154,  -172,   114,   156,
    -172,   140,   145,  -172,  -172,   151,  -172,   -26,  -172,  -172,
    -172
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     116,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,    76,    67,    68,    79,    82,    83,    80,    81,    90,
      77,     0,     0,     0,    88,    92,    31,    30,     0,     0,
       0,     0,     0,   114,     1,   117,     2,     0,     0,    29,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,     0,    78,     0,    96,     0,     0,
       0,     0,     0,     0,    74,    69,    70,    71,    72,    73,
      91,    94,     0,     0,    94,    88,    92,     0,    98,    62,
       0,   115,     0,     0,    37,     0,    35,     0,     0,    53,
       0,    60,    96,    86,     0,    85,    96,    89,    93,     0,
       0,     0,    97,    99,     0,     0,    42,    43,    44,    45,
      40,     0,     0,     0,    94,    54,    59,    60,    96,    65,
       0,    64,    47,     0,   112,   105,   106,   107,   108,   109,
     110,     0,     0,    98,    96,     0,     0,    37,    36,    32,
      95,    55,    61,    66,    87,     0,     0,   111,   102,   104,
     101,   103,   100,    63,   113,    41,     0,    38,     0,     0,
      58,    56,    47,    46,    39,    32,    34,    98,    48,    33,
      57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,   157,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,   -28,  -172,  -172,  -172,     1,    28,  -172,  -172,
    -172,   -21,   -98,  -172,  -172,    73,    23,  -172,  -172,  -172,
    -172,   103,   -42,  -172,  -172,  -172,   101,    67,    -4,    74,
     -92,  -118,  -171,     2,    44,  -172,  -172,  -172,  -172
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   199,    30,    31,    32,   152,   124,   196,   150,
      33,   186,    51,   130,   200,   157,   158,    34,    35,    36,
      37,    52,    53,    61,    62,    63,    64,    93,   141,    95,
     132,   119,   142,   143,   171,    38,    39,    40,    76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,   121,   192,    81,   104,    66,   133,   112,    82,   127,
      67,   113,    45,    41,   159,    42,    83,   134,   161,    43,
     140,    44,   136,   128,   129,    54,    55,    56,    57,    58,
      46,    47,    48,    59,    49,    68,   210,    70,    86,    87,
     183,   162,   106,   107,   108,   109,   174,    84,    85,    86,
      87,    46,    47,    48,    69,    49,   193,    50,    84,    85,
      86,    87,   180,    54,    55,    56,    57,    58,    46,    47,
      48,    72,    49,   188,   190,   140,    71,    59,   128,   129,
      74,    60,    75,   140,    77,    78,    79,   202,     1,     2,
     116,    80,    88,     3,     4,     5,     6,     7,     8,     9,
      10,    89,    90,    91,    11,    12,    13,   163,   164,   140,
      92,    14,    15,    94,   165,   166,   167,   168,   169,   170,
      96,    16,    99,    17,    97,    98,    18,   146,   147,   148,
     149,   100,   101,   102,   103,   110,   111,   114,   117,   135,
      59,   118,   120,   127,   139,   151,   122,   144,   123,   145,
     153,   125,   126,   173,   155,   175,   176,   154,   156,   160,
     178,   179,   184,   181,   185,   195,   187,   189,   191,   194,
     198,   203,   204,   205,   206,    73,   207,   209,   197,   177,
     182,   208,   137,   201,   131,   172,   105,     0,     0,     0,
     138,     0,     0,   115
};

static const yytype_int16 yycheck[] =
{
       4,    99,   173,    45,    18,    59,    18,    59,    50,    19,
       7,    63,    17,     6,   132,     8,    19,    29,   136,     6,
     118,     8,   114,    33,    34,    45,    46,    47,    48,    49,
      56,    57,    58,    59,    60,    30,   207,    59,    63,    64,
     158,   139,    84,    85,    86,    87,   144,    61,    62,    63,
      64,    56,    57,    58,    32,    60,   174,    62,    61,    62,
      63,    64,   154,    45,    46,    47,    48,    49,    56,    57,
      58,    40,    60,   171,   172,   173,    59,    59,    33,    34,
       0,    63,     3,   181,    59,    59,    59,   185,     4,     5,
      94,    59,    29,     9,    10,    11,    12,    13,    14,    15,
      16,    32,    17,    32,    20,    21,    22,    43,    44,   207,
      19,    27,    28,    19,    50,    51,    52,    53,    54,    55,
      59,    37,    50,    39,    59,    37,    42,    23,    24,    25,
      26,    41,    17,    38,    38,    59,    59,    59,    31,    18,
      59,    35,    59,    19,    17,    19,    60,    50,    59,    30,
      17,    59,    59,    36,    34,     6,    17,    59,    59,    59,
      18,    59,    18,    38,    19,    56,    44,   171,   172,    59,
      19,    18,    18,    59,    18,    18,    36,   205,   177,   151,
     157,   202,   115,   181,   111,   141,    83,    -1,    -1,    -1,
     116,    -1,    -1,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    27,    28,    37,    39,    42,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      79,    80,    81,    86,    93,    94,    95,    96,   111,   112,
     113,     6,     8,     6,     8,    17,    56,    57,    58,    60,
      62,    88,    97,    98,    45,    46,    47,    48,    49,    59,
      63,    99,   100,   101,   102,   104,    59,     7,    30,    32,
      59,    59,    40,    68,     0,     3,   114,    59,    59,    59,
      59,    98,    98,    19,    61,    62,    63,    64,    29,    32,
      17,    32,    19,   103,    19,   105,    59,    59,    37,    50,
      41,    17,    38,    38,    18,    97,    98,    98,    98,    98,
      59,    59,    59,    63,    59,   102,   104,    31,    35,   107,
      59,    88,    60,    59,    83,    59,    59,    19,    33,    34,
      89,    91,   106,    18,    29,    18,   106,   103,   105,    17,
      88,   104,   108,   109,    50,    30,    23,    24,    25,    26,
      85,    19,    82,    17,    59,    34,    59,    91,    92,   107,
      59,   107,    88,    43,    44,    50,    51,    52,    53,    54,
      55,   110,   110,    36,    88,     6,    17,    83,    18,    59,
     106,    38,    92,   107,    18,    19,    87,    44,    88,   104,
      88,   104,   108,   107,    59,    56,    84,    82,    19,    78,
      90,   109,    88,    18,    18,    59,    18,    36,    87,    78,
     108
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    78,    79,    80,    81,    82,    82,    83,
      83,    84,    85,    85,    85,    85,    86,    87,    87,    88,
      88,    88,    88,    89,    89,    90,    90,    90,    91,    91,
      92,    92,    93,    94,    95,    95,    95,    96,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    99,    99,   100,
     100,   100,   100,   100,   101,   102,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   109,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   112,   113,   114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     0,     3,     9,     5,     7,     0,     3,     5,
       2,     1,     1,     1,     1,     1,     8,     0,     3,     1,
       1,     1,     1,     1,     2,     0,     1,     3,     4,     2,
       0,     2,     4,     7,     6,     6,     7,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     4,     4,     6,     0,     3,
       1,     3,     0,     3,     0,     3,     0,     2,     0,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     2,     1,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 199 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1755 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 229 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1764 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 235 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1772 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 240 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1780 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 246 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1788 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 252 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1796 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 258 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1804 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 264 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1814 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 271 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1822 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 277 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1832 "yacc_sql.cpp"
    break;

  case 32: /* ind_list: %empty  */
#line 285 "yacc_sql.y"
    {
      (yyval.index_list) = nullptr;
    }
#line 1840 "yacc_sql.cpp"
    break;

  case 33: /* ind_list: COMMA ID ind_list  */
#line 288 "yacc_sql.y"
                        {
      if((yyvsp[0].index_list) != nullptr){
        (yyval.index_list) = (yyvsp[0].index_list);
      }else{
        (yyval.index_list) = new std::vector<std::string>; 
      }
      (yyval.index_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID ind_list RBRACE  */
#line 301 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      std::vector<string> * ind_list = (yyvsp[-1].index_list);
      if(ind_list != nullptr) {
        create_index.attribute_name.swap(*ind_list);
      }
      create_index.attribute_name.push_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_name.begin(),create_index.attribute_name.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      delete (yyvsp[-1].index_list);
    }
#line 1875 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1887 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 331 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1907 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 349 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1915 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 353 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1929 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE  */
#line 366 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      free((yyvsp[-4].string));
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type  */
#line 374 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-1].string));
    }
#line 1953 "yacc_sql.cpp"
    break;

  case 41: /* number: NUMBER  */
#line 383 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1959 "yacc_sql.cpp"
    break;

  case 42: /* type: INT_T  */
#line 386 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 1965 "yacc_sql.cpp"
    break;

  case 43: /* type: STRING_T  */
#line 387 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 1971 "yacc_sql.cpp"
    break;

  case 44: /* type: FLOAT_T  */
#line 388 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 1977 "yacc_sql.cpp"
    break;

  case 45: /* type: DATE_T  */
#line 389 "yacc_sql.y"
             { (yyval.number)=DATES; }
#line 1983 "yacc_sql.cpp"
    break;

  case 46: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 393 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 1999 "yacc_sql.cpp"
    break;

  case 47: /* value_list: %empty  */
#line 408 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 48: /* value_list: COMMA value value_list  */
#line 411 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2021 "yacc_sql.cpp"
    break;

  case 49: /* value: NUMBER  */
#line 422 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 50: /* value: FLOAT  */
#line 426 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 51: /* value: DATE_STR  */
#line 430 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value();
      (yyval.value)->set_date(tmp);
      free(tmp);
    }
#line 2050 "yacc_sql.cpp"
    break;

  case 52: /* value: SSS  */
#line 436 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2060 "yacc_sql.cpp"
    break;

  case 53: /* join_expr: JOIN  */
#line 445 "yacc_sql.y"
  {
    (yyval.join_type) = JOIN_TABLE;

  }
#line 2069 "yacc_sql.cpp"
    break;

  case 54: /* join_expr: INNER JOIN  */
#line 450 "yacc_sql.y"
  {
    (yyval.join_type) = INNER_JOIN_TABLE;
  }
#line 2077 "yacc_sql.cpp"
    break;

  case 55: /* on_condition_exprs: %empty  */
#line 457 "yacc_sql.y"
  {
    (yyval.condition_list) = nullptr;
  }
#line 2085 "yacc_sql.cpp"
    break;

  case 56: /* on_condition_exprs: condition  */
#line 461 "yacc_sql.y"
  {
    (yyval.condition_list) = new std::vector<ConditionSqlNode>;
    (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
    delete (yyvsp[0].condition);
  }
#line 2095 "yacc_sql.cpp"
    break;

  case 57: /* on_condition_exprs: condition AND condition_list  */
#line 466 "yacc_sql.y"
                                 {
    (yyval.condition_list) = (yyvsp[0].condition_list);
    (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
    delete (yyvsp[-2].condition);
  }
#line 2105 "yacc_sql.cpp"
    break;

  case 58: /* join_table: join_expr ID ON on_condition_exprs  */
#line 475 "yacc_sql.y"
  {
    (yyval.join_table) = new JoinTableSqlNode;
    (yyval.join_table)->table_name = (yyvsp[-2].string);
    free((yyvsp[-2].string));

    if ((yyvsp[0].condition_list) != nullptr) {
      (yyval.join_table)->on_conditions = *(yyvsp[0].condition_list);
    }
    delete (yyvsp[0].condition_list);
  }
#line 2120 "yacc_sql.cpp"
    break;

  case 59: /* join_table: join_expr ID  */
#line 486 "yacc_sql.y"
  {
    (yyval.join_table) = new JoinTableSqlNode;
    (yyval.join_table)->table_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2130 "yacc_sql.cpp"
    break;

  case 60: /* join_tables: %empty  */
#line 494 "yacc_sql.y"
    {
      (yyval.join_table_list) = nullptr;
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 61: /* join_tables: join_table join_tables  */
#line 498 "yacc_sql.y"
    { 
      if ((yyvsp[0].join_table_list) == nullptr) {
        (yyval.join_table_list) = new std::vector<JoinTableSqlNode>;
      } else {
        (yyval.join_table_list) = (yyvsp[0].join_table_list);
      }

      (yyval.join_table_list)->push_back(*(yyvsp[-1].join_table));
      delete (yyvsp[-1].join_table);
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 62: /* delete_stmt: DELETE FROM ID where  */
#line 511 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2167 "yacc_sql.cpp"
    break;

  case 63: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 523 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2184 "yacc_sql.cpp"
    break;

  case 64: /* select_stmt: SELECT select_aggr_attr FROM ID rel_list where  */
#line 539 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-4].rel_attr_list));
        delete (yyvsp[-4].rel_attr_list);
      }
      if ((yyvsp[-1].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-2].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].string));
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: SELECT select_attr FROM ID rel_list where  */
#line 559 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-4].rel_attr_list));
        delete (yyvsp[-4].rel_attr_list);
      }
      if ((yyvsp[-1].relation_list) != nullptr) {
        /* join with COMMA represents empty on condition */
        for (int i = 0;i < (int)(yyvsp[-1].relation_list)->size(); i++) {
          (yyval.sql_node)->selection.on_conditions.push_back(vector<ConditionSqlNode>());
        }

        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-2].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].string));
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: SELECT select_attr FROM ID join_table join_tables where  */
#line 584 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-5].rel_attr_list));
        delete (yyvsp[-5].rel_attr_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-3].string));
      
      if ((yyvsp[-1].join_table_list) != nullptr) {
        int i = 0;
        for(i = 0; i < (int)(yyvsp[-1].join_table_list)->size(); i++) {
          (yyval.sql_node)->selection.relations.push_back((*(yyvsp[-1].join_table_list))[i].table_name);
          (yyval.sql_node)->selection.on_conditions.push_back((*(yyvsp[-1].join_table_list))[i].on_conditions);
        }
        delete (yyvsp[-1].join_table_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-2].join_table)->table_name);
      (yyval.sql_node)->selection.on_conditions.push_back((yyvsp[-2].join_table)->on_conditions);
      std::reverse((yyval.sql_node)->selection.relations.begin() + 1, (yyval.sql_node)->selection.relations.end());
      std::reverse((yyval.sql_node)->selection.on_conditions.begin(), (yyval.sql_node)->selection.on_conditions.end());
      delete (yyvsp[-2].join_table);

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 67: /* calc_stmt: CALC expression_list  */
#line 615 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2281 "yacc_sql.cpp"
    break;

  case 68: /* expression_list: expression  */
#line 625 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2290 "yacc_sql.cpp"
    break;

  case 69: /* expression_list: expression COMMA expression_list  */
#line 630 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 70: /* expression: expression '+' expression  */
#line 640 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2311 "yacc_sql.cpp"
    break;

  case 71: /* expression: expression '-' expression  */
#line 643 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 72: /* expression: expression '*' expression  */
#line 646 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 73: /* expression: expression '/' expression  */
#line 649 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 74: /* expression: LBRACE expression RBRACE  */
#line 652 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 75: /* expression: '-' expression  */
#line 656 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 76: /* expression: value  */
#line 659 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2362 "yacc_sql.cpp"
    break;

  case 77: /* select_attr: '*'  */
#line 667 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 78: /* select_attr: rel_attr attr_list  */
#line 674 "yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 79: /* aggr_op: MAX  */
#line 686 "yacc_sql.y"
      {
    (yyval.aggr_op) = AGG_MAX;
  }
#line 2396 "yacc_sql.cpp"
    break;

  case 80: /* aggr_op: AVG  */
#line 689 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_AVG;
  }
#line 2404 "yacc_sql.cpp"
    break;

  case 81: /* aggr_op: SUM  */
#line 692 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_SUM;
  }
#line 2412 "yacc_sql.cpp"
    break;

  case 82: /* aggr_op: MIN  */
#line 695 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_MIN;
  }
#line 2420 "yacc_sql.cpp"
    break;

  case 83: /* aggr_op: COUNT  */
#line 698 "yacc_sql.y"
          {
    (yyval.aggr_op) = AGG_COUNT;
  }
#line 2428 "yacc_sql.cpp"
    break;

  case 84: /* select_aggr_attr: aggr_func aggr_func_list  */
#line 703 "yacc_sql.y"
                          {
    if ((yyvsp[0].rel_attr_list) != nullptr){
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
    delete (yyvsp[-1].rel_attr);
  }
#line 2442 "yacc_sql.cpp"
    break;

  case 85: /* aggr_func: aggr_op LBRACE '*' RBRACE  */
#line 713 "yacc_sql.y"
                            {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name = "";
    (yyval.rel_attr)->attribute_name = '*';
    (yyval.rel_attr)->aggr_op = (yyvsp[-3].aggr_op);
  }
#line 2453 "yacc_sql.cpp"
    break;

  case 86: /* aggr_func: aggr_op LBRACE ID RBRACE  */
#line 719 "yacc_sql.y"
                             {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-3].aggr_op);
    free((yyvsp[-1].string));    
  }
#line 2464 "yacc_sql.cpp"
    break;

  case 87: /* aggr_func: aggr_op LBRACE ID DOT ID RBRACE  */
#line 725 "yacc_sql.y"
                                    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_op = (yyvsp[-5].aggr_op);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
  }
#line 2477 "yacc_sql.cpp"
    break;

  case 88: /* aggr_func_list: %empty  */
#line 737 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 89: /* aggr_func_list: COMMA aggr_func aggr_func_list  */
#line 740 "yacc_sql.y"
                                     {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 90: /* rel_attr: ID  */
#line 752 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2509 "yacc_sql.cpp"
    break;

  case 91: /* rel_attr: ID DOT ID  */
#line 757 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 92: /* attr_list: %empty  */
#line 767 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 93: /* attr_list: COMMA rel_attr attr_list  */
#line 770 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2544 "yacc_sql.cpp"
    break;

  case 94: /* rel_list: %empty  */
#line 784 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 95: /* rel_list: COMMA ID rel_list  */
#line 787 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 96: /* where: %empty  */
#line 800 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2575 "yacc_sql.cpp"
    break;

  case 97: /* where: WHERE condition_list  */
#line 803 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 98: /* condition_list: %empty  */
#line 809 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 99: /* condition_list: condition  */
#line 812 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 100: /* condition_list: condition AND condition_list  */
#line 817 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 101: /* condition: rel_attr comp_op value  */
#line 825 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2627 "yacc_sql.cpp"
    break;

  case 102: /* condition: value comp_op value  */
#line 837 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 103: /* condition: rel_attr comp_op rel_attr  */
#line 849 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 104: /* condition: value comp_op rel_attr  */
#line 861 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 105: /* comp_op: EQ  */
#line 875 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2681 "yacc_sql.cpp"
    break;

  case 106: /* comp_op: LT  */
#line 876 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2687 "yacc_sql.cpp"
    break;

  case 107: /* comp_op: GT  */
#line 877 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2693 "yacc_sql.cpp"
    break;

  case 108: /* comp_op: LE  */
#line 878 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2699 "yacc_sql.cpp"
    break;

  case 109: /* comp_op: GE  */
#line 879 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2705 "yacc_sql.cpp"
    break;

  case 110: /* comp_op: NE  */
#line 880 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2711 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: NOT LIKE  */
#line 881 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2717 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LIKE  */
#line 882 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2723 "yacc_sql.cpp"
    break;

  case 113: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 887 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 114: /* explain_stmt: EXPLAIN command_wrapper  */
#line 900 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 115: /* set_variable_stmt: SET ID EQ value  */
#line 908 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2758 "yacc_sql.cpp"
    break;


#line 2762 "yacc_sql.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 920 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
