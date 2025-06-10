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
#include "tabela_simbolos.h"
#include "llvm_lib.h"
#include "compilador.h"

int yylex();
extern FILE *yyin;
extern int yylineno;
FILE *log_file, *out_file;

tabela_simbolos_t* tab_simbolos = NULL;
int escopo_atual = 0;
int variaveis_num = 0;
int temp_count = 0;

int dentro_de_funcao = 0;

int if_count = 0;

#line 94 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_OPERADOR_RELACIONAL = 4,        /* OPERADOR_RELACIONAL  */
  YYSYMBOL_NUM = 5,                        /* NUM  */
  YYSYMBOL_OPERADOR_MULTIPLICATIVO = 6,    /* OPERADOR_MULTIPLICATIVO  */
  YYSYMBOL_OR = 7,                         /* OR  */
  YYSYMBOL_MENOS = 8,                      /* MENOS  */
  YYSYMBOL_MAIS = 9,                       /* MAIS  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_OPERADOR_ATRIBUICAO = 12,       /* OPERADOR_ATRIBUICAO  */
  YYSYMBOL_DO = 13,                        /* DO  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_END = 16,                       /* END  */
  YYSYMBOL_BEGIN_TOKEN = 17,               /* BEGIN_TOKEN  */
  YYSYMBOL_DOIS_PONTOS = 18,               /* DOIS_PONTOS  */
  YYSYMBOL_PONTO_VIRGULA = 19,             /* PONTO_VIRGULA  */
  YYSYMBOL_FECHA_PARENTESES = 20,          /* FECHA_PARENTESES  */
  YYSYMBOL_ABRE_PARENTESES = 21,           /* ABRE_PARENTESES  */
  YYSYMBOL_FUNCTION = 22,                  /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 23,                 /* PROCEDURE  */
  YYSYMBOL_REAL = 24,                      /* REAL  */
  YYSYMBOL_INTEIRO = 25,                   /* INTEIRO  */
  YYSYMBOL_VAR = 26,                       /* VAR  */
  YYSYMBOL_PONTO_FINAL = 27,               /* PONTO_FINAL  */
  YYSYMBOL_PROGRAM = 28,                   /* PROGRAM  */
  YYSYMBOL_EOL = 29,                       /* EOL  */
  YYSYMBOL_VIRGULA = 30,                   /* VIRGULA  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_PROGRAMA = 36,                  /* PROGRAMA  */
  YYSYMBOL_37_1 = 37,                      /* $@1  */
  YYSYMBOL_38_2 = 38,                      /* $@2  */
  YYSYMBOL_39_3 = 39,                      /* $@3  */
  YYSYMBOL_LISTA_DE_IDENTIFICADORES = 40,  /* LISTA_DE_IDENTIFICADORES  */
  YYSYMBOL_DECLARACOES = 41,               /* DECLARACOES  */
  YYSYMBOL_TIPO = 42,                      /* TIPO  */
  YYSYMBOL_DECLARACOES_DE_SUBPROGRAMAS = 43, /* DECLARACOES_DE_SUBPROGRAMAS  */
  YYSYMBOL_DECLARACAO_DE_SUBPROGRAMA = 44, /* DECLARACAO_DE_SUBPROGRAMA  */
  YYSYMBOL_45_4 = 45,                      /* $@4  */
  YYSYMBOL_CABECALHO_DE_SUBPROGRAMA = 46,  /* CABECALHO_DE_SUBPROGRAMA  */
  YYSYMBOL_47_5 = 47,                      /* $@5  */
  YYSYMBOL_48_6 = 48,                      /* $@6  */
  YYSYMBOL_49_7 = 49,                      /* $@7  */
  YYSYMBOL_50_8 = 50,                      /* $@8  */
  YYSYMBOL_ARGUMENTOS = 51,                /* ARGUMENTOS  */
  YYSYMBOL_LISTA_DE_PARAMETROS = 52,       /* LISTA_DE_PARAMETROS  */
  YYSYMBOL_ENUNCIADO_COMPOSTO = 53,        /* ENUNCIADO_COMPOSTO  */
  YYSYMBOL_ENUNCIADOS_OPCIONAIS = 54,      /* ENUNCIADOS_OPCIONAIS  */
  YYSYMBOL_LISTA_DE_ENUNCIADOS = 55,       /* LISTA_DE_ENUNCIADOS  */
  YYSYMBOL_ENUNCIADO = 56,                 /* ENUNCIADO  */
  YYSYMBOL_57_9 = 57,                      /* $@9  */
  YYSYMBOL_58_10 = 58,                     /* $@10  */
  YYSYMBOL_VARIAVEL = 59,                  /* VARIAVEL  */
  YYSYMBOL_CHAMADA_DE_PROCEDIMENTO = 60,   /* CHAMADA_DE_PROCEDIMENTO  */
  YYSYMBOL_LISTA_DE_EXPRESSOES = 61,       /* LISTA_DE_EXPRESSOES  */
  YYSYMBOL_EXPRESSAO = 62,                 /* EXPRESSAO  */
  YYSYMBOL_EXPRESSAO_SIMPLES = 63,         /* EXPRESSAO_SIMPLES  */
  YYSYMBOL_TERMO = 64,                     /* TERMO  */
  YYSYMBOL_FATOR = 65,                     /* FATOR  */
  YYSYMBOL_SINAL = 66                      /* SINAL  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
       2,     2,    33,    31,     2,    32,     2,    34,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    58,    61,    56,    66,    67,    70,    71,
      74,    75,    78,    79,    82,    82,    95,   103,    94,   109,
     110,   108,   113,   114,   117,   119,   121,   123,   127,   130,
     131,   134,   135,   138,   148,   149,   150,   155,   150,   156,
     159,   162,   163,   166,   167,   170,   171,   174,   175,   178,
     181,   184,   187,   188,   193,   215,   234,   254,   259,   260
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID",
  "OPERADOR_RELACIONAL", "NUM", "OPERADOR_MULTIPLICATIVO", "OR", "MENOS",
  "MAIS", "IF", "WHILE", "OPERADOR_ATRIBUICAO", "DO", "ELSE", "THEN",
  "END", "BEGIN_TOKEN", "DOIS_PONTOS", "PONTO_VIRGULA", "FECHA_PARENTESES",
  "ABRE_PARENTESES", "FUNCTION", "PROCEDURE", "REAL", "INTEIRO", "VAR",
  "PONTO_FINAL", "PROGRAM", "EOL", "VIRGULA", "'+'", "'-'", "'*'", "'/'",
  "$accept", "PROGRAMA", "$@1", "$@2", "$@3", "LISTA_DE_IDENTIFICADORES",
  "DECLARACOES", "TIPO", "DECLARACOES_DE_SUBPROGRAMAS",
  "DECLARACAO_DE_SUBPROGRAMA", "$@4", "CABECALHO_DE_SUBPROGRAMA", "$@5",
  "$@6", "$@7", "$@8", "ARGUMENTOS", "LISTA_DE_PARAMETROS",
  "ENUNCIADO_COMPOSTO", "ENUNCIADOS_OPCIONAIS", "LISTA_DE_ENUNCIADOS",
  "ENUNCIADO", "$@9", "$@10", "VARIAVEL", "CHAMADA_DE_PROCEDIMENTO",
  "LISTA_DE_EXPRESSOES", "EXPRESSAO", "EXPRESSAO_SIMPLES", "TERMO",
  "FATOR", "SINAL", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-64)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-41)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -27,    41,    21,    -3,   -64,    58,   -64,    -8,    46,    66,
     -64,   -64,    52,    58,   -64,    -1,    -7,    50,    76,    78,
     -64,    63,   -64,   -64,   -64,    64,   -64,   -64,    67,   -64,
      52,   -64,    65,    65,    30,    60,    67,     2,    70,   -64,
      37,     5,     5,   -64,    69,    71,   -64,    77,   -64,   -64,
     -64,    58,     1,    57,    50,    72,     5,    73,   -64,   -64,
     -64,     5,   -64,    59,    86,   -64,     6,    80,   -64,    30,
       5,    16,    50,     4,   -64,   -64,   -64,    15,   -64,     5,
      75,    81,     5,     5,     5,     5,     6,    86,    30,   -64,
     -64,    50,   -64,    58,    18,    79,   -64,     5,    23,   -64,
      30,    43,    43,    43,    43,   -64,   -64,   -64,    24,    50,
     -64,   -64,   -64,   -64,    50,   -64,    83,   -64,    30,   -64
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     6,     0,     0,     0,
       9,     7,     2,     0,    13,     0,     3,     0,     0,     0,
       4,     0,     9,    11,    10,     0,    16,    19,     0,    12,
      14,     8,    23,    23,    30,     0,     0,     0,     0,    20,
      41,     0,     0,    35,     0,    29,    31,     0,    34,     5,
      15,     0,     0,     0,     0,     0,     0,    54,    56,    59,
      58,     0,    36,    45,    47,    52,     0,     0,    28,     0,
       0,     0,     0,     0,    22,    17,    21,     0,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,    32,
      33,     0,    24,     0,     0,     0,    42,     0,     0,    57,
       0,    46,    51,    50,    49,    53,    39,    25,     0,     0,
      18,    44,    55,    37,     0,    26,     0,    27,     0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -64,   -64,   -64,   -64,   -13,    82,   -52,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,    68,   -64,    28,   -64,
     -64,   -63,   -64,   -64,   -64,   -64,    20,   -38,   -12,    34,
      17,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    14,    20,    28,     7,    12,    25,    16,    21,
      36,    22,    32,    95,    33,    55,    38,    53,    43,    44,
      45,    46,    81,   116,    47,    48,    77,    78,    63,    64,
      65,    66
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,     1,    75,    62,    67,     6,    89,     6,    57,    57,
      58,    58,     8,    59,    60,    18,    19,    17,     5,    72,
      92,     4,     9,    80,    52,   106,    61,    61,    51,     9,
      93,     9,    90,    40,    91,    96,   109,   113,    71,   107,
      41,    42,   114,   112,     3,    97,     9,    34,     9,   -40,
      83,    84,    85,    97,     9,   119,    35,   115,    56,   111,
      94,     6,   117,    82,    50,    10,    83,    84,    85,    11,
     101,   102,   103,   104,    23,    24,    73,    74,    13,    26,
     108,    27,    29,    31,    34,    68,    37,    49,    54,    70,
      69,    76,    86,    88,    79,    99,   100,   118,   110,    98,
      87,    39,     0,   105,    30
};

static const yytype_int8 yycheck[] =
{
      13,    28,    54,    41,    42,     3,    69,     3,     3,     3,
       5,     5,    20,     8,     9,    22,    23,    18,    21,    18,
      72,     0,    30,    61,    37,    88,    21,    21,    26,    30,
      26,    30,    70,     3,    18,    20,    18,   100,    51,    91,
      10,    11,    18,    20,     3,    30,    30,    17,    30,    12,
       7,     8,     9,    30,    30,   118,    28,   109,    21,    97,
      73,     3,   114,     4,    36,    19,     7,     8,     9,     3,
      82,    83,    84,    85,    24,    25,    19,    20,    26,     3,
      93,     3,    19,    19,    17,    16,    21,    27,    18,    12,
      19,    19,     6,    13,    21,    20,    15,    14,    19,    79,
      66,    33,    -1,    86,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    36,     3,     0,    21,     3,    40,    20,    30,
      19,     3,    41,    26,    37,    40,    43,    18,    22,    23,
      38,    44,    46,    24,    25,    42,     3,     3,    39,    19,
      41,    19,    47,    49,    17,    53,    45,    21,    51,    51,
       3,    10,    11,    53,    54,    55,    56,    59,    60,    27,
      53,    26,    40,    52,    18,    50,    21,     3,     5,     8,
       9,    21,    62,    63,    64,    65,    66,    62,    16,    19,
      12,    40,    18,    19,    20,    42,    19,    61,    62,    21,
      62,    57,     4,     7,     8,     9,     6,    64,    13,    56,
      62,    18,    42,    26,    40,    48,    20,    30,    61,    20,
      15,    63,    63,    63,    63,    65,    56,    42,    40,    18,
      19,    62,    20,    56,    18,    42,    58,    42,    14,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    37,    38,    39,    36,    40,    40,    41,    41,
      42,    42,    43,    43,    45,    44,    47,    48,    46,    49,
      50,    46,    51,    51,    52,    52,    52,    52,    53,    54,
      54,    55,    55,    56,    56,    56,    57,    58,    56,    56,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    65,    65,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     0,    13,     1,     3,     6,     0,
       1,     1,     3,     0,     0,     4,     0,     0,     8,     0,
       0,     6,     3,     0,     3,     4,     5,     6,     3,     1,
       0,     1,     3,     3,     1,     1,     0,     0,     8,     4,
       1,     1,     4,     1,     3,     1,     3,     1,     2,     3,
       3,     3,     1,     3,     1,     4,     1,     3,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
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
  case 2: /* $@1: %empty  */
#line 57 "parser.y"
                    {cria_globais(tab_simbolos, out_file); imprime_ts(log_file, tab_simbolos);}
#line 1222 "parser.tab.c"
    break;

  case 3: /* $@2: %empty  */
#line 58 "parser.y"
                                    {imprime_ts(log_file, tab_simbolos);
        fprintf(out_file, "\n\ndefine i32 @main(){\nentry:\n");
        }
#line 1230 "parser.tab.c"
    break;

  case 4: /* $@3: %empty  */
#line 61 "parser.y"
        {destroi_tabela(tab_simbolos);}
#line 1236 "parser.tab.c"
    break;

  case 5: /* PROGRAMA: PROGRAM ID ABRE_PARENTESES LISTA_DE_IDENTIFICADORES FECHA_PARENTESES PONTO_VIRGULA DECLARACOES $@1 DECLARACOES_DE_SUBPROGRAMAS $@2 $@3 ENUNCIADO_COMPOSTO PONTO_FINAL  */
#line 63 "parser.y"
                    {fprintf(out_file, "ret i32 0\n}");}
#line 1242 "parser.tab.c"
    break;

  case 6: /* LISTA_DE_IDENTIFICADORES: ID  */
#line 66 "parser.y"
                             {(yyval.lista_s) = insere_lista_simbolo(NULL, cria_simbolo((yyvsp[0].str), "variavel", escopo_atual));}
#line 1248 "parser.tab.c"
    break;

  case 7: /* LISTA_DE_IDENTIFICADORES: LISTA_DE_IDENTIFICADORES VIRGULA ID  */
#line 67 "parser.y"
                                                              {(yyval.lista_s) = insere_lista_simbolo((yyvsp[-2].lista_s), cria_simbolo((yyvsp[0].str), "variavel", escopo_atual));}
#line 1254 "parser.tab.c"
    break;

  case 8: /* DECLARACOES: DECLARACOES VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO PONTO_VIRGULA  */
#line 70 "parser.y"
                                                                                     {atualiza_tipo_simbolos((yyvsp[-3].lista_s), (yyvsp[-1].tipo)); tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-3].lista_s)); }
#line 1260 "parser.tab.c"
    break;

  case 10: /* TIPO: INTEIRO  */
#line 74 "parser.y"
              {(yyval.tipo) = "INTEIRO";}
#line 1266 "parser.tab.c"
    break;

  case 11: /* TIPO: REAL  */
#line 75 "parser.y"
            {(yyval.tipo) = "REAL";}
#line 1272 "parser.tab.c"
    break;

  case 12: /* DECLARACOES_DE_SUBPROGRAMAS: DECLARACOES_DE_SUBPROGRAMAS DECLARACAO_DE_SUBPROGRAMA PONTO_VIRGULA  */
#line 78 "parser.y"
                                                                                                 {imprime_ts(log_file, tab_simbolos); tab_simbolos = destroi_var_locais(tab_simbolos);}
#line 1278 "parser.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 82 "parser.y"
                                                                {cria_func(out_file, tab_simbolos);}
#line 1284 "parser.tab.c"
    break;

  case 15: /* DECLARACAO_DE_SUBPROGRAMA: CABECALHO_DE_SUBPROGRAMA DECLARACOES $@4 ENUNCIADO_COMPOSTO  */
#line 83 "parser.y"
    {
        if (dentro_de_funcao) {
            int temp_id = temp_count++;
            ret_funcao(temp_id, tab_simbolos);
            dentro_de_funcao = 0;
        }
        fprintf(out_file, "}"); 
        escopo_atual--;
    }
#line 1298 "parser.tab.c"
    break;

  case 16: /* $@5: %empty  */
#line 95 "parser.y"
                        {
                            (yyvsp[-1].lista_s) = insere_lista_simbolo(NULL, cria_simbolo((yyvsp[0].str), "funcao", escopo_atual)); 
                            escopo_atual++;
                            simbolo_t* retorno = cria_simbolo((yyvsp[0].str), "retorno", escopo_atual);
                            (yyvsp[-1].lista_s) = insere_lista_simbolo((yyvsp[-1].lista_s), retorno);

                            dentro_de_funcao = 1;
                        }
#line 1311 "parser.tab.c"
    break;

  case 17: /* $@6: %empty  */
#line 103 "parser.y"
                                                     {
                            atualiza_tipo_simbolos((yyvsp[-5].lista_s), (yyvsp[0].tipo)); 
                            tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-5].lista_s));
                        }
#line 1320 "parser.tab.c"
    break;

  case 19: /* $@7: %empty  */
#line 109 "parser.y"
                        {(yyvsp[-1].lista_s) = insere_lista_simbolo(NULL, cria_simbolo((yyvsp[0].str), "procedure", escopo_atual)); escopo_atual++;}
#line 1326 "parser.tab.c"
    break;

  case 20: /* $@8: %empty  */
#line 110 "parser.y"
                                   {tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-3].lista_s));}
#line 1332 "parser.tab.c"
    break;

  case 24: /* LISTA_DE_PARAMETROS: LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO  */
#line 118 "parser.y"
                    {atualiza_tipo_simbolos((yyvsp[-2].lista_s), (yyvsp[0].tipo)); atualiza_tipo_novo((yyvsp[-2].lista_s), "parametro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-2].lista_s));}
#line 1338 "parser.tab.c"
    break;

  case 25: /* LISTA_DE_PARAMETROS: VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO  */
#line 120 "parser.y"
                   {atualiza_tipo_simbolos((yyvsp[-2].lista_s), (yyvsp[0].tipo)); atualiza_tipo_novo((yyvsp[-2].lista_s), "ponteiro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-2].lista_s));}
#line 1344 "parser.tab.c"
    break;

  case 26: /* LISTA_DE_PARAMETROS: LISTA_DE_PARAMETROS PONTO_VIRGULA LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO  */
#line 122 "parser.y"
                   {atualiza_tipo_simbolos((yyvsp[-2].lista_s), (yyvsp[0].tipo)); atualiza_tipo_novo((yyvsp[-2].lista_s), "parametro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-2].lista_s));}
#line 1350 "parser.tab.c"
    break;

  case 27: /* LISTA_DE_PARAMETROS: LISTA_DE_PARAMETROS PONTO_VIRGULA VAR LISTA_DE_IDENTIFICADORES DOIS_PONTOS TIPO  */
#line 124 "parser.y"
                   {atualiza_tipo_simbolos((yyvsp[-2].lista_s), (yyvsp[0].tipo)); atualiza_tipo_novo((yyvsp[-2].lista_s), "ponteiro"); tab_simbolos = insere_simbolos_ts(tab_simbolos, (yyvsp[-2].lista_s));}
#line 1356 "parser.tab.c"
    break;

  case 33: /* ENUNCIADO: VARIAVEL OPERADOR_ATRIBUICAO EXPRESSAO  */
#line 138 "parser.y"
                                                  {
            if (!strcmp((yyvsp[0].exp)->tipo_llvm, "i32")) {
                fprintf(out_file, "store i32 %%%d, ptr %%%s\n", (yyvsp[0].exp)->id_temporario, (yyvsp[-2].str));
            } else if (!strcmp((yyvsp[0].exp)->tipo_llvm, "float")) {
                fprintf(out_file, "store float %%%d, ptr %%%s\n", (yyvsp[0].exp)->id_temporario, (yyvsp[-2].str));
            } else {
                fprintf(stderr, "Tipo LLVM não suportado na atribuição: %s\n", (yyvsp[0].exp)->tipo_llvm);
                exit(1);
            }
        }
#line 1371 "parser.tab.c"
    break;

  case 36: /* $@9: %empty  */
#line 150 "parser.y"
                        {
            if_count++;
            cria_if(out_file, (yyvsp[0].exp), if_count);
            (yyvsp[-1].num) = if_count;
        }
#line 1381 "parser.tab.c"
    break;

  case 37: /* $@10: %empty  */
#line 155 "parser.y"
                        {cria_fim_then(out_file, (yyvsp[-4].num));}
#line 1387 "parser.tab.c"
    break;

  case 38: /* ENUNCIADO: IF EXPRESSAO $@9 THEN ENUNCIADO $@10 ELSE ENUNCIADO  */
#line 155 "parser.y"
                                                                      {cria_fim_else(out_file, (yyvsp[-7].num));}
#line 1393 "parser.tab.c"
    break;

  case 43: /* LISTA_DE_EXPRESSOES: EXPRESSAO  */
#line 166 "parser.y"
                               {(yyval.exp) = cria_parametros_funcao(NULL, (yyvsp[0].exp));}
#line 1399 "parser.tab.c"
    break;

  case 44: /* LISTA_DE_EXPRESSOES: LISTA_DE_EXPRESSOES VIRGULA EXPRESSAO  */
#line 167 "parser.y"
                                                           {(yyval.exp) = cria_parametros_funcao((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1405 "parser.tab.c"
    break;

  case 45: /* EXPRESSAO: EXPRESSAO_SIMPLES  */
#line 170 "parser.y"
                             {(yyval.exp) = (yyvsp[0].exp);}
#line 1411 "parser.tab.c"
    break;

  case 46: /* EXPRESSAO: EXPRESSAO_SIMPLES OPERADOR_RELACIONAL EXPRESSAO_SIMPLES  */
#line 171 "parser.y"
                                                                   { (yyval.exp) = cria_expressao_binaria(out_file, (yyvsp[-2].exp), (yyvsp[0].exp), (yyvsp[-1].str), &temp_count); temp_count++;}
#line 1417 "parser.tab.c"
    break;

  case 47: /* EXPRESSAO_SIMPLES: TERMO  */
#line 174 "parser.y"
                         { (yyval.exp) = (yyvsp[0].exp); }
#line 1423 "parser.tab.c"
    break;

  case 48: /* EXPRESSAO_SIMPLES: SINAL TERMO  */
#line 175 "parser.y"
                                {
                    (yyval.exp) = (yyvsp[0].exp); // ignora o sinal por enquanto
                }
#line 1431 "parser.tab.c"
    break;

  case 49: /* EXPRESSAO_SIMPLES: EXPRESSAO_SIMPLES MAIS EXPRESSAO_SIMPLES  */
#line 178 "parser.y"
                                                            {
                     (yyval.exp) = cria_expressao_binaria(out_file, (yyvsp[-2].exp), (yyvsp[0].exp), "+", &temp_count);
                 }
#line 1439 "parser.tab.c"
    break;

  case 50: /* EXPRESSAO_SIMPLES: EXPRESSAO_SIMPLES MENOS EXPRESSAO_SIMPLES  */
#line 181 "parser.y"
                                                             {
                     (yyval.exp) = cria_expressao_binaria(out_file, (yyvsp[-2].exp), (yyvsp[0].exp), "-", &temp_count);
                 }
#line 1447 "parser.tab.c"
    break;

  case 53: /* TERMO: TERMO OPERADOR_MULTIPLICATIVO FATOR  */
#line 188 "parser.y"
                                           {
         (yyval.exp) = cria_expressao_binaria(out_file, (yyvsp[-2].exp), (yyvsp[0].exp), "*", &temp_count);
     }
#line 1455 "parser.tab.c"
    break;

  case 54: /* FATOR: ID  */
#line 193 "parser.y"
         {
        if (tab_simbolos == NULL) {
            fprintf(stderr, "Erro interno: tabela de símbolos não inicializada\n");
            exit(1);
        }
        simbolo_t* s = busca_simbolo(tab_simbolos, (yyvsp[0].str));
        if (s == NULL) {
            char erro[256];
            sprintf(erro, "variável '%s' não declarada", (yyvsp[0].str));
            yyerror(erro);
        }
        if(strcmp("var", s->tipo_simb) == 0 || strcmp("parametro", s->tipo_simb) == 0 || strcmp("ponteiro", s->tipo_simb) == 0){

            exp_t* e = malloc(sizeof(exp_t));
            e->nome = strdup((yyvsp[0].str));
            e->tipo = "var";
            e->tipo_llvm = converte_tipo(s->tipo);
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = load %s, ptr %%%s\n", e->id_temporario, e->tipo_llvm, (yyvsp[0].str));
            (yyval.exp) = e;
        }
    }
#line 1482 "parser.tab.c"
    break;

  case 55: /* FATOR: ID ABRE_PARENTESES LISTA_DE_EXPRESSOES FECHA_PARENTESES  */
#line 215 "parser.y"
                                                               {
        simbolo_t* s = busca_simbolo(tab_simbolos, (yyvsp[-3].str));
        if (s == NULL) {
            char erro[256];
            sprintf(erro, "variável '%s' não declarada", (yyvsp[-3].str));
            yyerror(erro);
        }
        exp_t* e = malloc(sizeof(exp_t));
        e->nome = strdup((yyvsp[-3].str));
        e->tipo = "funcao";
        e->tipo_llvm = converte_tipo(s->tipo);
        e->id_temporario = temp_count++;

        cria_chamada_funcao(out_file, (yyvsp[-1].exp), e, tab_simbolos, temp_count);
        // fprintf(out_file, "%%%d = load %s, ptr %%%s\n", e->id_temporario, e->tipo_llvm, $1);
        
        
        (yyval.exp) = e;
     }
#line 1506 "parser.tab.c"
    break;

  case 56: /* FATOR: NUM  */
#line 234 "parser.y"
           {
        exp_t* e = malloc(sizeof(exp_t));

        // Detecta se $1 contém ponto decimal → float
        if (strchr((yyvsp[0].str), '.')) {
            e->tipo = strdup("numero");
            e->tipo_llvm = strdup("float");
            e->nome = strdup((yyvsp[0].str));
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = fadd float 0.0, %s\n", e->id_temporario, (yyvsp[0].str));
        } else {
            e->tipo = strdup("numero");
            e->tipo_llvm = strdup("i32");
            e->nome = strdup((yyvsp[0].str));
            e->id_temporario = temp_count++;
            fprintf(out_file, "%%%d = add i32 0, %s\n", e->id_temporario, (yyvsp[0].str));
        }

        (yyval.exp) = e;
    }
#line 1531 "parser.tab.c"
    break;

  case 57: /* FATOR: ABRE_PARENTESES EXPRESSAO FECHA_PARENTESES  */
#line 254 "parser.y"
                                                  {
        (yyval.exp) = (yyvsp[-1].exp);
    }
#line 1539 "parser.tab.c"
    break;


#line 1543 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 262 "parser.y"



int main(int argc, char ** argv) {
    log_file = fopen ("compilador.log", "w");
    out_file = fopen ("output.ll", "w");
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yylineno=1;
        yyparse();
    } else if (argc == 1) {
        yyparse();
    }    
    fprintf(log_file, "Finalizando compilacao\n");
    fclose(out_file);
    fclose(log_file);
    return 0;
}


int yyerror(const char *s) {
  fprintf(stderr, "Erro na linha %d: %s\n", yylineno,s);
  exit(1);
  //return 0;
}
