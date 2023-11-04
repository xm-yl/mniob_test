/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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
  YYSYMBOL_UNIQUE = 8,                     /* UNIQUE  */
  YYSYMBOL_INDEX = 9,                      /* INDEX  */
  YYSYMBOL_CALC = 10,                      /* CALC  */
  YYSYMBOL_SELECT = 11,                    /* SELECT  */
  YYSYMBOL_DESC = 12,                      /* DESC  */
  YYSYMBOL_SHOW = 13,                      /* SHOW  */
  YYSYMBOL_SYNC = 14,                      /* SYNC  */
  YYSYMBOL_INSERT = 15,                    /* INSERT  */
  YYSYMBOL_DELETE = 16,                    /* DELETE  */
  YYSYMBOL_UPDATE = 17,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 21,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 22,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 23,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 24,                     /* INT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_AS = 33,                        /* AS  */
  YYSYMBOL_FROM = 34,                      /* FROM  */
  YYSYMBOL_INNER = 35,                     /* INNER  */
  YYSYMBOL_JOIN = 36,                      /* JOIN  */
  YYSYMBOL_WHERE = 37,                     /* WHERE  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_OR = 39,                        /* OR  */
  YYSYMBOL_SET = 40,                       /* SET  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_LOAD = 42,                      /* LOAD  */
  YYSYMBOL_DATA = 43,                      /* DATA  */
  YYSYMBOL_INFILE = 44,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 45,                   /* EXPLAIN  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_IN = 47,                        /* IN  */
  YYSYMBOL_EXISTS = 48,                    /* EXISTS  */
  YYSYMBOL_LIKE = 49,                      /* LIKE  */
  YYSYMBOL_ORDER = 50,                     /* ORDER  */
  YYSYMBOL_BY = 51,                        /* BY  */
  YYSYMBOL_ASC = 52,                       /* ASC  */
  YYSYMBOL_MAX = 53,                       /* MAX  */
  YYSYMBOL_MIN = 54,                       /* MIN  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_AVG = 56,                       /* AVG  */
  YYSYMBOL_SUM = 57,                       /* SUM  */
  YYSYMBOL_NULL_T = 58,                    /* NULL_T  */
  YYSYMBOL_IS = 59,                        /* IS  */
  YYSYMBOL_EQ = 60,                        /* EQ  */
  YYSYMBOL_LT = 61,                        /* LT  */
  YYSYMBOL_GT = 62,                        /* GT  */
  YYSYMBOL_LE = 63,                        /* LE  */
  YYSYMBOL_GE = 64,                        /* GE  */
  YYSYMBOL_NE = 65,                        /* NE  */
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_DATE_STR = 68,                  /* DATE_STR  */
  YYSYMBOL_ID = 69,                        /* ID  */
  YYSYMBOL_SSS = 70,                       /* SSS  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '-'  */
  YYSYMBOL_73_ = 73,                       /* '*'  */
  YYSYMBOL_74_ = 74,                       /* '/'  */
  YYSYMBOL_UMINUS = 75,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_commands = 77,                  /* commands  */
  YYSYMBOL_command_wrapper = 78,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 79,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 80,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 81,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 82,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 83,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 84,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 85,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 86,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 87,           /* desc_table_stmt  */
  YYSYMBOL_ind_list = 88,                  /* ind_list  */
  YYSYMBOL_unique_token = 89,              /* unique_token  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 91,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 92,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_attr_can_null = 95,             /* attr_can_null  */
  YYSYMBOL_number = 96,                    /* number  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_insert_stmt = 98,               /* insert_stmt  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_join_expr = 101,                /* join_expr  */
  YYSYMBOL_on_condition_exprs = 102,       /* on_condition_exprs  */
  YYSYMBOL_join_table = 103,               /* join_table  */
  YYSYMBOL_join_tables = 104,              /* join_tables  */
  YYSYMBOL_delete_stmt = 105,              /* delete_stmt  */
  YYSYMBOL_update_expr = 106,              /* update_expr  */
  YYSYMBOL_update_exprs = 107,             /* update_exprs  */
  YYSYMBOL_update_stmt = 108,              /* update_stmt  */
  YYSYMBOL_order_by_attr = 109,            /* order_by_attr  */
  YYSYMBOL_order_by_attrs = 110,           /* order_by_attrs  */
  YYSYMBOL_order_by = 111,                 /* order_by  */
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 113,                /* calc_stmt  */
  YYSYMBOL_expression_list = 114,          /* expression_list  */
  YYSYMBOL_expression = 115,               /* expression  */
  YYSYMBOL_select_attr = 116,              /* select_attr  */
  YYSYMBOL_aggr_op = 117,                  /* aggr_op  */
  YYSYMBOL_aggr_func = 118,                /* aggr_func  */
  YYSYMBOL_aggr_func_list = 119,           /* aggr_func_list  */
  YYSYMBOL_rel_attr = 120,                 /* rel_attr  */
  YYSYMBOL_attr_list = 121,                /* attr_list  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_where = 123,                    /* where  */
  YYSYMBOL_condition_list = 124,           /* condition_list  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_comp_op = 126,                  /* comp_op  */
  YYSYMBOL_comp_op_reverse = 127,          /* comp_op_reverse  */
  YYSYMBOL_load_data_stmt = 128,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 129,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 130,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 131             /* opt_semicolon  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  316

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,    73,    71,     2,    72,     2,    74,     2,     2,
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
      65,    66,    67,    68,    69,    70,    75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   250,   256,   261,   267,   273,   279,   285,
     292,   298,   306,   309,   320,   323,   327,   351,   361,   380,
     383,   396,   405,   417,   420,   423,   429,   432,   433,   434,
     435,   438,   454,   457,   468,   472,   476,   482,   486,   494,
     499,   507,   510,   516,   524,   535,   544,   547,   560,   573,
     585,   599,   602,   615,   637,   643,   650,   660,   663,   669,
     682,   685,   692,   719,   757,   767,   772,   783,   786,   789,
     792,   795,   799,   802,   810,   817,   826,   838,   841,   844,
     847,   850,   856,   862,   871,   880,   886,   894,   902,   910,
     920,   934,   937,   949,   954,   961,   968,   975,   984,   996,
     999,  1011,  1020,  1029,  1040,  1051,  1062,  1076,  1079,  1085,
    1088,  1093,  1098,  1106,  1118,  1130,  1142,  1154,  1166,  1178,
    1192,  1206,  1220,  1234,  1248,  1262,  1279,  1296,  1313,  1331,
    1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
    1364,  1365,  1366,  1367,  1368,  1369,  1372,  1385,  1393,  1403,
    1404
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
  "DROP", "TABLE", "TABLES", "UNIQUE", "INDEX", "CALC", "SELECT", "DESC",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "AS",
  "FROM", "INNER", "JOIN", "WHERE", "AND", "OR", "SET", "ON", "LOAD",
  "DATA", "INFILE", "EXPLAIN", "NOT", "IN", "EXISTS", "LIKE", "ORDER",
  "BY", "ASC", "MAX", "MIN", "COUNT", "AVG", "SUM", "NULL_T", "IS", "EQ",
  "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "DATE_STR", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "ind_list", "unique_token", "create_index_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "attr_can_null", "number", "type", "insert_stmt", "value_list", "value",
  "join_expr", "on_condition_exprs", "join_table", "join_tables",
  "delete_stmt", "update_expr", "update_exprs", "update_stmt",
  "order_by_attr", "order_by_attrs", "order_by", "select_stmt",
  "calc_stmt", "expression_list", "expression", "select_attr", "aggr_op",
  "aggr_func", "aggr_func_list", "rel_attr", "attr_list", "rel_list",
  "where", "condition_list", "condition", "comp_op", "comp_op_reverse",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-199)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-156)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     189,    82,    24,    39,   111,   -34,    37,  -199,    16,    28,
      10,  -199,  -199,  -199,  -199,  -199,    13,    44,   189,   108,
     131,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,    66,  -199,   129,    79,    80,    39,  -199,  -199,  -199,
    -199,  -199,    39,  -199,  -199,     2,  -199,  -199,  -199,  -199,
    -199,    -1,  -199,   117,   139,   141,   143,  -199,  -199,   101,
     102,   133,   114,   132,  -199,  -199,  -199,  -199,   160,   110,
    -199,   140,    -2,  -199,    39,    39,    39,    39,    39,   113,
     121,  -199,   122,    64,   193,  -199,   127,  -199,   156,   161,
     128,   119,   137,   144,   167,   145,  -199,  -199,   -59,   -59,
    -199,  -199,   -24,  -199,    -9,   161,     4,   190,   141,   143,
     198,    73,  -199,   159,   200,  -199,   195,   227,   201,   155,
    -199,   158,  -199,   163,   164,   192,  -199,   210,   175,    67,
     212,   -13,   194,    45,  -199,  -199,   119,   253,   218,   249,
     176,   196,  -199,    74,    92,   128,   161,   263,  -199,  -199,
    -199,  -199,    -5,   144,   251,   254,  -199,    -8,  -199,   255,
    -199,   163,   232,    67,   161,   223,  -199,   207,  -199,   258,
     209,  -199,   259,   269,   271,   253,    75,   272,  -199,   245,
    -199,  -199,  -199,  -199,  -199,  -199,    59,    98,   274,    86,
      73,    73,   253,  -199,   200,  -199,   224,   228,   237,  -199,
    -199,   201,  -199,   229,   163,  -199,    73,  -199,   212,   127,
    -199,    51,  -199,   119,   277,   222,   253,   278,   281,  -199,
     119,  -199,   253,  -199,  -199,   282,    -3,   253,  -199,  -199,
    -199,  -199,   283,  -199,  -199,  -199,   284,  -199,  -199,   285,
    -199,  -199,   266,  -199,   286,  -199,     6,   238,  -199,   259,
    -199,   252,   290,   291,   292,   293,   294,   295,   296,   -30,
     297,  -199,   119,   259,   298,    -3,   259,   299,   300,  -199,
     -27,   246,   301,    73,   127,  -199,  -199,  -199,  -199,   253,
    -199,  -199,  -199,   259,   302,  -199,   259,   303,   304,  -199,
    -199,  -199,   285,  -199,  -199,  -199,   305,   306,  -199,   307,
    -199,  -199,  -199,  -199,  -199,  -199
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     169,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,    35,     0,     0,     0,     0,    57,    54,    55,
      56,    58,     0,    93,    84,    85,    97,   100,   101,    98,
      99,   113,    94,     0,     0,   111,   119,    31,    30,     0,
       0,     0,     0,     0,   167,     1,   170,     2,     0,     0,
      29,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,   116,     0,     0,     0,    96,     0,    95,     0,   127,
       0,     0,     0,     0,     0,     0,    91,    86,    87,    88,
      89,    90,   114,   115,   121,   127,     0,     0,   111,   119,
       0,   129,    68,     0,    71,   168,     0,     0,    39,     0,
      37,     0,   118,     0,     0,     0,    59,   123,     0,    66,
      80,   105,     0,   102,   112,   120,     0,     0,     0,     0,
       0,     0,   128,   130,     0,     0,   127,     0,    47,    48,
      49,    50,    43,     0,     0,     0,   117,   121,   122,   124,
      60,     0,    65,    66,   127,     0,    82,     0,   107,     0,
       0,   104,    52,     0,     0,     0,     0,     0,   157,   158,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
     129,   129,     0,    69,    71,    73,     0,     0,     0,    45,
      42,    39,    38,     0,     0,   125,    61,    67,    80,    77,
     106,   108,   103,     0,     0,     0,     0,     0,     0,   156,
       0,   159,     0,   134,   136,     0,     0,     0,   133,   135,
     131,   132,     0,    72,   166,    46,     0,    44,    40,    32,
     126,    64,    62,    83,    78,    81,    74,     0,   110,    52,
      51,     0,   160,   161,   162,   163,   164,   165,     0,     0,
       0,   137,     0,    52,     0,     0,    52,     0,     0,    70,
      43,     0,     0,   129,    77,    76,    75,   109,    53,     0,
     143,   144,   138,    52,     0,   142,    52,     0,     0,   139,
     141,    41,    32,    36,    63,    79,     0,     0,   147,     0,
     140,   145,    33,   149,   148,   146
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,   309,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,    26,  -199,  -199,  -199,  -199,   118,   168,    50,
    -199,  -199,  -199,  -178,  -100,  -199,  -199,   219,   162,  -199,
     177,   130,  -199,  -199,    52,   120,  -143,  -199,   256,   -36,
    -199,  -199,   243,   221,    -4,   225,  -128,  -108,  -198,   125,
    -145,  -199,  -199,  -199,  -199,  -199
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   282,    43,    30,    31,    32,   164,   128,   210,
     246,   162,    33,   224,    53,   138,   251,   173,   174,    34,
     124,   156,    35,   254,   255,   176,    36,    37,    54,    55,
      63,    64,    65,    95,   151,    97,   115,   122,   152,   153,
     196,   269,    38,    39,    40,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,   125,   240,   241,   183,   168,   199,   140,     4,   131,
      82,   133,   133,   207,    87,    88,    83,   106,   285,   208,
     177,   150,    84,   141,   134,   134,   135,   136,    47,    89,
      44,   209,    90,    45,   142,    67,    48,    49,    50,    61,
      51,   208,   227,   215,    68,   132,   182,    69,   205,   108,
     109,   110,   111,   209,   203,    47,   178,    46,   286,   242,
     137,   137,    70,    48,    49,    50,   218,    51,    91,    85,
      86,    87,    88,    85,    86,    87,    88,   232,   180,    71,
     268,   288,    72,   270,   257,   304,   250,    73,    41,   274,
      42,   147,   119,   277,   278,   294,   233,    47,   298,   238,
     150,   150,   135,   136,   237,    48,    49,    50,    75,    51,
     202,    52,   200,   201,   181,   307,   150,    47,   309,   148,
     258,   149,   228,   259,   229,    48,    49,    50,    61,    51,
     273,    47,   297,   116,    76,    78,   276,   117,    79,    48,
      49,    50,    61,    51,    47,   235,   306,   229,    80,    81,
      47,    92,    48,    49,    50,    61,    51,    93,    48,    49,
      50,    94,    51,    96,    56,    57,    58,    59,    60,   290,
      98,    99,   293,   100,   101,   296,   102,    47,   103,   104,
      61,   105,   112,   150,    62,    48,    49,    50,   120,    51,
     113,   114,   234,     1,     2,   239,    61,   123,   121,     3,
       4,     5,     6,     7,     8,     9,    10,   126,   129,   143,
      11,    12,    13,   127,   130,   256,   146,    14,    15,   154,
     155,   163,   186,   187,   165,   188,   157,   166,   170,    16,
     171,    17,   167,   169,    18,   189,   190,   191,   192,   193,
     194,   195,   197,   198,   172,   188,    56,    57,    58,    59,
      60,   158,   159,   160,   161,   189,   190,   191,   192,   193,
     194,   195,   175,   179,     4,   291,   184,   185,   261,   206,
     212,   188,   213,   216,   219,   214,   220,   221,   222,   223,
     256,   189,   262,   263,   264,   265,   266,   267,   225,   226,
     230,   231,   236,   244,   245,   247,   260,   271,   249,   272,
     275,   229,   279,   280,   283,   281,   284,   287,  -150,  -151,
    -152,  -153,  -154,  -155,   289,   302,   292,   295,   299,   300,
     303,   308,   310,   311,   313,   314,   315,    74,   312,   248,
     301,   211,   204,   139,   243,   217,   305,   118,   253,   144,
     107,   252,     0,     0,   145
};

static const yytype_int16 yycheck[] =
{
       4,   101,   200,   201,   147,   133,   151,   115,    11,    33,
      46,    20,    20,    18,    73,    74,    52,    19,    12,    46,
      33,   121,    20,    19,    33,    33,    35,    36,    58,    30,
       6,    58,    33,     9,    30,    69,    66,    67,    68,    69,
      70,    46,   185,   171,     7,    69,   146,    31,   156,    85,
      86,    87,    88,    58,   154,    58,    69,    18,    52,   202,
      69,    69,    34,    66,    67,    68,   174,    70,    69,    71,
      72,    73,    74,    71,    72,    73,    74,    18,    33,    69,
     225,   259,    69,   226,    33,   283,   214,    43,     6,   232,
       8,    18,    96,   236,   237,   273,   196,    58,   276,   199,
     200,   201,    35,    36,    18,    66,    67,    68,     0,    70,
      18,    72,    38,    39,    69,   293,   216,    58,   296,    46,
      69,    48,    47,   223,    49,    66,    67,    68,    69,    70,
     230,    58,   275,    69,     3,    69,   236,    73,     9,    66,
      67,    68,    69,    70,    58,    47,   289,    49,    69,    69,
      58,    34,    66,    67,    68,    69,    70,    18,    66,    67,
      68,    20,    70,    20,    53,    54,    55,    56,    57,   269,
      69,    69,   272,    40,    60,   275,    44,    58,    18,    69,
      69,    41,    69,   283,    73,    66,    67,    68,    32,    70,
      69,    69,   196,     4,     5,   199,    69,    69,    37,    10,
      11,    12,    13,    14,    15,    16,    17,    70,    41,    19,
      21,    22,    23,    69,    69,   219,    18,    28,    29,    60,
      20,    20,    46,    47,    69,    49,    31,    69,    36,    40,
      20,    42,    69,    69,    45,    59,    60,    61,    62,    63,
      64,    65,    46,    47,    69,    49,    53,    54,    55,    56,
      57,    24,    25,    26,    27,    59,    60,    61,    62,    63,
      64,    65,    50,    69,    11,   269,    48,    18,    46,     6,
      19,    49,    18,    41,    51,    20,    69,    19,    69,    20,
     284,    59,    60,    61,    62,    63,    64,    65,    19,    18,
      18,    46,    18,    69,    66,    58,    19,    19,    69,    18,
      18,    49,    19,    19,    38,    20,    20,    69,    18,    18,
      18,    18,    18,    18,    18,    69,    19,    19,    19,    19,
      19,    19,    19,    19,    19,    19,    19,    18,   302,   211,
     280,   163,   155,   114,   204,   173,   284,    94,   218,   118,
      84,   216,    -1,    -1,   119
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    11,    12,    13,    14,    15,    16,
      17,    21,    22,    23,    28,    29,    40,    42,    45,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      90,    91,    92,    98,   105,   108,   112,   113,   128,   129,
     130,     6,     8,    89,     6,     9,    18,    58,    66,    67,
      68,    70,    72,   100,   114,   115,    53,    54,    55,    56,
      57,    69,    73,   116,   117,   118,   120,    69,     7,    31,
      34,    69,    69,    43,    78,     0,     3,   131,    69,     9,
      69,    69,   115,   115,    20,    71,    72,    73,    74,    30,
      33,    69,    34,    18,    20,   119,    20,   121,    69,    69,
      40,    60,    44,    18,    69,    41,    19,   114,   115,   115,
     115,   115,    69,    69,    69,   122,    69,    73,   118,   120,
      32,    37,   123,    69,   106,   100,    70,    69,    94,    41,
      69,    33,    69,    20,    33,    35,    36,    69,   101,   103,
     123,    19,    30,    19,   119,   121,    18,    18,    46,    48,
     100,   120,   124,   125,    60,    20,   107,    31,    24,    25,
      26,    27,    97,    20,    93,    69,    69,    69,   122,    69,
      36,    20,    69,   103,   104,    50,   111,    33,    69,    69,
      33,    69,   100,   112,    48,    18,    46,    47,    49,    59,
      60,    61,    62,    63,    64,    65,   126,    46,    47,   126,
      38,    39,    18,   100,   106,   123,     6,    18,    46,    58,
      95,    94,    19,    18,    20,   122,    41,   104,   123,    51,
      69,    19,    69,    20,    99,    19,    18,   112,    47,    49,
      18,    46,    18,   100,   120,    47,    18,    18,   100,   120,
     124,   124,   112,   107,    69,    66,    96,    58,    93,    69,
     122,   102,   125,   111,   109,   110,   120,    33,    69,   100,
      19,    46,    60,    61,    62,    63,    64,    65,   126,   127,
     112,    19,    18,   100,   112,    18,   100,   112,   112,    19,
      19,    20,    88,    38,    20,    12,    52,    69,    99,    18,
     100,   120,    19,   100,    99,    19,   100,   112,    99,    19,
      19,    95,    69,    19,   124,   110,   112,    99,    19,    99,
      19,    19,    88,    19,    19,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    88,    89,    89,    90,    91,    92,    93,
      93,    94,    94,    95,    95,    95,    96,    97,    97,    97,
      97,    98,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   103,   103,   104,   104,   105,   106,
     106,   107,   107,   108,   109,   109,   109,   110,   110,   110,
     111,   111,   112,   112,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   117,   117,   117,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   122,   122,   122,   122,   123,   123,   124,
     124,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   127,   127,   127,   127,   128,   129,   130,   131,
     131
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     0,     3,     0,     1,    10,     5,     7,     0,
       3,     6,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     8,     0,     3,     1,     1,     1,     1,     1,     1,
       2,     0,     1,     3,     4,     2,     0,     2,     4,     3,
       5,     0,     3,     6,     1,     2,     2,     0,     1,     3,
       0,     3,     6,     8,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     4,     6,     5,     4,     6,     5,     6,     8,
       7,     0,     3,     1,     3,     3,     2,     5,     4,     0,
       3,     1,     3,     2,     3,     4,     5,     0,     2,     0,
       1,     3,     3,     3,     3,     3,     3,     4,     5,     5,
       6,     5,     5,     5,     5,     6,     7,     6,     7,     7,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     7,     2,     4,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


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
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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

  YYLOCATION_PRINT (yyo, yylocationp);
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
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
#line 220 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1872 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 250 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 256 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 261 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 267 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1905 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 273 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1913 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 279 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 285 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1931 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 292 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1939 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 298 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1949 "yacc_sql.cpp"
    break;

  case 32: /* ind_list: %empty  */
#line 306 "yacc_sql.y"
    {
      (yyval.index_list) = nullptr;
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 33: /* ind_list: COMMA ID ind_list  */
#line 309 "yacc_sql.y"
                        {
      if((yyvsp[0].index_list) != nullptr){
        (yyval.index_list) = (yyvsp[0].index_list);
      }else{
        (yyval.index_list) = new std::vector<std::string>; 
      }
      (yyval.index_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 34: /* unique_token: %empty  */
#line 320 "yacc_sql.y"
           {
    (yyval.is_unique) = nullptr;
  }
#line 1979 "yacc_sql.cpp"
    break;

  case 35: /* unique_token: UNIQUE  */
#line 323 "yacc_sql.y"
           {
    (yyval.is_unique) = new std::string("uniqueistrue");
  }
#line 1987 "yacc_sql.cpp"
    break;

  case 36: /* create_index_stmt: CREATE unique_token INDEX ID ON ID LBRACE ID ind_list RBRACE  */
#line 328 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      if((yyvsp[-8].is_unique) != nullptr){
        create_index.is_unique = *(yyvsp[-8].is_unique);
        delete (yyvsp[-8].is_unique);
      }
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
#line 2012 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 352 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 362 "yacc_sql.y"
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
#line 2044 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: %empty  */
#line 380 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2052 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 384 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2066 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE attr_can_null  */
#line 397 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->can_null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2079 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type attr_can_null  */
#line 406 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->can_null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 43: /* attr_can_null: %empty  */
#line 417 "yacc_sql.y"
  {
    (yyval.bools) = true;
  }
#line 2100 "yacc_sql.cpp"
    break;

  case 44: /* attr_can_null: NOT NULL_T  */
#line 420 "yacc_sql.y"
               {
    (yyval.bools) = false;
  }
#line 2108 "yacc_sql.cpp"
    break;

  case 45: /* attr_can_null: NULL_T  */
#line 423 "yacc_sql.y"
           {
    (yyval.bools) = true;
  }
#line 2116 "yacc_sql.cpp"
    break;

  case 46: /* number: NUMBER  */
#line 429 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2122 "yacc_sql.cpp"
    break;

  case 47: /* type: INT_T  */
#line 432 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2128 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 433 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2134 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 434 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2140 "yacc_sql.cpp"
    break;

  case 50: /* type: DATE_T  */
#line 435 "yacc_sql.y"
             { (yyval.number)=DATES; }
#line 2146 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 439 "yacc_sql.y"
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
#line 2162 "yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 454 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2170 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 457 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2184 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 468 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2193 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 472 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2202 "yacc_sql.cpp"
    break;

  case 56: /* value: DATE_STR  */
#line 476 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value();
      (yyval.value)->set_date(tmp);
      free(tmp);
    }
#line 2213 "yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 482 "yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_null(true);
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 486 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2232 "yacc_sql.cpp"
    break;

  case 59: /* join_expr: JOIN  */
#line 495 "yacc_sql.y"
  {
    (yyval.join_type) = JOIN_TABLE;

  }
#line 2241 "yacc_sql.cpp"
    break;

  case 60: /* join_expr: INNER JOIN  */
#line 500 "yacc_sql.y"
  {
    (yyval.join_type) = INNER_JOIN_TABLE;
  }
#line 2249 "yacc_sql.cpp"
    break;

  case 61: /* on_condition_exprs: %empty  */
#line 507 "yacc_sql.y"
  {
    (yyval.condition_list) = nullptr;
  }
#line 2257 "yacc_sql.cpp"
    break;

  case 62: /* on_condition_exprs: condition  */
#line 511 "yacc_sql.y"
  {
    (yyval.condition_list) = new std::vector<ConditionSqlNode>;
    (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
    delete (yyvsp[0].condition);
  }
#line 2267 "yacc_sql.cpp"
    break;

  case 63: /* on_condition_exprs: condition AND condition_list  */
#line 516 "yacc_sql.y"
                                 {
    (yyval.condition_list) = (yyvsp[0].condition_list);
    (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
    delete (yyvsp[-2].condition);
  }
#line 2277 "yacc_sql.cpp"
    break;

  case 64: /* join_table: join_expr ID ON on_condition_exprs  */
#line 525 "yacc_sql.y"
  {
    (yyval.join_table) = new JoinTableSqlNode;
    (yyval.join_table)->table_name = (yyvsp[-2].string);
    free((yyvsp[-2].string));

    if ((yyvsp[0].condition_list) != nullptr) {
      (yyval.join_table)->on_conditions = *(yyvsp[0].condition_list);
    }
    delete (yyvsp[0].condition_list);
  }
#line 2292 "yacc_sql.cpp"
    break;

  case 65: /* join_table: join_expr ID  */
#line 536 "yacc_sql.y"
  {
    (yyval.join_table) = new JoinTableSqlNode;
    (yyval.join_table)->table_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2302 "yacc_sql.cpp"
    break;

  case 66: /* join_tables: %empty  */
#line 544 "yacc_sql.y"
    {
      (yyval.join_table_list) = nullptr;
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 67: /* join_tables: join_table join_tables  */
#line 548 "yacc_sql.y"
    { 
      if ((yyvsp[0].join_table_list) == nullptr) {
        (yyval.join_table_list) = new std::vector<JoinTableSqlNode>;
      } else {
        (yyval.join_table_list) = (yyvsp[0].join_table_list);
      }

      (yyval.join_table_list)->push_back(*(yyvsp[-1].join_table));
      delete (yyvsp[-1].join_table);
    }
#line 2325 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 561 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 69: /* update_expr: ID EQ value  */
#line 573 "yacc_sql.y"
             {
    (yyval.condition) = new ConditionSqlNode();
    (yyval.condition)->left_is_attr = 1;
    (yyval.condition)->left_attr.attribute_name = (yyvsp[-2].string);
    (yyval.condition)->right_is_attr = 0;
    (yyval.condition)->right_is_sub_query = 0;
    (yyval.condition)->right_value = *(yyvsp[0].value);
    (yyval.condition)->comp = EQUAL_TO;
    
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2356 "yacc_sql.cpp"
    break;

  case 70: /* update_expr: ID EQ LBRACE select_stmt RBRACE  */
#line 585 "yacc_sql.y"
                                   {
    (yyval.condition) = new ConditionSqlNode();
    (yyval.condition)->left_is_attr = 1;
    (yyval.condition)->left_attr.attribute_name = (yyvsp[-4].string);
    (yyval.condition)->right_is_attr = 0;
    (yyval.condition)->right_is_sub_query = 1;
    (yyval.condition)->right_sub_query = make_shared<SelectSqlNode>((*(yyvsp[-1].sql_node)).selection);
    (yyval.condition)->comp = EQUAL_TO;
  
    free((yyvsp[-4].string));
    delete (yyvsp[-1].sql_node);
  }
#line 2373 "yacc_sql.cpp"
    break;

  case 71: /* update_exprs: %empty  */
#line 599 "yacc_sql.y"
           {
    (yyval.condition_list) = nullptr;
  }
#line 2381 "yacc_sql.cpp"
    break;

  case 72: /* update_exprs: COMMA update_expr update_exprs  */
#line 602 "yacc_sql.y"
                                  {
    if((yyvsp[0].condition_list) == nullptr){
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
    }
    else {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
    (yyval.condition_list)->push_back(*(yyvsp[-1].condition));

    delete (yyvsp[-1].condition);
  }
#line 2397 "yacc_sql.cpp"
    break;

  case 73: /* update_stmt: UPDATE ID SET update_expr update_exprs where  */
#line 616 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      (yyval.sql_node)->update.update_conditions.push_back(*(yyvsp[-2].condition));
      
      free((yyvsp[-4].string));
      delete (yyvsp[-2].condition);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      if ((yyvsp[-1].condition_list) != nullptr){
        for(int i = 0; i < (int)(yyvsp[-1].condition_list)->size(); i++){
          (yyval.sql_node)->update.update_conditions.push_back((yyvsp[-1].condition_list)->at(i));
        }
        delete (yyvsp[-1].condition_list);
      }
    }
#line 2420 "yacc_sql.cpp"
    break;

  case 74: /* order_by_attr: rel_attr  */
#line 638 "yacc_sql.y"
  {
    (yyval.order_by) = new OrderBySqlNode();
    (yyval.order_by)->rel_name = *(yyvsp[0].rel_attr);
    delete (yyvsp[0].rel_attr);
  }
#line 2430 "yacc_sql.cpp"
    break;

  case 75: /* order_by_attr: rel_attr ASC  */
#line 644 "yacc_sql.y"
  {
    (yyval.order_by) = new OrderBySqlNode();
    (yyval.order_by)->rel_name = *(yyvsp[-1].rel_attr);
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by)->order_by = ORDER_ASC;
  }
#line 2441 "yacc_sql.cpp"
    break;

  case 76: /* order_by_attr: rel_attr DESC  */
#line 651 "yacc_sql.y"
  {
    (yyval.order_by) = new OrderBySqlNode();
    (yyval.order_by)->rel_name = *(yyvsp[-1].rel_attr);
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by)->order_by = ORDER_DESC;
  }
#line 2452 "yacc_sql.cpp"
    break;

  case 77: /* order_by_attrs: %empty  */
#line 660 "yacc_sql.y"
  {
    (yyval.order_bys) = nullptr;
  }
#line 2460 "yacc_sql.cpp"
    break;

  case 78: /* order_by_attrs: order_by_attr  */
#line 664 "yacc_sql.y"
  {
    (yyval.order_bys) = new vector<OrderBySqlNode>();
    (yyval.order_bys)->emplace_back(*(yyvsp[0].order_by));
    delete (yyvsp[0].order_by);
  }
#line 2470 "yacc_sql.cpp"
    break;

  case 79: /* order_by_attrs: order_by_attr COMMA order_by_attrs  */
#line 669 "yacc_sql.y"
                                       {
    if ((yyval.order_bys) == nullptr) {
      (yyval.order_bys) = new std::vector<OrderBySqlNode>();
    } else {
      (yyval.order_bys) = (yyvsp[0].order_bys);
    }
    (yyval.order_bys)->emplace_back(*(yyvsp[-2].order_by));
    delete (yyvsp[-2].order_by);
  }
#line 2484 "yacc_sql.cpp"
    break;

  case 80: /* order_by: %empty  */
#line 682 "yacc_sql.y"
  {
    (yyval.order_bys) = nullptr;
  }
#line 2492 "yacc_sql.cpp"
    break;

  case 81: /* order_by: ORDER BY order_by_attrs  */
#line 686 "yacc_sql.y"
  {
    (yyval.order_bys) = (yyvsp[0].order_bys);
  }
#line 2500 "yacc_sql.cpp"
    break;

  case 82: /* select_stmt: SELECT select_attr FROM rel_list where order_by  */
#line 693 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-4].rel_attr_list));
        delete (yyvsp[-4].rel_attr_list);
      }
      if ((yyvsp[-2].rel_attr_list) != nullptr){
        for(auto itr = (yyvsp[-2].rel_attr_list)->rbegin(); itr < (yyvsp[-2].rel_attr_list)->rend(); itr ++){
          (yyval.sql_node)->selection.on_conditions.push_back(vector<ConditionSqlNode>());
          (yyval.sql_node)->selection.relations.push_back(itr->relation_name);
          (yyval.sql_node)->selection.rel_alias.push_back(itr->alias);
        }
        delete (yyvsp[-2].rel_attr_list);
      }

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_bys) != nullptr) {
        (yyval.sql_node)->selection.order_bys.swap(*(yyvsp[0].order_bys));
        std::reverse((yyval.sql_node)->selection.order_bys.begin(), (yyval.sql_node)->selection.order_bys.end());
        delete (yyvsp[0].order_bys);
      } 
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 83: /* select_stmt: SELECT select_attr FROM ID join_table join_tables where order_by  */
#line 720 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_list));
        delete (yyvsp[-6].rel_attr_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
      (yyval.sql_node)->selection.rel_alias.push_back(std::string());
      if ((yyvsp[-2].join_table_list) != nullptr) {
        int i = 0;
        for(i = 0; i < (int)(yyvsp[-2].join_table_list)->size(); i++) {
          (yyval.sql_node)->selection.relations.push_back((*(yyvsp[-2].join_table_list))[i].table_name);
          (yyval.sql_node)->selection.rel_alias.push_back(std::string());
          (yyval.sql_node)->selection.on_conditions.push_back((*(yyvsp[-2].join_table_list))[i].on_conditions);
        }
        delete (yyvsp[-2].join_table_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-3].join_table)->table_name);
      (yyval.sql_node)->selection.on_conditions.push_back((yyvsp[-3].join_table)->on_conditions);
      (yyval.sql_node)->selection.rel_alias.push_back(std::string());
      std::reverse((yyval.sql_node)->selection.relations.begin() + 1, (yyval.sql_node)->selection.relations.end());
      std::reverse((yyval.sql_node)->selection.on_conditions.begin(), (yyval.sql_node)->selection.on_conditions.end());
      delete (yyvsp[-3].join_table);

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      free((yyvsp[-4].string));
      if ((yyvsp[0].order_bys) != nullptr) {
        (yyval.sql_node)->selection.order_bys.swap(*(yyvsp[0].order_bys));
        std::reverse((yyval.sql_node)->selection.order_bys.begin(), (yyval.sql_node)->selection.order_bys.end());
        delete (yyvsp[0].order_bys);
      }    
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 84: /* calc_stmt: CALC expression_list  */
#line 758 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 85: /* expression_list: expression  */
#line 768 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression COMMA expression_list  */
#line 773 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '+' expression  */
#line 783 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '-' expression  */
#line 786 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '*' expression  */
#line 789 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '/' expression  */
#line 792 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 91: /* expression: LBRACE expression RBRACE  */
#line 795 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 92: /* expression: '-' expression  */
#line 799 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 93: /* expression: value  */
#line 802 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 94: /* select_attr: '*'  */
#line 810 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 95: /* select_attr: rel_attr attr_list  */
#line 817 "yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2689 "yacc_sql.cpp"
    break;

  case 96: /* select_attr: aggr_func aggr_func_list  */
#line 826 "yacc_sql.y"
                              {
      if ((yyvsp[0].rel_attr_list) != nullptr){
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 97: /* aggr_op: MAX  */
#line 838 "yacc_sql.y"
      {
    (yyval.aggr_op) = AGG_MAX;
  }
#line 2711 "yacc_sql.cpp"
    break;

  case 98: /* aggr_op: AVG  */
#line 841 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_AVG;
  }
#line 2719 "yacc_sql.cpp"
    break;

  case 99: /* aggr_op: SUM  */
#line 844 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_SUM;
  }
#line 2727 "yacc_sql.cpp"
    break;

  case 100: /* aggr_op: MIN  */
#line 847 "yacc_sql.y"
        {
    (yyval.aggr_op) = AGG_MIN;
  }
#line 2735 "yacc_sql.cpp"
    break;

  case 101: /* aggr_op: COUNT  */
#line 850 "yacc_sql.y"
          {
    (yyval.aggr_op) = AGG_COUNT;
  }
#line 2743 "yacc_sql.cpp"
    break;

  case 102: /* aggr_func: aggr_op LBRACE '*' RBRACE  */
#line 856 "yacc_sql.y"
                            {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name = "";
    (yyval.rel_attr)->attribute_name = '*';
    (yyval.rel_attr)->aggr_op = (yyvsp[-3].aggr_op);
  }
#line 2754 "yacc_sql.cpp"
    break;

  case 103: /* aggr_func: aggr_op LBRACE '*' RBRACE AS ID  */
#line 862 "yacc_sql.y"
                                   {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name = "";
    (yyval.rel_attr)->attribute_name = '*';
    (yyval.rel_attr)->alias = (yyvsp[0].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-5].aggr_op);

    free((yyvsp[0].string));
  }
#line 2768 "yacc_sql.cpp"
    break;

  case 104: /* aggr_func: aggr_op LBRACE '*' RBRACE ID  */
#line 871 "yacc_sql.y"
                                 {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name = "";
    (yyval.rel_attr)->attribute_name = '*';
    (yyval.rel_attr)->alias = (yyvsp[0].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-4].aggr_op);

    free((yyvsp[0].string));
  }
#line 2782 "yacc_sql.cpp"
    break;

  case 105: /* aggr_func: aggr_op LBRACE ID RBRACE  */
#line 880 "yacc_sql.y"
                             {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-3].aggr_op);
    free((yyvsp[-1].string));    
  }
#line 2793 "yacc_sql.cpp"
    break;

  case 106: /* aggr_func: aggr_op LBRACE ID RBRACE AS ID  */
#line 886 "yacc_sql.y"
                                  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
    (yyval.rel_attr)->alias = (yyvsp[0].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-5].aggr_op);
    free((yyvsp[-3].string)); 
    free((yyvsp[0].string));
  }
#line 2806 "yacc_sql.cpp"
    break;

  case 107: /* aggr_func: aggr_op LBRACE ID RBRACE ID  */
#line 894 "yacc_sql.y"
                               {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
    (yyval.rel_attr)->alias = (yyvsp[0].string);
    (yyval.rel_attr)->aggr_op = (yyvsp[-4].aggr_op);
    free((yyvsp[-2].string)); 
    free((yyvsp[0].string));
  }
#line 2819 "yacc_sql.cpp"
    break;

  case 108: /* aggr_func: aggr_op LBRACE ID DOT ID RBRACE  */
#line 902 "yacc_sql.y"
                                    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_op = (yyvsp[-5].aggr_op);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
  }
#line 2832 "yacc_sql.cpp"
    break;

  case 109: /* aggr_func: aggr_op LBRACE ID DOT ID RBRACE AS ID  */
#line 910 "yacc_sql.y"
                                          {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-5].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_op = (yyvsp[-7].aggr_op);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[0].string));
  }
#line 2847 "yacc_sql.cpp"
    break;

  case 110: /* aggr_func: aggr_op LBRACE ID DOT ID RBRACE ID  */
#line 920 "yacc_sql.y"
                                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_op = (yyvsp[-6].aggr_op);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
  }
#line 2862 "yacc_sql.cpp"
    break;

  case 111: /* aggr_func_list: %empty  */
#line 934 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 112: /* aggr_func_list: COMMA aggr_func aggr_func_list  */
#line 937 "yacc_sql.y"
                                     {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 113: /* rel_attr: ID  */
#line 949 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 114: /* rel_attr: ID DOT ID  */
#line 954 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2906 "yacc_sql.cpp"
    break;

  case 115: /* rel_attr: ID AS ID  */
#line 961 "yacc_sql.y"
               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 116: /* rel_attr: ID ID  */
#line 968 "yacc_sql.y"
           {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 117: /* rel_attr: ID DOT ID AS ID  */
#line 975 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr: ID DOT ID ID  */
#line 984 "yacc_sql.y"
                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 119: /* attr_list: %empty  */
#line 996 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 120: /* attr_list: COMMA rel_attr attr_list  */
#line 999 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 121: /* rel_list: ID  */
#line 1011 "yacc_sql.y"
      {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[0].string);
      (yyval.rel_attr_list)->push_back(*this_rel);
      
      delete this_rel;
      free((yyvsp[0].string));
    }
#line 2995 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: ID COMMA rel_list  */
#line 1020 "yacc_sql.y"
                       {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr_list)->push_back(*this_rel);

      delete this_rel;
      free((yyvsp[-2].string));
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 123: /* rel_list: ID ID  */
#line 1029 "yacc_sql.y"
           {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[-1].string);
      this_rel->alias =(yyvsp[0].string);
      (yyval.rel_attr_list)->push_back(*this_rel);
      
      delete this_rel;
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 124: /* rel_list: ID AS ID  */
#line 1040 "yacc_sql.y"
               {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[-2].string);
      this_rel->alias =(yyvsp[0].string);
      (yyval.rel_attr_list)->push_back(*this_rel);
      
      delete this_rel;
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 125: /* rel_list: ID ID COMMA rel_list  */
#line 1051 "yacc_sql.y"
                          {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[-3].string);
      this_rel->alias = (yyvsp[-2].string);
      (yyval.rel_attr_list)->push_back(*this_rel);
      
      delete this_rel;
      free((yyvsp[-3].string));
      free((yyvsp[-2].string));
    }
#line 3057 "yacc_sql.cpp"
    break;

  case 126: /* rel_list: ID AS ID COMMA rel_list  */
#line 1062 "yacc_sql.y"
                             {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      RelAttrSqlNode* this_rel = new RelAttrSqlNode();
      this_rel->relation_name = (yyvsp[-4].string);
      this_rel->alias = (yyvsp[-2].string);
      (yyval.rel_attr_list)->push_back(*this_rel);
      
      delete this_rel;
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3073 "yacc_sql.cpp"
    break;

  case 127: /* where: %empty  */
#line 1076 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 128: /* where: WHERE condition_list  */
#line 1079 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: %empty  */
#line 1085 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3097 "yacc_sql.cpp"
    break;

  case 130: /* condition_list: condition  */
#line 1088 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3107 "yacc_sql.cpp"
    break;

  case 131: /* condition_list: condition AND condition_list  */
#line 1093 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 132: /* condition_list: condition OR condition_list  */
#line 1098 "yacc_sql.y"
                                 {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
      (yyval.condition_list)->front().is_or = true;
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 133: /* condition: rel_attr comp_op value  */
#line 1107 "yacc_sql.y"
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
#line 3144 "yacc_sql.cpp"
    break;

  case 134: /* condition: value comp_op value  */
#line 1119 "yacc_sql.y"
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
#line 3160 "yacc_sql.cpp"
    break;

  case 135: /* condition: rel_attr comp_op rel_attr  */
#line 1131 "yacc_sql.y"
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
#line 3176 "yacc_sql.cpp"
    break;

  case 136: /* condition: value comp_op rel_attr  */
#line 1143 "yacc_sql.y"
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
#line 3192 "yacc_sql.cpp"
    break;

  case 137: /* condition: EXISTS LBRACE select_stmt RBRACE  */
#line 1155 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = EXISTS_OP;

      delete (yyvsp[-1].sql_node);
    }
#line 3208 "yacc_sql.cpp"
    break;

  case 138: /* condition: NOT EXISTS LBRACE select_stmt RBRACE  */
#line 1167 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = NOT_EXISTS_OP;

      delete (yyvsp[-1].sql_node);
    }
#line 3224 "yacc_sql.cpp"
    break;

  case 139: /* condition: rel_attr IN LBRACE select_stmt RBRACE  */
#line 1179 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = IN_OP;

      delete (yyvsp[-4].rel_attr);
      delete (yyvsp[-1].sql_node);
    }
#line 3242 "yacc_sql.cpp"
    break;

  case 140: /* condition: rel_attr NOT IN LBRACE select_stmt RBRACE  */
#line 1193 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = NOT_IN_OP;

      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-1].sql_node);
    }
#line 3260 "yacc_sql.cpp"
    break;

  case 141: /* condition: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 1207 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].rel_attr);
      delete (yyvsp[-1].sql_node);
    }
#line 3278 "yacc_sql.cpp"
    break;

  case 142: /* condition: value comp_op LBRACE select_stmt RBRACE  */
#line 1221 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_attr;
      (yyval.condition)->left_value = *(yyvsp[-4].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].value);
      delete (yyvsp[-1].sql_node);
    }
#line 3296 "yacc_sql.cpp"
    break;

  case 143: /* condition: LBRACE select_stmt RBRACE comp_op_reverse value  */
#line 1235 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_attr;
      (yyval.condition)->left_value = *(yyvsp[0].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-3].sql_node);
      delete (yyvsp[0].value);
    }
#line 3314 "yacc_sql.cpp"
    break;

  case 144: /* condition: LBRACE select_stmt RBRACE comp_op_reverse rel_attr  */
#line 1249 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-3].sql_node)->selection);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-3].sql_node);
      delete (yyvsp[0].rel_attr);
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 145: /* condition: rel_attr IN LBRACE value value_list RBRACE  */
#line 1262 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->right_sub_query;
      (yyval.condition)->comp = IN_OP;

      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-2].value);
    }
#line 3354 "yacc_sql.cpp"
    break;

  case 146: /* condition: rel_attr NOT IN LBRACE value value_list RBRACE  */
#line 1279 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-6].rel_attr);
      (yyval.condition)->left_value;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->right_sub_query;
      (yyval.condition)->comp = NOT_IN_OP;

      delete (yyvsp[-6].rel_attr);
      delete (yyvsp[-2].value);
    }
#line 3376 "yacc_sql.cpp"
    break;

  case 147: /* condition: value IN LBRACE value value_list RBRACE  */
#line 1296 "yacc_sql.y"
                                             {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_attr;
      (yyval.condition)->left_value = *(yyvsp[-5].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = IN_OP;

      delete (yyvsp[-5].value);
      delete (yyvsp[-2].value);
    }
#line 3398 "yacc_sql.cpp"
    break;

  case 148: /* condition: value NOT IN LBRACE value value_list RBRACE  */
#line 1314 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_attr;
      (yyval.condition)->left_value = *(yyvsp[-6].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = NOT_IN_OP;

      delete (yyvsp[-6].value);
      delete (yyvsp[-2].value);
    }
#line 3420 "yacc_sql.cpp"
    break;

  case 149: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1332 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_is_sub_query = 1;
      (yyval.condition)->left_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-5].sql_node)->selection);
     
      (yyval.condition)->comp = (yyvsp[-3].comp);
      
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_is_sub_query = 1;
      (yyval.condition)->right_sub_query = std::make_shared<SelectSqlNode>((yyvsp[-1].sql_node)->selection);

      delete (yyvsp[-5].sql_node);
      delete (yyvsp[-1].sql_node);
    }
#line 3441 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: EQ  */
#line 1351 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3447 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: LT  */
#line 1352 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3453 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: GT  */
#line 1353 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3459 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: LE  */
#line 1354 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3465 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: GE  */
#line 1355 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3471 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: NE  */
#line 1356 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3477 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: NOT LIKE  */
#line 1357 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3483 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: LIKE  */
#line 1358 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3489 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: IS  */
#line 1359 "yacc_sql.y"
         { (yyval.comp) = IS_OP; }
#line 3495 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: IS NOT  */
#line 1360 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_OP; }
#line 3501 "yacc_sql.cpp"
    break;

  case 160: /* comp_op_reverse: EQ  */
#line 1364 "yacc_sql.y"
       { (yyval.comp) = EQUAL_TO; }
#line 3507 "yacc_sql.cpp"
    break;

  case 161: /* comp_op_reverse: LT  */
#line 1365 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3513 "yacc_sql.cpp"
    break;

  case 162: /* comp_op_reverse: GT  */
#line 1366 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3519 "yacc_sql.cpp"
    break;

  case 163: /* comp_op_reverse: LE  */
#line 1367 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3525 "yacc_sql.cpp"
    break;

  case 164: /* comp_op_reverse: GE  */
#line 1368 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3531 "yacc_sql.cpp"
    break;

  case 165: /* comp_op_reverse: NE  */
#line 1369 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3537 "yacc_sql.cpp"
    break;

  case 166: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1373 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3551 "yacc_sql.cpp"
    break;

  case 167: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1386 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3560 "yacc_sql.cpp"
    break;

  case 168: /* set_variable_stmt: SET ID EQ value  */
#line 1394 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3572 "yacc_sql.cpp"
    break;


#line 3576 "yacc_sql.cpp"

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
          YYNOMEM;
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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 1406 "yacc_sql.y"

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
