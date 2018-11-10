/* A Bison parser, made by GNU Bison 3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         GLSL_STYPE
#define YYLTYPE         GLSL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         glsl_parse
#define yylex           glsl_lex
#define yyerror         glsl_error
#define yydebug         glsl_debug
#define yynerrs         glsl_nerrs


/* First part of user prologue.  */
#line 1 "glsl.y" /* yacc.c:338  */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "glsl_parser.h" //For context struct
#include "glsl.parser.h" //For GLSL_STYPE and GLSL_LTYPE
#include "glsl.lexer.h" //For glsl_lex()

static void glsl_error(GLSL_LTYPE *loc, glsl_parse_context *c, const char *s);

#define GLSL_STACK_BUFFER_SIZE (1024*1024)
#define GLSL_STACK_BUFFER_PAYLOAD_SIZE (GLSL_STACK_BUFFER_SIZE - sizeof(intptr_t))

uint8_t *glsl_parse_alloc(glsl_parse_context *context, size_t size, int align)
{
	uint8_t *ret;

	if (size + align > (context->cur_buffer_end - context->cur_buffer)) {
		uint8_t *next_buffer = (uint8_t *)malloc(GLSL_STACK_BUFFER_SIZE);
		if (context->cur_buffer) {
			uint8_t **pnext = (uint8_t **)context->cur_buffer_end;
			*pnext = next_buffer;
		}
		context->cur_buffer_start = next_buffer;
		context->cur_buffer = next_buffer;
		context->cur_buffer_end = next_buffer + GLSL_STACK_BUFFER_PAYLOAD_SIZE;
		if (!context->first_buffer) {
			context->first_buffer = context->cur_buffer;
		}
		*((uint8_t **)context->cur_buffer_end) = NULL;
	}

	ret = context->cur_buffer;

	uint8_t *trunc = (uint8_t *)((~((intptr_t)align - 1)) & ((intptr_t)ret));
	if (trunc != ret) {
		ret = trunc + align;
	}
	context->cur_buffer = ret + size;
	return ret;
}

void glsl_parse_dealloc(glsl_parse_context *context)
{
	uint8_t *buffer = context->first_buffer;
	while (buffer) {
		uint8_t *next = *((uint8_t **)(buffer + GLSL_STACK_BUFFER_PAYLOAD_SIZE));
		free(buffer);
		buffer = next;
	}
}

static char *glsl_parse_strdup(glsl_parse_context *context, const char *c)
{
	int len = strlen(c);
	char *ret = (char *)glsl_parse_alloc(context, len + 1, 1);
	strcpy(ret, c);
	return ret;
}

glsl_node *new_glsl_node(glsl_parse_context *context, int code, ...)
{
	glsl_node *temp;
	int i;
	int n = 0;
	va_list vl;
	va_start(vl, code);
	while (1) {
		temp = va_arg(vl, glsl_node *);
		if (temp)
			n++;
		else
			break;
	}
	va_end(vl);
	glsl_node *g = (glsl_node *)glsl_parse_alloc(context, offsetof(glsl_node, children[n]), 8);
	g->code = code;
	g->child_count = n;
	va_start(vl, code);
	for (i = 0; i < n; i++) {
		temp = va_arg(vl, glsl_node *);
		g->children[i] = temp;
	}
	va_end(vl);
	return g;
}

static glsl_node *new_glsl_identifier(glsl_parse_context *context, const char *str)
{
	glsl_node *n = new_glsl_node(context, IDENTIFIER, NULL);
	if (!str)
		n->data.str = NULL;
	else
		n->data.str = glsl_parse_strdup(context, str);
	return n;
}

static glsl_node *new_glsl_string(glsl_parse_context *context, int code, const char *str)
{
	glsl_node *n = new_glsl_node(context, code, NULL);
	n->data.str = glsl_parse_strdup(context, str);
	return n;
}

#define scanner context->scanner //To allow the scanner to find it's context


#line 191 "glsl.parser.cpp" /* yacc.c:338  */
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

/* In a future release of Bison, this section will be replaced
   by #include "glsl.parser.h".  */
#ifndef YY_GLSL_GLSL_PARSER_H_INCLUDED
# define YY_GLSL_GLSL_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef GLSL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define GLSL_DEBUG 1
#  else
#   define GLSL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define GLSL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined GLSL_DEBUG */
#if GLSL_DEBUG
extern int glsl_debug;
#endif

/* Token type.  */
#ifndef GLSL_TOKENTYPE
# define GLSL_TOKENTYPE
  enum glsl_tokentype
  {
    CONST = 258,
    BOOL = 259,
    FLOAT = 260,
    DOUBLE = 261,
    INT = 262,
    UINT = 263,
    BREAK = 264,
    CONTINUE = 265,
    DO = 266,
    ELSE = 267,
    FOR = 268,
    IF = 269,
    DISCARD = 270,
    RETURN = 271,
    RETURN_VALUE = 272,
    SWITCH = 273,
    CASE = 274,
    DEFAULT = 275,
    SUBROUTINE = 276,
    BVEC2 = 277,
    BVEC3 = 278,
    BVEC4 = 279,
    IVEC2 = 280,
    IVEC3 = 281,
    IVEC4 = 282,
    UVEC2 = 283,
    UVEC3 = 284,
    UVEC4 = 285,
    VEC2 = 286,
    VEC3 = 287,
    VEC4 = 288,
    MAT2 = 289,
    MAT3 = 290,
    MAT4 = 291,
    CENTROID = 292,
    IN = 293,
    OUT = 294,
    INOUT = 295,
    UNIFORM = 296,
    PATCH = 297,
    SAMPLE = 298,
    BUFFER = 299,
    SHARED = 300,
    COHERENT = 301,
    VOLATILE = 302,
    RESTRICT = 303,
    READONLY = 304,
    WRITEONLY = 305,
    DVEC2 = 306,
    DVEC3 = 307,
    DVEC4 = 308,
    DMAT2 = 309,
    DMAT3 = 310,
    DMAT4 = 311,
    NOPERSPECTIVE = 312,
    FLAT = 313,
    SMOOTH = 314,
    LAYOUT = 315,
    MAT2X2 = 316,
    MAT2X3 = 317,
    MAT2X4 = 318,
    MAT3X2 = 319,
    MAT3X3 = 320,
    MAT3X4 = 321,
    MAT4X2 = 322,
    MAT4X3 = 323,
    MAT4X4 = 324,
    DMAT2X2 = 325,
    DMAT2X3 = 326,
    DMAT2X4 = 327,
    DMAT3X2 = 328,
    DMAT3X3 = 329,
    DMAT3X4 = 330,
    DMAT4X2 = 331,
    DMAT4X3 = 332,
    DMAT4X4 = 333,
    ATOMIC_UINT = 334,
    SAMPLER1D = 335,
    SAMPLER2D = 336,
    SAMPLER3D = 337,
    SAMPLERCUBE = 338,
    SAMPLER1DSHADOW = 339,
    SAMPLER2DSHADOW = 340,
    SAMPLERCUBESHADOW = 341,
    SAMPLER1DARRAY = 342,
    SAMPLER2DARRAY = 343,
    SAMPLER1DARRAYSHADOW = 344,
    SAMPLER2DARRAYSHADOW = 345,
    ISAMPLER1D = 346,
    ISAMPLER2D = 347,
    ISAMPLER3D = 348,
    ISAMPLERCUBE = 349,
    ISAMPLER1DARRAY = 350,
    ISAMPLER2DARRAY = 351,
    USAMPLER1D = 352,
    USAMPLER2D = 353,
    USAMPLER3D = 354,
    USAMPLERCUBE = 355,
    USAMPLER1DARRAY = 356,
    USAMPLER2DARRAY = 357,
    SAMPLER2DRECT = 358,
    SAMPLER2DRECTSHADOW = 359,
    ISAMPLER2DRECT = 360,
    USAMPLER2DRECT = 361,
    SAMPLERBUFFER = 362,
    ISAMPLERBUFFER = 363,
    USAMPLERBUFFER = 364,
    SAMPLERCUBEARRAY = 365,
    SAMPLERCUBEARRAYSHADOW = 366,
    ISAMPLERCUBEARRAY = 367,
    USAMPLERCUBEARRAY = 368,
    SAMPLER2DMS = 369,
    ISAMPLER2DMS = 370,
    USAMPLER2DMS = 371,
    SAMPLER2DMSARRAY = 372,
    ISAMPLER2DMSARRAY = 373,
    USAMPLER2DMSARRAY = 374,
    IMAGE1D = 375,
    IIMAGE1D = 376,
    UIMAGE1D = 377,
    IMAGE2D = 378,
    IIMAGE2D = 379,
    UIMAGE2D = 380,
    IMAGE3D = 381,
    IIMAGE3D = 382,
    UIMAGE3D = 383,
    IMAGE2DRECT = 384,
    IIMAGE2DRECT = 385,
    UIMAGE2DRECT = 386,
    IMAGECUBE = 387,
    IIMAGECUBE = 388,
    UIMAGECUBE = 389,
    IMAGEBUFFER = 390,
    IIMAGEBUFFER = 391,
    UIMAGEBUFFER = 392,
    IMAGE1DARRAY = 393,
    IIMAGE1DARRAY = 394,
    UIMAGE1DARRAY = 395,
    IMAGE2DARRAY = 396,
    IIMAGE2DARRAY = 397,
    UIMAGE2DARRAY = 398,
    IMAGECUBEARRAY = 399,
    IIMAGECUBEARRAY = 400,
    UIMAGECUBEARRAY = 401,
    IMAGE2DMS = 402,
    IIMAGE2DMS = 403,
    UIMAGE2DMS = 404,
    IMAGE2DMSARRAY = 405,
    IIMAGE2DMSARRAY = 406,
    UIMAGE2DMSARRAY = 407,
    STRUCT = 408,
    VOID = 409,
    WHILE = 410,
    IDENTIFIER = 411,
    FLOATCONSTANT = 412,
    DOUBLECONSTANT = 413,
    INTCONSTANT = 414,
    UINTCONSTANT = 415,
    TRUE_VALUE = 416,
    FALSE_VALUE = 417,
    LEFT_OP = 418,
    RIGHT_OP = 419,
    INC_OP = 420,
    DEC_OP = 421,
    LE_OP = 422,
    GE_OP = 423,
    EQ_OP = 424,
    NE_OP = 425,
    AND_OP = 426,
    OR_OP = 427,
    XOR_OP = 428,
    MUL_ASSIGN = 429,
    DIV_ASSIGN = 430,
    ADD_ASSIGN = 431,
    MOD_ASSIGN = 432,
    LEFT_ASSIGN = 433,
    RIGHT_ASSIGN = 434,
    AND_ASSIGN = 435,
    XOR_ASSIGN = 436,
    OR_ASSIGN = 437,
    SUB_ASSIGN = 438,
    LEFT_PAREN = 439,
    RIGHT_PAREN = 440,
    LEFT_BRACKET = 441,
    RIGHT_BRACKET = 442,
    LEFT_BRACE = 443,
    RIGHT_BRACE = 444,
    DOT = 445,
    COMMA = 446,
    COLON = 447,
    EQUAL = 448,
    SEMICOLON = 449,
    BANG = 450,
    DASH = 451,
    TILDE = 452,
    PLUS = 453,
    STAR = 454,
    SLASH = 455,
    PERCENT = 456,
    LEFT_ANGLE = 457,
    RIGHT_ANGLE = 458,
    VERTICAL_BAR = 459,
    CARET = 460,
    AMPERSAND = 461,
    QUESTION = 462,
    INVARIANT = 463,
    PRECISE = 464,
    HIGHP = 465,
    MEDIUMP = 466,
    LOWP = 467,
    PRECISION = 468,
    AT = 469,
    UNARY_PLUS = 470,
    UNARY_DASH = 471,
    PRE_INC_OP = 472,
    PRE_DEC_OP = 473,
    POST_DEC_OP = 474,
    POST_INC_OP = 475,
    ARRAY_REF_OP = 476,
    FUNCTION_CALL = 477,
    TYPE_NAME_LIST = 478,
    TYPE_SPECIFIER = 479,
    POSTFIX_EXPRESSION = 480,
    LAYOUT_QUALIFIER = 481,
    LAYOUT_QUALIFIER_ID = 482,
    LAYOUT_QUALIFIER_ID_LIST = 483,
    TYPE_QUALIFIER_LIST = 484,
    STRUCT_DECLARATION = 485,
    STRUCT_DECLARATOR = 486,
    STRUCT_SPECIFIER = 487,
    FUNCTION_DEFINITION = 488,
    DECLARATION = 489,
    STATEMENT_LIST = 490,
    TRANSLATION_UNIT = 491,
    PRECISION_DECLARATION = 492,
    BLOCK_DECLARATION = 493,
    TYPE_QUALIFIER_DECLARATION = 494,
    IDENTIFIER_LIST = 495,
    INIT_DECLARATOR_LIST = 496,
    FULLY_SPECIFIED_TYPE = 497,
    SINGLE_DECLARATION = 498,
    SINGLE_INIT_DECLARATION = 499,
    INITIALIZER_LIST = 500,
    EXPRESSION_STATEMENT = 501,
    SELECTION_STATEMENT = 502,
    SELECTION_STATEMENT_ELSE = 503,
    SWITCH_STATEMENT = 504,
    FOR_REST_STATEMENT = 505,
    WHILE_STATEMENT = 506,
    DO_STATEMENT = 507,
    FOR_STATEMENT = 508,
    CASE_LABEL = 509,
    CONDITION_OPT = 510,
    ASSIGNMENT_CONDITION = 511,
    EXPRESSION_CONDITION = 512,
    FUNCTION_HEADER = 513,
    FUNCTION_DECLARATION = 514,
    FUNCTION_PARAMETER_LIST = 515,
    PARAMETER_DECLARATION = 516,
    PARAMETER_DECLARATOR = 517,
    UNINITIALIZED_DECLARATION = 518,
    ARRAY_SPECIFIER = 519,
    ARRAY_SPECIFIER_LIST = 520,
    STRUCT_DECLARATOR_LIST = 521,
    FUNCTION_CALL_PARAMETER_LIST = 522,
    STRUCT_DECLARATION_LIST = 523,
    SUBROUTINE_TYPE = 524,
    PAREN_EXPRESSION = 525,
    INIT_DECLARATOR = 526,
    INITIALIZER = 527,
    TERNARY_EXPRESSION = 528,
    FIELD_IDENTIFIER = 529,
    NUM_GLSL_TOKEN = 530
  };
#endif

/* Value type.  */
#if ! defined GLSL_STYPE && ! defined GLSL_STYPE_IS_DECLARED

union GLSL_STYPE
{

  /* IDENTIFIER  */
  char * IDENTIFIER;
  /* DOUBLECONSTANT  */
  double DOUBLECONSTANT;
  /* FLOATCONSTANT  */
  float FLOATCONSTANT;
  /* translation_unit  */
  glsl_node * translation_unit;
  /* block_identifier  */
  glsl_node * block_identifier;
  /* decl_identifier  */
  glsl_node * decl_identifier;
  /* struct_name  */
  glsl_node * struct_name;
  /* type_name  */
  glsl_node * type_name;
  /* param_name  */
  glsl_node * param_name;
  /* function_name  */
  glsl_node * function_name;
  /* field_identifier  */
  glsl_node * field_identifier;
  /* variable_identifier  */
  glsl_node * variable_identifier;
  /* layout_identifier  */
  glsl_node * layout_identifier;
  /* type_specifier_identifier  */
  glsl_node * type_specifier_identifier;
  /* external_declaration  */
  glsl_node * external_declaration;
  /* function_definition  */
  glsl_node * function_definition;
  /* compound_statement_no_new_scope  */
  glsl_node * compound_statement_no_new_scope;
  /* statement  */
  glsl_node * statement;
  /* statement_list  */
  glsl_node * statement_list;
  /* compound_statement  */
  glsl_node * compound_statement;
  /* simple_statement  */
  glsl_node * simple_statement;
  /* declaration  */
  glsl_node * declaration;
  /* identifier_list  */
  glsl_node * identifier_list;
  /* init_declarator_list  */
  glsl_node * init_declarator_list;
  /* single_declaration  */
  glsl_node * single_declaration;
  /* initializer  */
  glsl_node * initializer;
  /* initializer_list  */
  glsl_node * initializer_list;
  /* expression_statement  */
  glsl_node * expression_statement;
  /* selection_statement  */
  glsl_node * selection_statement;
  /* switch_statement  */
  glsl_node * switch_statement;
  /* switch_statement_list  */
  glsl_node * switch_statement_list;
  /* case_label  */
  glsl_node * case_label;
  /* iteration_statement  */
  glsl_node * iteration_statement;
  /* statement_no_new_scope  */
  glsl_node * statement_no_new_scope;
  /* for_init_statement  */
  glsl_node * for_init_statement;
  /* conditionopt  */
  glsl_node * conditionopt;
  /* condition  */
  glsl_node * condition;
  /* for_rest_statement  */
  glsl_node * for_rest_statement;
  /* jump_statement  */
  glsl_node * jump_statement;
  /* function_prototype  */
  glsl_node * function_prototype;
  /* function_declarator  */
  glsl_node * function_declarator;
  /* function_parameter_list  */
  glsl_node * function_parameter_list;
  /* parameter_declaration  */
  glsl_node * parameter_declaration;
  /* parameter_declarator  */
  glsl_node * parameter_declarator;
  /* function_header  */
  glsl_node * function_header;
  /* fully_specified_type  */
  glsl_node * fully_specified_type;
  /* parameter_type_specifier  */
  glsl_node * parameter_type_specifier;
  /* type_specifier  */
  glsl_node * type_specifier;
  /* array_specifier_list  */
  glsl_node * array_specifier_list;
  /* array_specifier  */
  glsl_node * array_specifier;
  /* type_specifier_nonarray  */
  glsl_node * type_specifier_nonarray;
  /* struct_specifier  */
  glsl_node * struct_specifier;
  /* struct_declaration_list  */
  glsl_node * struct_declaration_list;
  /* struct_declaration  */
  glsl_node * struct_declaration;
  /* struct_declarator_list  */
  glsl_node * struct_declarator_list;
  /* struct_declarator  */
  glsl_node * struct_declarator;
  /* type_qualifier  */
  glsl_node * type_qualifier;
  /* single_type_qualifier  */
  glsl_node * single_type_qualifier;
  /* layout_qualifier  */
  glsl_node * layout_qualifier;
  /* layout_qualifier_id_list  */
  glsl_node * layout_qualifier_id_list;
  /* layout_qualifier_id  */
  glsl_node * layout_qualifier_id;
  /* precision_qualifier  */
  glsl_node * precision_qualifier;
  /* interpolation_qualifier  */
  glsl_node * interpolation_qualifier;
  /* invariant_qualifier  */
  glsl_node * invariant_qualifier;
  /* precise_qualifier  */
  glsl_node * precise_qualifier;
  /* storage_qualifier  */
  glsl_node * storage_qualifier;
  /* type_name_list  */
  glsl_node * type_name_list;
  /* expression  */
  glsl_node * expression;
  /* assignment_expression  */
  glsl_node * assignment_expression;
  /* constant_expression  */
  glsl_node * constant_expression;
  /* conditional_expression  */
  glsl_node * conditional_expression;
  /* logical_or_expression  */
  glsl_node * logical_or_expression;
  /* logical_xor_expression  */
  glsl_node * logical_xor_expression;
  /* logical_and_expression  */
  glsl_node * logical_and_expression;
  /* inclusive_or_expression  */
  glsl_node * inclusive_or_expression;
  /* exclusive_or_expression  */
  glsl_node * exclusive_or_expression;
  /* and_expression  */
  glsl_node * and_expression;
  /* equality_expression  */
  glsl_node * equality_expression;
  /* relational_expression  */
  glsl_node * relational_expression;
  /* shift_expression  */
  glsl_node * shift_expression;
  /* additive_expression  */
  glsl_node * additive_expression;
  /* multiplicative_expression  */
  glsl_node * multiplicative_expression;
  /* unary_expression  */
  glsl_node * unary_expression;
  /* postfix_expression  */
  glsl_node * postfix_expression;
  /* integer_expression  */
  glsl_node * integer_expression;
  /* function_call  */
  glsl_node * function_call;
  /* function_call_or_method  */
  glsl_node * function_call_or_method;
  /* function_call_generic  */
  glsl_node * function_call_generic;
  /* function_call_parameter_list  */
  glsl_node * function_call_parameter_list;
  /* function_identifier  */
  glsl_node * function_identifier;
  /* primary_expression  */
  glsl_node * primary_expression;
  /* INTCONSTANT  */
  int INTCONSTANT;
  /* assignment_operator  */
  int assignment_operator;
  /* unary_operator  */
  int unary_operator;
  /* UINTCONSTANT  */
  unsigned int UINTCONSTANT;
#line 709 "glsl.parser.cpp" /* yacc.c:353  */
};

typedef union GLSL_STYPE GLSL_STYPE;
# define GLSL_STYPE_IS_TRIVIAL 1
# define GLSL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined GLSL_LTYPE && ! defined GLSL_LTYPE_IS_DECLARED
typedef struct GLSL_LTYPE GLSL_LTYPE;
struct GLSL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define GLSL_LTYPE_IS_DECLARED 1
# define GLSL_LTYPE_IS_TRIVIAL 1
#endif



int glsl_parse (glsl_parse_context * context);

#endif /* !YY_GLSL_GLSL_PARSER_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
         || (defined GLSL_LTYPE_IS_TRIVIAL && GLSL_LTYPE_IS_TRIVIAL \
             && defined GLSL_STYPE_IS_TRIVIAL && GLSL_STYPE_IS_TRIVIAL)))

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
#define YYFINAL  177
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  276
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  361
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  496

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   530

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275
};

#if GLSL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   505,   505,   506,   509,   512,   516,   519,   522,   525,
     528,   531,   534,   537,   540,   543,   546,   547,   550,   555,
     562,   563,   566,   567,   570,   571,   574,   575,   578,   579,
     580,   581,   582,   583,   584,   587,   588,   589,   596,   606,
     616,   626,   633,   641,   649,   659,   660,   664,   665,   673,
     681,   690,   701,   708,   715,   718,   721,   730,   731,   732,
     735,   737,   741,   742,   745,   748,   752,   756,   757,   760,
     761,   764,   767,   770,   774,   775,   778,   779,   782,   783,
     786,   789,   793,   796,   800,   803,   806,   809,   812,   816,
     819,   825,   832,   835,   839,   842,   848,   851,   858,   861,
     865,   869,   875,   879,   883,   889,   893,   896,   900,   903,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   950,   951,   952,   953,   954,   955,   956,
     957,   958,   959,   960,   961,   962,   963,   964,   965,   966,
     967,   968,   969,   970,   971,   972,   973,   974,   975,   976,
     977,   978,   979,   980,   981,   982,   983,   984,   985,   986,
     987,   988,   989,   990,   991,   992,   993,   994,   995,   996,
     997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,
    1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1030,  1033,  1040,  1042,  1046,  1053,  1057,  1060,  1064,
    1067,  1071,  1073,  1077,  1078,  1079,  1080,  1081,  1082,  1085,
    1088,  1090,  1094,  1097,  1100,  1104,  1105,  1106,  1109,  1110,
    1111,  1114,  1117,  1120,  1121,  1122,  1123,  1124,  1125,  1126,
    1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,
    1142,  1143,  1147,  1148,  1152,  1153,  1157,  1158,  1159,  1160,
    1161,  1162,  1163,  1164,  1165,  1166,  1167,  1170,  1173,  1174,
    1178,  1179,  1183,  1184,  1188,  1189,  1193,  1194,  1198,  1199,
    1203,  1204,  1208,  1210,  1213,  1217,  1219,  1222,  1225,  1228,
    1232,  1234,  1237,  1241,  1243,  1246,  1250,  1252,  1255,  1258,
    1262,  1264,  1267,  1270,  1274,  1275,  1276,  1277,  1280,  1282,
    1285,  1287,  1290,  1293,  1297,  1300,  1303,  1306,  1309,  1315,
    1322,  1325,  1329,  1331,  1335,  1337,  1340,  1343,  1346,  1349,
    1352,  1355
};
#endif

#if GLSL_DEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "BOOL", "FLOAT", "DOUBLE",
  "INT", "UINT", "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF", "DISCARD",
  "RETURN", "RETURN_VALUE", "SWITCH", "CASE", "DEFAULT", "SUBROUTINE",
  "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "UVEC2", "UVEC3",
  "UVEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID",
  "IN", "OUT", "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED",
  "COHERENT", "VOLATILE", "RESTRICT", "READONLY", "WRITEONLY", "DVEC2",
  "DVEC3", "DVEC4", "DMAT2", "DMAT3", "DMAT4", "NOPERSPECTIVE", "FLAT",
  "SMOOTH", "LAYOUT", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3",
  "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3", "DMAT2X4",
  "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3", "DMAT4X4",
  "ATOMIC_UINT", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D",
  "ISAMPLERCUBE", "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW",
  "ISAMPLER2DRECT", "USAMPLER2DRECT", "SAMPLERBUFFER", "ISAMPLERBUFFER",
  "USAMPLERBUFFER", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLERCUBEARRAY", "USAMPLERCUBEARRAY", "SAMPLER2DMS", "ISAMPLER2DMS",
  "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "IMAGE1D", "IIMAGE1D", "UIMAGE1D", "IMAGE2D",
  "IIMAGE2D", "UIMAGE2D", "IMAGE3D", "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT",
  "IIMAGE2DRECT", "UIMAGE2DRECT", "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE",
  "IMAGEBUFFER", "IIMAGEBUFFER", "UIMAGEBUFFER", "IMAGE1DARRAY",
  "IIMAGE1DARRAY", "UIMAGE1DARRAY", "IMAGE2DARRAY", "IIMAGE2DARRAY",
  "UIMAGE2DARRAY", "IMAGECUBEARRAY", "IIMAGECUBEARRAY", "UIMAGECUBEARRAY",
  "IMAGE2DMS", "IIMAGE2DMS", "UIMAGE2DMS", "IMAGE2DMSARRAY",
  "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY", "STRUCT", "VOID", "WHILE",
  "IDENTIFIER", "FLOATCONSTANT", "DOUBLECONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "TRUE_VALUE", "FALSE_VALUE", "LEFT_OP", "RIGHT_OP",
  "INC_OP", "DEC_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "XOR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "ADD_ASSIGN",
  "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "SUB_ASSIGN", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_BRACE", "RIGHT_BRACE", "DOT", "COMMA", "COLON",
  "EQUAL", "SEMICOLON", "BANG", "DASH", "TILDE", "PLUS", "STAR", "SLASH",
  "PERCENT", "LEFT_ANGLE", "RIGHT_ANGLE", "VERTICAL_BAR", "CARET",
  "AMPERSAND", "QUESTION", "INVARIANT", "PRECISE", "HIGHP", "MEDIUMP",
  "LOWP", "PRECISION", "AT", "UNARY_PLUS", "UNARY_DASH", "PRE_INC_OP",
  "PRE_DEC_OP", "POST_DEC_OP", "POST_INC_OP", "ARRAY_REF_OP",
  "FUNCTION_CALL", "TYPE_NAME_LIST", "TYPE_SPECIFIER",
  "POSTFIX_EXPRESSION", "LAYOUT_QUALIFIER", "LAYOUT_QUALIFIER_ID",
  "LAYOUT_QUALIFIER_ID_LIST", "TYPE_QUALIFIER_LIST", "STRUCT_DECLARATION",
  "STRUCT_DECLARATOR", "STRUCT_SPECIFIER", "FUNCTION_DEFINITION",
  "DECLARATION", "STATEMENT_LIST", "TRANSLATION_UNIT",
  "PRECISION_DECLARATION", "BLOCK_DECLARATION",
  "TYPE_QUALIFIER_DECLARATION", "IDENTIFIER_LIST", "INIT_DECLARATOR_LIST",
  "FULLY_SPECIFIED_TYPE", "SINGLE_DECLARATION", "SINGLE_INIT_DECLARATION",
  "INITIALIZER_LIST", "EXPRESSION_STATEMENT", "SELECTION_STATEMENT",
  "SELECTION_STATEMENT_ELSE", "SWITCH_STATEMENT", "FOR_REST_STATEMENT",
  "WHILE_STATEMENT", "DO_STATEMENT", "FOR_STATEMENT", "CASE_LABEL",
  "CONDITION_OPT", "ASSIGNMENT_CONDITION", "EXPRESSION_CONDITION",
  "FUNCTION_HEADER", "FUNCTION_DECLARATION", "FUNCTION_PARAMETER_LIST",
  "PARAMETER_DECLARATION", "PARAMETER_DECLARATOR",
  "UNINITIALIZED_DECLARATION", "ARRAY_SPECIFIER", "ARRAY_SPECIFIER_LIST",
  "STRUCT_DECLARATOR_LIST", "FUNCTION_CALL_PARAMETER_LIST",
  "STRUCT_DECLARATION_LIST", "SUBROUTINE_TYPE", "PAREN_EXPRESSION",
  "INIT_DECLARATOR", "INITIALIZER", "TERNARY_EXPRESSION",
  "FIELD_IDENTIFIER", "NUM_GLSL_TOKEN", "$accept", "root",
  "translation_unit", "block_identifier", "decl_identifier", "struct_name",
  "type_name", "param_name", "function_name", "field_identifier",
  "variable_identifier", "layout_identifier", "type_specifier_identifier",
  "external_declaration", "function_definition",
  "compound_statement_no_new_scope", "statement", "statement_list",
  "compound_statement", "simple_statement", "declaration",
  "identifier_list", "init_declarator_list", "single_declaration",
  "initializer", "initializer_list", "expression_statement",
  "selection_statement", "switch_statement", "switch_statement_list",
  "case_label", "iteration_statement", "statement_no_new_scope",
  "for_init_statement", "conditionopt", "condition", "for_rest_statement",
  "jump_statement", "function_prototype", "function_declarator",
  "function_parameter_list", "parameter_declaration",
  "parameter_declarator", "function_header", "fully_specified_type",
  "parameter_type_specifier", "type_specifier", "array_specifier_list",
  "array_specifier", "type_specifier_nonarray", "struct_specifier",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "type_qualifier",
  "single_type_qualifier", "layout_qualifier", "layout_qualifier_id_list",
  "layout_qualifier_id", "precision_qualifier", "interpolation_qualifier",
  "invariant_qualifier", "precise_qualifier", "storage_qualifier",
  "type_name_list", "expression", "assignment_expression",
  "assignment_operator", "constant_expression", "conditional_expression",
  "logical_or_expression", "logical_xor_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "unary_operator",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_parameter_list", "function_identifier",
  "primary_expression", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530
};
# endif

#define YYPACT_NINF -412

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-412)))

#define YYTABLE_NINF -354

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1937,  -412,  -412,  -412,  -412,  -412,  -412,  -131,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -119,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -122,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,   -64,    81,  1937,
    -412,  -412,  -412,  -412,  -164,  -412,  -163,   -97,  3094,   -44,
    -412,   -93,  -412,  2326,  -412,  3094,  -412,  -412,  -412,  -412,
    -412,   -30,   -31,  -412,  3094,   -58,  4354,  -412,  -412,   -22,
    -412,   490,  -412,  -412,  -412,   -29,  -412,  -412,  -412,    10,
    3094,  -412,   -20,  -116,   -12,  3442,   -93,  -412,  -132,  -412,
     -13,   -87,  -412,  -412,   -78,   -22,  3094,  -412,  -412,  -102,
    -412,  -412,   -14,  -101,  -412,    33,  2518,  -412,  3094,  3094,
      -3,  -412,  -111,    13,    16,  1334,     9,    11,    19,  3626,
      18,  3992,     5,    24,    58,  -412,  -412,  -412,  -412,  -412,
    -412,  3992,  3992,  3992,   701,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,   912,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,    21,    36,   -73,  -412,  -412,  -150,    48,
      51,    20,    22,    17,    -1,  -139,    14,   -39,   -45,  -138,
    3992,  -117,  -412,  -412,  -412,    42,  -412,  3094,  -412,   -93,
    -412,  -412,  3807,  -108,  -412,  -412,  -412,    44,  -412,  -412,
    -412,  3094,   -22,  -412,   -63,  -412,  -412,   -30,  3992,  -412,
     -31,  -412,   -93,   -51,  -412,  -412,  -412,    33,  2710,  -412,
    3807,  -106,  -412,  -412,    74,  1741,  3992,  -412,  -412,   -50,
    3992,    -9,  -412,  2130,  -412,  -412,   -99,  -412,  1123,  -412,
    -412,  3992,  -412,  3992,  3992,  3992,  3992,  3992,  3992,  3992,
    3992,  3992,  3992,  3992,  3992,  3992,  3992,  3992,  3992,  3992,
    3992,  3992,  3992,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  3992,  -412,  -412,  -412,  3992,    33,
    4173,  -412,   -93,  3807,  -412,  -412,  3807,  -412,  2902,  -412,
     -22,  -412,  -412,  -412,  -412,   -93,    33,  -412,   -49,  -412,
    -412,  3807,    49,  -412,  -412,  2130,   -94,  -412,   -90,  -412,
      47,    78,    45,  -412,  -412,  -412,    48,    -5,    51,    20,
      22,    17,    -1,  -139,  -139,    14,    14,    14,    14,   -39,
     -39,   -45,   -45,  -412,  -412,  -412,  -412,    45,    50,  -412,
      57,  3992,  -412,   -89,  -412,   -83,  -412,  -135,  -412,  -412,
    -412,  -412,  3992,    41,  -412,    61,  1334,    55,  1545,  -412,
      59,  3992,  -412,  -412,  -412,  3992,  -412,  3256,  -412,  -136,
     -82,  3992,  1545,   236,  1334,  -412,  -412,  -412,  3807,  -412,
    -412,  -412,  -412,  -412,  -134,    60,    45,  -412,  1334,  1334,
      62,  -412,  -412,  -412,  -412,  -412
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,   263,   115,   111,   112,   113,   114,   278,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   116,   117,   118,
     131,   132,   133,   267,   265,   266,   264,   270,   268,   269,
     271,   272,   273,   274,   275,   276,   277,   119,   120,   121,
     143,   144,   145,   260,   259,   258,     0,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   169,   170,   171,
     172,   173,   174,   176,   177,   178,   179,   180,   181,   183,
     184,   185,   186,   187,   188,   189,   167,   168,   175,   182,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,     0,
     110,    15,   261,   262,   255,   256,   257,     0,     0,     3,
     230,     4,    16,    17,     0,    47,    19,     0,    90,    52,
     101,   104,   229,     0,   241,   244,   245,   246,   247,   248,
     243,     0,     0,     8,     0,     0,     0,     1,     5,     0,
      36,     0,    35,    18,    89,    91,    92,    95,    97,   103,
       0,   244,     7,    53,     0,     0,   105,   106,     9,    41,
       0,     0,   102,   242,     0,    52,     0,     9,   280,     0,
     254,    14,   252,     0,   250,     0,     0,   233,     0,     0,
       0,     7,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,   357,   360,   355,   356,   358,
     359,     0,     0,     0,     0,    20,    62,   336,   335,   337,
     334,   354,    24,     0,    22,    23,    28,    29,    30,    31,
      32,    33,    34,     0,   101,     0,   282,   284,   298,   300,
     302,   304,   306,   308,   310,   312,   315,   320,   323,   326,
       0,   330,   340,   345,   346,     0,   338,     0,    10,    98,
      94,    96,     0,    54,   100,   108,   352,     0,   297,   326,
     107,     0,     0,    42,     0,    44,   279,     0,     0,   249,
       0,    12,   239,     0,   237,   232,   234,     0,     0,    37,
       0,    49,    85,    84,     0,     0,     0,    88,    86,     0,
       0,     0,    70,     0,   331,   332,     0,    26,     0,    21,
      25,     0,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   287,   288,   290,   289,   292,   293,   294,
     295,   296,   291,   286,     0,   333,   342,   343,     0,     0,
       0,    93,    99,     0,    56,    57,     0,   109,     0,    45,
       0,    43,   281,   253,   251,   240,     0,   235,     0,   231,
      51,     0,     0,    77,    76,    79,     0,    87,     0,    69,
       0,     0,    80,   361,    27,   283,   301,     0,   303,   305,
     307,   309,   311,   313,   314,   318,   319,   316,   317,   321,
     322,   325,   324,   327,   328,   329,   285,   344,     0,   341,
     110,   348,   350,     0,    60,     0,    55,     0,    46,   238,
     236,    50,     0,     0,    78,     0,     0,     0,     0,    13,
       0,     0,   339,   349,   347,     0,    58,     0,    38,     0,
       0,    82,     0,    64,    67,    74,    75,    71,     0,   299,
     351,    59,    61,    39,     0,     0,    83,    73,     0,    68,
       0,    81,    40,    72,    65,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -412,  -412,  -412,  -412,  -173,  -412,  -156,  -412,  -412,  -124,
    -153,  -412,  -412,   110,  -412,   105,  -218,  -235,  -412,  -411,
       1,  -412,    97,  -412,  -307,  -412,   -62,  -412,  -412,  -412,
    -412,  -412,  -207,  -412,  -412,  -141,  -412,  -412,    12,  -412,
    -412,   -21,    77,  -412,  -160,    79,     0,  -189,  -194,  -412,
    -412,  -203,  -208,   -42,  -128,  -148,  -144,     3,  -412,   -38,
     126,  -412,  -412,  -412,  -412,  -412,  -211,  -269,  -412,   -32,
    -184,  -412,   -66,   -67,   -65,   -68,   -59,   -57,  -151,  -217,
    -152,  -147,     8,  -412,  -412,  -412,  -412,  -412,  -412,  -412,
    -412,  -412
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   148,   149,   200,   193,   175,   201,   289,   194,   312,
     251,   212,   150,   151,   152,   475,   252,   253,   254,   255,
     256,   304,   154,   155,   384,   445,   257,   258,   259,   490,
     260,   261,   477,   405,   453,   410,   455,   262,   263,   157,
     185,   186,   187,   158,   159,   188,   296,   196,   197,   161,
     162,   216,   217,   313,   314,   163,   164,   191,   213,   214,
     166,   167,   168,   169,   170,   209,   265,   266,   374,   297,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   438,   282,   283,   284,   443,
     285,   286
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     160,   153,   300,   165,   293,   205,   222,   324,   316,   338,
     190,   298,   156,   400,   210,   208,   318,   206,   329,   203,
     331,   221,   343,   385,   -15,   181,   218,   179,   352,   353,
     180,   182,   336,   321,   173,   340,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   203,   476,   376,   377,
     195,   385,   195,   171,   -15,   373,    -6,   344,   483,   468,
     492,   476,   203,   354,   355,   172,   174,  -353,   218,   378,
     195,   218,   415,   379,   203,   195,   444,   292,   195,   446,
     195,   177,   320,   306,   309,   386,   413,   401,   184,   307,
     310,   456,   341,   195,   451,   457,   464,   341,   388,   300,
     382,   341,   465,   485,   302,   436,   466,   303,   467,   341,
     316,   442,   192,   179,   385,   406,   305,   385,   341,   408,
     340,   342,   412,   395,   298,   211,   207,   300,   390,   389,
     219,   391,   385,   417,   221,   425,   426,   427,   428,   190,
     396,   341,   396,   397,   407,   450,   144,   145,   146,   160,
     153,   392,   165,   218,   360,   361,   362,   358,   189,   359,
     482,   156,   287,   202,   -11,   160,   288,   437,   350,   351,
     218,   491,   294,   411,   215,   301,   220,   356,   357,   308,
     316,   264,   341,   409,   165,   206,   341,   461,   300,   311,
     189,   319,   479,   325,   412,   326,   480,   332,   385,   423,
     424,   300,   330,   299,   429,   430,   202,   322,   333,   385,
     323,   431,   432,   327,   -15,   182,   215,   448,   317,   215,
    -352,   345,   346,   349,   347,   264,   380,   348,   165,   402,
     336,   387,   458,   452,   459,   471,   341,   462,   473,   489,
     218,   470,   463,   474,   264,   411,   472,   165,   488,   334,
     335,   495,   478,   264,   493,   439,   165,   206,   460,   178,
     486,   183,   204,   404,   454,   487,   381,   290,   449,   291,
     494,   340,   394,   176,   469,   398,   393,   416,   418,   420,
     484,   419,     0,     0,     0,     0,     0,   189,   375,   421,
     300,     0,   422,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   299,     0,   215,     0,
       0,     0,     0,     0,     0,   264,   403,     0,   165,     0,
       0,     0,     0,   264,     0,     0,     0,     0,   264,     0,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   299,     0,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,   433,   434,
     435,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   264,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   264,     0,   264,   165,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   264,     0,   264,   165,     0,   165,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   264,   264,
       0,   165,   165,     1,     2,     3,     4,     5,     6,   223,
     224,   225,     0,   226,   227,   228,   229,     0,   230,   231,
     232,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   233,   234,   235,   236,   237,
     238,   239,   240,     0,     0,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,     0,     0,   244,   245,
       0,     0,     0,     0,   246,   247,   248,   249,   250,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   143,
     144,   145,   146,   147,     1,     2,     3,     4,     5,     6,
     223,   224,   225,     0,   226,   227,   228,   229,     0,   230,
     231,   232,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   233,   234,   235,   236,
     237,   238,   239,   240,     0,     0,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   243,     0,     0,     0,   244,
     337,     0,     0,     0,     0,   246,   247,   248,   249,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   146,   147,     1,     2,     3,     4,     5,
       6,   223,   224,   225,     0,   226,   227,   228,   229,     0,
     230,   231,   232,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   233,   234,   235,
     236,   237,   238,   239,   240,     0,     0,   241,   242,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   243,     0,     0,     0,
     244,   339,     0,     0,     0,     0,   246,   247,   248,   249,
     250,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     142,   143,   144,   145,   146,   147,     1,     2,     3,     4,
       5,     6,   223,   224,   225,     0,   226,   227,   228,   229,
       0,   230,   231,   232,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   233,   234,
     235,   236,   237,   238,   239,   240,     0,     0,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   243,     0,     0,
       0,   244,   414,     0,     0,     0,     0,   246,   247,   248,
     249,   250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   143,   144,   145,   146,   147,     1,     2,     3,
       4,     5,     6,   223,   224,   225,     0,   226,   227,   228,
     229,     0,   230,   231,   232,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   233,
     234,   235,   236,   237,   238,   239,   240,     0,     0,   241,
     242,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   243,     0,
       0,     0,   244,     0,     0,     0,     0,     0,   246,   247,
     248,   249,   250,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   143,   144,   145,   146,   147,     1,     2,
       3,     4,     5,     6,   223,   224,   225,     0,   226,   227,
     228,   229,     0,   230,   231,   232,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     233,   234,   235,   236,   237,   238,   239,   240,     0,     0,
     241,   242,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   243,
       0,     0,     0,   181,     0,     0,     0,     0,     0,   246,
     247,   248,   249,   250,     1,     2,     3,     4,     5,     6,
       0,     0,     0,   142,   143,   144,   145,   146,   147,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,   234,   235,   236,
     237,   238,   239,   240,     0,     0,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   246,   247,   248,   249,   250,
       1,     2,     3,     4,     5,     6,     0,     0,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,   146,
     147,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     0,   234,   235,   236,   237,
     238,   239,   240,     0,     0,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   247,   248,   249,   250,     1,
       2,     3,     4,     5,     6,     0,     0,     0,   142,   143,
     144,   145,   146,     0,     0,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,   198,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     199,     1,     2,     3,     4,     5,     6,     0,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,   146,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,     0,   141,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   315,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
     146,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     0,   141,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   399,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     0,     0,     0,     0,     0,     0,     0,   142,   143,
     144,   145,   146,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   447,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     0,     0,     0,     0,     0,     0,     0,
     142,   143,   144,   145,   146,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     4,     5,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   143,   144,   145,   146,    37,    38,    39,
      40,    41,    42,     0,     0,     0,     0,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,   234,   235,   236,   237,   238,   239,   240,     0,
       0,   241,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     243,     0,     0,     0,   383,   481,     2,     3,     4,     5,
       6,   247,   248,   249,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,     0,
       0,     0,     0,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,     0,   234,   235,
     236,   237,   238,   239,   240,     0,     0,   241,   242,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   243,     0,     0,   295,
       2,     3,     4,     5,     6,     0,     0,   247,   248,   249,
     250,     0,     0,     0,     0,     0,     0,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,     0,     0,     0,     0,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,   234,   235,   236,   237,   238,   239,   240,     0,
       0,   241,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     243,     2,     3,     4,     5,     6,     0,     0,     0,     0,
     328,   247,   248,   249,   250,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,    41,    42,     0,     0,     0,     0,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,   234,   235,   236,   237,   238,   239,   240,
       0,     0,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   243,     0,     0,     0,   383,     2,     3,     4,     5,
       6,     0,   247,   248,   249,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,     0,
       0,     0,     0,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,     0,   234,   235,
     236,   237,   238,   239,   240,     0,     0,   241,   242,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   243,     2,     3,     4,
       5,     6,     0,     0,     0,     0,     0,   247,   248,   249,
     250,     0,     0,     0,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   440,     0,   234,
     235,   236,   237,   238,   239,   240,     0,     0,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   441,     2,     3,
       4,     5,     6,     0,     0,     0,     0,     0,   247,   248,
     249,   250,     0,     0,     0,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,    41,
      42,     0,     0,     0,     0,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     141
};

static const yytype_int16 yycheck[] =
{
       0,     0,   196,     0,   193,   165,   179,   225,   216,   244,
     158,   195,     0,   320,    45,   171,   219,   165,   229,   163,
     231,   156,   172,   292,   156,   188,   174,   191,   167,   168,
     194,   194,   243,   222,   156,   253,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   190,   458,   165,   166,
     186,   320,   186,   184,   186,   193,   188,   207,   194,   194,
     194,   472,   206,   202,   203,   184,   188,   184,   216,   186,
     186,   219,   341,   190,   218,   186,   383,   193,   186,   386,
     186,     0,   193,   185,   185,   193,   185,   193,   185,   191,
     191,   185,   191,   186,   401,   185,   185,   191,   301,   293,
     289,   191,   191,   185,   191,   374,   189,   194,   191,   191,
     318,   380,   156,   191,   383,   326,   194,   386,   191,   330,
     338,   194,   333,   312,   308,   156,   156,   321,   191,   302,
     188,   194,   401,   344,   156,   352,   353,   354,   355,   287,
     191,   191,   191,   194,   194,   194,   210,   211,   212,   149,
     149,   307,   149,   301,   199,   200,   201,   196,   158,   198,
     467,   149,   191,   163,   184,   165,   156,   378,   169,   170,
     318,   478,   184,   333,   174,   188,   176,   163,   164,   193,
     388,   181,   191,   192,   181,   333,   191,   192,   382,   156,
     190,   194,   461,   184,   405,   184,   465,   192,   467,   350,
     351,   395,   184,   195,   356,   357,   206,   194,   184,   478,
     194,   358,   359,   194,   156,   194,   216,   390,   218,   219,
     184,   173,   171,   206,   204,   225,   184,   205,   225,   155,
     441,   187,   185,   184,   156,   194,   191,   187,   456,   474,
     388,   452,   185,   188,   244,   405,   185,   244,    12,   241,
     242,   189,   193,   253,   194,   379,   253,   405,   411,   149,
     471,   156,   165,   325,   405,   472,   287,   190,   396,   190,
     488,   489,   310,   147,   447,   317,   308,   343,   345,   347,
     469,   346,    -1,    -1,    -1,    -1,    -1,   287,   280,   348,
     484,    -1,   349,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,   318,    -1,
      -1,    -1,    -1,    -1,    -1,   325,   325,    -1,   325,    -1,
      -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,   338,    -1,
      -1,   338,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   343,    -1,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   456,    -1,   458,   456,
      -1,   458,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   472,    -1,   474,   472,    -1,   474,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   488,   489,
      -1,   488,   489,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    -1,    -1,   165,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,   188,   189,
      -1,    -1,    -1,    -1,   194,   195,   196,   197,   198,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,   211,   212,   213,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,    -1,    -1,   165,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,   188,
     189,    -1,    -1,    -1,    -1,   194,   195,   196,   197,   198,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,   211,   212,   213,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,    -1,    -1,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,
     188,   189,    -1,    -1,    -1,    -1,   194,   195,   196,   197,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,   211,   212,   213,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    14,    15,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,    -1,    -1,   165,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,
      -1,   188,   189,    -1,    -1,    -1,    -1,   194,   195,   196,
     197,   198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,   211,   212,   213,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,    -1,    -1,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,
      -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,   194,   195,
     196,   197,   198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,   212,   213,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,    -1,    -1,
     165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
      -1,    -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,   194,
     195,   196,   197,   198,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,   208,   209,   210,   211,   212,   213,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,    -1,   156,   157,   158,
     159,   160,   161,   162,    -1,    -1,   165,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   194,   195,   196,   197,   198,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,   208,
     209,   210,   211,   212,   213,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,    -1,   156,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,   208,   209,   210,   211,   212,
     213,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,    -1,   156,   157,   158,   159,
     160,   161,   162,    -1,    -1,   165,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   195,   196,   197,   198,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,   208,   209,
     210,   211,   212,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,    -1,   156,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     194,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,   209,   210,   211,   212,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,    -1,   156,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,   211,
     212,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,    -1,   156,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   189,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,   211,   212,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,    -1,   156,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   189,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,   211,   212,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,    -1,
     156,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,   212,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,    -1,   156,   157,   158,   159,   160,   161,   162,    -1,
      -1,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    -1,    -1,    -1,   188,   189,     4,     5,     6,     7,
       8,   195,   196,   197,   198,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,    -1,   156,   157,
     158,   159,   160,   161,   162,    -1,    -1,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,   187,
       4,     5,     6,     7,     8,    -1,    -1,   195,   196,   197,
     198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,    -1,   156,   157,   158,   159,   160,   161,   162,    -1,
      -1,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
     194,   195,   196,   197,   198,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,    -1,   156,   157,   158,   159,   160,   161,   162,
      -1,    -1,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,    -1,    -1,    -1,   188,     4,     5,     6,     7,
       8,    -1,   195,   196,   197,   198,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,    -1,   156,   157,
     158,   159,   160,   161,   162,    -1,    -1,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,   195,   196,   197,
     198,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,    -1,   156,
     157,   158,   159,   160,   161,   162,    -1,    -1,   165,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,   195,   196,
     197,   198,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,    -1,
     156
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   156,   208,   209,   210,   211,   212,   213,   277,   278,
     288,   289,   290,   296,   298,   299,   314,   315,   319,   320,
     322,   325,   326,   331,   332,   333,   336,   337,   338,   339,
     340,   184,   184,   156,   188,   281,   336,     0,   289,   191,
     194,   188,   194,   291,   185,   316,   317,   318,   321,   322,
     331,   333,   156,   280,   284,   186,   323,   324,   156,   194,
     279,   282,   322,   332,   298,   320,   331,   156,   282,   341,
      45,   156,   287,   334,   335,   322,   327,   328,   331,   188,
     322,   156,   280,     9,    10,    11,    13,    14,    15,    16,
      18,    19,    20,   155,   156,   157,   158,   159,   160,   161,
     162,   165,   166,   184,   188,   189,   194,   195,   196,   197,
     198,   286,   292,   293,   294,   295,   296,   302,   303,   304,
     306,   307,   313,   314,   322,   342,   343,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   362,   363,   364,   366,   367,   191,   156,   283,
     318,   321,   193,   323,   184,   187,   322,   345,   346,   358,
     324,   188,   191,   194,   297,   194,   185,   191,   193,   185,
     191,   156,   285,   329,   330,   189,   328,   322,   327,   194,
     193,   323,   194,   194,   292,   184,   184,   194,   194,   342,
     184,   342,   192,   184,   358,   358,   342,   189,   293,   189,
     292,   191,   194,   172,   207,   173,   171,   204,   205,   206,
     169,   170,   167,   168,   202,   203,   163,   164,   196,   198,
     199,   200,   201,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   193,   344,   358,   165,   166,   186,   190,
     184,   317,   323,   188,   300,   343,   193,   187,   327,   280,
     191,   194,   282,   345,   335,   323,   191,   194,   329,   189,
     300,   193,   155,   296,   302,   309,   342,   194,   342,   192,
     311,   320,   342,   185,   189,   343,   348,   342,   349,   350,
     351,   352,   353,   354,   354,   355,   355,   355,   355,   356,
     356,   357,   357,   358,   358,   358,   343,   342,   361,   285,
     154,   184,   343,   365,   300,   301,   300,   189,   280,   330,
     194,   300,   184,   310,   311,   312,   185,   185,   185,   156,
     286,   192,   187,   185,   185,   191,   189,   191,   194,   280,
     342,   194,   185,   292,   188,   291,   295,   308,   193,   343,
     343,   189,   300,   194,   323,   185,   342,   308,    12,   293,
     305,   300,   194,   194,   292,   189
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   276,   277,   277,   278,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   295,   295,
     295,   295,   295,   295,   295,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   297,   297,   298,   298,   298,
     298,   298,   299,   299,   299,   299,   299,   300,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   305,   305,   306,
     306,   307,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   313,   313,   313,   314,
     315,   315,   316,   316,   317,   317,   317,   317,   318,   318,
     319,   320,   320,   321,   322,   322,   323,   323,   324,   324,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   326,   326,   327,   327,   328,   328,   329,   329,   330,
     330,   331,   331,   332,   332,   332,   332,   332,   332,   333,
     334,   334,   335,   335,   335,   336,   336,   336,   337,   337,
     337,   338,   339,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     341,   341,   342,   342,   343,   343,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   345,   346,   346,
     347,   347,   348,   348,   349,   349,   350,   350,   351,   351,
     352,   352,   353,   353,   353,   354,   354,   354,   354,   354,
     355,   355,   355,   356,   356,   356,   357,   357,   357,   357,
     358,   358,   358,   358,   359,   359,   359,   359,   360,   360,
     360,   360,   360,   360,   361,   362,   363,   364,   364,   364,
     365,   365,   366,   366,   367,   367,   367,   367,   367,   367,
     367,   367
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     3,     1,     1,     1,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     6,     7,
       8,     2,     3,     4,     3,     2,     3,     1,     3,     4,
       6,     5,     1,     2,     3,     5,     4,     1,     3,     4,
       1,     3,     1,     2,     5,     7,     7,     0,     1,     3,
       2,     5,     7,     6,     1,     1,     1,     1,     1,     0,
       1,     4,     2,     3,     2,     2,     2,     3,     2,     2,
       1,     2,     1,     3,     2,     1,     2,     1,     2,     3,
       3,     1,     2,     1,     1,     2,     1,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     1,     2,     3,     4,     1,     3,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     4,
       1,     3,     2,     2,     1,     1,     1,     4,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3
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
      yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
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
#if GLSL_DEBUG

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
# if defined GLSL_LTYPE_IS_TRIVIAL && GLSL_LTYPE_IS_TRIVIAL

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
                  Type, Value, Location, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, glsl_parse_context * context)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, glsl_parse_context * context)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, context);
  YYFPRINTF (yyo, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, glsl_parse_context * context)
{
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, context); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !GLSL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !GLSL_DEBUG */


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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, glsl_parse_context * context)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (glsl_parse_context * context)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined GLSL_LTYPE_IS_TRIVIAL && GLSL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

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
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

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
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
                  (unsigned long) yystacksize));

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
      yychar = yylex (&yylval, &yylloc, scanner);
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 505 "glsl.y" /* yacc.c:1660  */
    { context->root = new_glsl_node(context, TRANSLATION_UNIT, NULL); }
#line 3218 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 3:
#line 506 "glsl.y" /* yacc.c:1660  */
    { context->root = (*(glsl_node **)(&yyvsp[0])); }
#line 3224 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 4:
#line 510 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TRANSLATION_UNIT, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3230 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 5:
#line 513 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TRANSLATION_UNIT, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3236 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 6:
#line 516 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3242 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 7:
#line 519 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3248 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 8:
#line 522 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3254 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 9:
#line 525 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3260 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 10:
#line 528 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3266 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 11:
#line 531 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3272 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 12:
#line 534 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_string(context, FIELD_IDENTIFIER, (*(char **)(&yyvsp[0]))); }
#line 3278 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 13:
#line 537 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3284 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 14:
#line 540 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3290 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 15:
#line 543 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_identifier(context, (*(char **)(&yyvsp[0]))); }
#line 3296 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 16:
#line 546 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3302 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 17:
#line 547 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3308 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 18:
#line 551 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_DEFINITION,
					(*(glsl_node **)(&yyvsp[-1])),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3317 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 19:
#line 556 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_DEFINITION,
					(*(glsl_node **)(&yyvsp[0])),
					new_glsl_node(context, STATEMENT_LIST, NULL),
					NULL); }
#line 3326 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 20:
#line 562 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STATEMENT_LIST, NULL); }
#line 3332 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 21:
#line 563 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[-1])); }
#line 3338 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 22:
#line 566 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3344 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 23:
#line 567 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3350 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 24:
#line 570 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STATEMENT_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3356 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 25:
#line 571 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STATEMENT_LIST, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3362 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 26:
#line 574 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STATEMENT_LIST, NULL); }
#line 3368 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 27:
#line 575 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[-1])); }
#line 3374 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 28:
#line 578 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3380 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 29:
#line 579 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3386 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 30:
#line 580 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3392 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 31:
#line 581 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3398 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 32:
#line 582 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval))= (*(glsl_node **)(&yyvsp[0])); }
#line 3404 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 33:
#line 583 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3410 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 34:
#line 584 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3416 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 35:
#line 587 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3422 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 36:
#line 588 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3428 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 37:
#line 590 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, PRECISION_DECLARATION,
							(*(glsl_node **)(&yyvsp[-2])),
							(*(glsl_node **)(&yyvsp[-1])),
							NULL),
						NULL); }
#line 3439 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 38:
#line 597 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, BLOCK_DECLARATION,
							(*(glsl_node **)(&yyvsp[-5])),
							(*(glsl_node **)(&yyvsp[-4])),
							(*(glsl_node **)(&yyvsp[-2])),
							new_glsl_identifier(context, NULL),
							new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
							NULL),
						NULL); }
#line 3453 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 39:
#line 607 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, BLOCK_DECLARATION,
							(*(glsl_node **)(&yyvsp[-6])),
							(*(glsl_node **)(&yyvsp[-5])),
							(*(glsl_node **)(&yyvsp[-3])),
							(*(glsl_node **)(&yyvsp[-1])),
							new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
							NULL),
						NULL); }
#line 3467 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 40:
#line 617 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, BLOCK_DECLARATION,
							(*(glsl_node **)(&yyvsp[-7])),
							(*(glsl_node **)(&yyvsp[-6])),
							(*(glsl_node **)(&yyvsp[-4])),
							(*(glsl_node **)(&yyvsp[-2])),
							(*(glsl_node **)(&yyvsp[-1])),
							NULL),
						NULL); }
#line 3481 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 41:
#line 627 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, UNINITIALIZED_DECLARATION,
							(*(glsl_node **)(&yyvsp[-1])),
							new_glsl_identifier(context, NULL),
							NULL),
						NULL); }
#line 3492 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 42:
#line 634 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, UNINITIALIZED_DECLARATION,
							(*(glsl_node **)(&yyvsp[-2])),
							(*(glsl_node **)(&yyvsp[-1])),
							new_glsl_node(context, IDENTIFIER_LIST, NULL),
							NULL),
						NULL); }
#line 3504 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 43:
#line 642 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DECLARATION,
						new_glsl_node(context, UNINITIALIZED_DECLARATION,
							(*(glsl_node **)(&yyvsp[-3])),
							(*(glsl_node **)(&yyvsp[-2])),
							(*(glsl_node **)(&yyvsp[-1])),
							NULL),
						NULL); }
#line 3516 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 44:
#line 650 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LAYOUT_QUALIFIER,
						(*(glsl_node **)(&yyvsp[-2])),
						new_glsl_node(context, DECLARATION,
							(*(glsl_node **)(&yyvsp[-1])),
							NULL),
						NULL); }
#line 3527 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 45:
#line 659 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IDENTIFIER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3533 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 46:
#line 661 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IDENTIFIER_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3539 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 47:
#line 664 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INIT_DECLARATOR_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3545 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 48:
#line 666 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INIT_DECLARATOR_LIST,
						(*(glsl_node **)(&yyvsp[-2])),
						new_glsl_node(context, INIT_DECLARATOR,
							(*(glsl_node **)(&yyvsp[0])),
							new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
							NULL),
						NULL); }
#line 3557 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 49:
#line 674 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INIT_DECLARATOR_LIST,
						(*(glsl_node **)(&yyvsp[-3])),
						new_glsl_node(context, INIT_DECLARATOR,
							(*(glsl_node **)(&yyvsp[-1])),
							(*(glsl_node **)(&yyvsp[0])),
							NULL),
						NULL); }
#line 3569 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 50:
#line 682 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INIT_DECLARATOR_LIST,
						(*(glsl_node **)(&yyvsp[-5])),
						new_glsl_node(context, INIT_DECLARATOR,
							(*(glsl_node **)(&yyvsp[-3])),
							(*(glsl_node **)(&yyvsp[-2])),
							(*(glsl_node **)(&yyvsp[0])),
							NULL),
						NULL); }
#line 3582 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 51:
#line 691 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INIT_DECLARATOR_LIST,
						(*(glsl_node **)(&yyvsp[-4])),
						new_glsl_node(context, INIT_DECLARATOR,
							(*(glsl_node **)(&yyvsp[-2])),
							new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
							(*(glsl_node **)(&yyvsp[0])),
							NULL),
						NULL); }
#line 3595 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 52:
#line 702 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SINGLE_DECLARATION,
					(*(glsl_node **)(&yyvsp[0])),
					new_glsl_identifier(context, NULL),
					new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
					NULL); }
#line 3605 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 53:
#line 709 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SINGLE_DECLARATION,
					(*(glsl_node **)(&yyvsp[-1])),
					(*(glsl_node **)(&yyvsp[0])),
					new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
					NULL); }
#line 3615 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 54:
#line 716 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SINGLE_DECLARATION, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3621 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 55:
#line 719 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SINGLE_INIT_DECLARATION, (*(glsl_node **)(&yyvsp[-4])), (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3627 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 56:
#line 722 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SINGLE_INIT_DECLARATION,
					(*(glsl_node **)(&yyvsp[-3])),
					(*(glsl_node **)(&yyvsp[-2])),
					new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3638 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 57:
#line 730 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INITIALIZER, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3644 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 58:
#line 731 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INITIALIZER, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3650 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 59:
#line 732 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INITIALIZER, (*(glsl_node **)(&yyvsp[-2])), NULL); }
#line 3656 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 60:
#line 736 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INITIALIZER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3662 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 61:
#line 738 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INITIALIZER_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3668 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 62:
#line 741 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, EXPRESSION_STATEMENT, NULL); }
#line 3674 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 63:
#line 742 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, EXPRESSION_STATEMENT, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3680 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 64:
#line 746 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SELECTION_STATEMENT, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3686 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 65:
#line 749 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SELECTION_STATEMENT_ELSE, (*(glsl_node **)(&yyvsp[-4])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3692 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 66:
#line 753 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SWITCH_STATEMENT, (*(glsl_node **)(&yyvsp[-4])), (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3698 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 67:
#line 756 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STATEMENT_LIST, NULL); }
#line 3704 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 68:
#line 757 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3710 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 69:
#line 760 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CASE_LABEL, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3716 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 70:
#line 761 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CASE_LABEL, NULL); }
#line 3722 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 71:
#line 765 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, WHILE_STATEMENT, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3728 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 72:
#line 768 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DO_STATEMENT, (*(glsl_node **)(&yyvsp[-5])), (*(glsl_node **)(&yyvsp[-2])), NULL); }
#line 3734 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 73:
#line 771 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FOR_STATEMENT, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3740 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 74:
#line 774 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3746 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 75:
#line 775 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3752 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 76:
#line 778 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3758 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 77:
#line 779 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 3764 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 78:
#line 782 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CONDITION_OPT, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3770 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 79:
#line 783 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CONDITION_OPT, NULL); }
#line 3776 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 80:
#line 787 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, EXPRESSION_CONDITION, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3782 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 81:
#line 790 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ASSIGNMENT_CONDITION, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3788 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 82:
#line 794 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FOR_REST_STATEMENT, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3794 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 83:
#line 797 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FOR_REST_STATEMENT, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3800 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 84:
#line 801 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CONTINUE, NULL); }
#line 3806 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 85:
#line 804 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BREAK, NULL); }
#line 3812 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 86:
#line 807 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, RETURN, NULL); }
#line 3818 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 87:
#line 810 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, RETURN_VALUE, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3824 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 88:
#line 813 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DISCARD, NULL); }
#line 3830 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 89:
#line 816 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[-1])); }
#line 3836 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 90:
#line 820 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_DECLARATION,
					(*(glsl_node **)(&yyvsp[0])),
					new_glsl_node(context, FUNCTION_PARAMETER_LIST, NULL),
					NULL); }
#line 3845 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 91:
#line 826 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_DECLARATION,
					(*(glsl_node **)(&yyvsp[-1])),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3854 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 92:
#line 833 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_PARAMETER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3860 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 93:
#line 836 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_PARAMETER_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3866 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 94:
#line 840 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATION, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3872 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 95:
#line 843 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATION,
					new_glsl_node(context, TYPE_QUALIFIER_LIST, NULL),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3881 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 96:
#line 849 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATION, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3887 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 97:
#line 852 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATION,
					new_glsl_node(context, TYPE_QUALIFIER_LIST, NULL),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3896 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 98:
#line 859 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATOR, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3902 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 99:
#line 862 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATOR, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL);}
#line 3908 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 100:
#line 866 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_HEADER, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3914 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 101:
#line 870 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FULLY_SPECIFIED_TYPE,
					new_glsl_node(context, TYPE_QUALIFIER_LIST, NULL),
					(*(glsl_node **)(&yyvsp[0])),
					NULL); }
#line 3923 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 102:
#line 876 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FULLY_SPECIFIED_TYPE, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3929 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 103:
#line 880 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PARAMETER_DECLARATOR, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3935 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 104:
#line 884 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TYPE_SPECIFIER,
					(*(glsl_node **)(&yyvsp[0])),
					new_glsl_node(context, ARRAY_SPECIFIER_LIST, NULL),
					NULL); }
#line 3944 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 105:
#line 890 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TYPE_SPECIFIER, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3950 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 106:
#line 894 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ARRAY_SPECIFIER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3956 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 107:
#line 897 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ARRAY_SPECIFIER_LIST, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 3962 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 108:
#line 901 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ARRAY_SPECIFIER, NULL); }
#line 3968 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 109:
#line 904 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ARRAY_SPECIFIER, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 3974 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 110:
#line 907 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VOID, NULL); }
#line 3980 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 111:
#line 908 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FLOAT, NULL); }
#line 3986 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 112:
#line 909 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DOUBLE, NULL); }
#line 3992 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 113:
#line 910 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INT, NULL); }
#line 3998 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 114:
#line 911 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UINT, NULL); }
#line 4004 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 115:
#line 912 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BOOL, NULL); }
#line 4010 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 116:
#line 913 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VEC2, NULL); }
#line 4016 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 117:
#line 914 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VEC3, NULL); }
#line 4022 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 118:
#line 915 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VEC4, NULL); }
#line 4028 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 119:
#line 916 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DVEC2, NULL); }
#line 4034 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 120:
#line 917 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DVEC3, NULL); }
#line 4040 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 121:
#line 918 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DVEC4, NULL); }
#line 4046 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 122:
#line 919 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BVEC2, NULL); }
#line 4052 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 123:
#line 920 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BVEC3, NULL); }
#line 4058 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 124:
#line 921 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BVEC4, NULL); }
#line 4064 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 125:
#line 922 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IVEC2, NULL); }
#line 4070 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 126:
#line 923 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IVEC3, NULL); }
#line 4076 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 127:
#line 924 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IVEC4, NULL); }
#line 4082 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 128:
#line 925 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UVEC2, NULL); }
#line 4088 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 129:
#line 926 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UVEC3, NULL); }
#line 4094 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 130:
#line 927 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UVEC4, NULL); }
#line 4100 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 131:
#line 928 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT2, NULL); }
#line 4106 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 132:
#line 929 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT3, NULL); }
#line 4112 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 133:
#line 930 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT4, NULL); }
#line 4118 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 134:
#line 931 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT2X2, NULL); }
#line 4124 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 135:
#line 932 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT2X3, NULL); }
#line 4130 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 136:
#line 933 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT2X4, NULL); }
#line 4136 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 137:
#line 934 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT3X2, NULL); }
#line 4142 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 138:
#line 935 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT3X3, NULL); }
#line 4148 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 139:
#line 936 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT3X4, NULL); }
#line 4154 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 140:
#line 937 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT4X2, NULL); }
#line 4160 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 141:
#line 938 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT4X3, NULL); }
#line 4166 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 142:
#line 939 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MAT4X4, NULL); }
#line 4172 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 143:
#line 940 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT2, NULL); }
#line 4178 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 144:
#line 941 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT3, NULL); }
#line 4184 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 145:
#line 942 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT4, NULL); }
#line 4190 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 146:
#line 943 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT2X2, NULL); }
#line 4196 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 147:
#line 944 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT2X3, NULL); }
#line 4202 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 148:
#line 945 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT2X4, NULL); }
#line 4208 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 149:
#line 946 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT3X2, NULL); }
#line 4214 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 150:
#line 947 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT3X3, NULL); }
#line 4220 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 151:
#line 948 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT3X4, NULL); }
#line 4226 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 152:
#line 949 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT4X2, NULL); }
#line 4232 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 153:
#line 950 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT4X3, NULL); }
#line 4238 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 154:
#line 951 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DMAT4X4, NULL); }
#line 4244 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 155:
#line 952 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UINT, NULL); }
#line 4250 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 156:
#line 953 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER1D, NULL); }
#line 4256 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 157:
#line 954 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2D, NULL); }
#line 4262 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 158:
#line 955 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER3D, NULL); }
#line 4268 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 159:
#line 956 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLERCUBE, NULL); }
#line 4274 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 160:
#line 957 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER1DSHADOW, NULL); }
#line 4280 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 161:
#line 958 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DSHADOW, NULL); }
#line 4286 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 162:
#line 959 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLERCUBESHADOW, NULL); }
#line 4292 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 163:
#line 960 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER1DARRAY, NULL); }
#line 4298 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 164:
#line 961 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DARRAY, NULL); }
#line 4304 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 165:
#line 962 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER1DARRAYSHADOW, NULL); }
#line 4310 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 166:
#line 963 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DARRAYSHADOW, NULL); }
#line 4316 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 167:
#line 964 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLERCUBEARRAY, NULL); }
#line 4322 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 168:
#line 965 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLERCUBEARRAYSHADOW, NULL); }
#line 4328 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 169:
#line 966 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER1D, NULL); }
#line 4334 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 170:
#line 967 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER2D, NULL); }
#line 4340 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 171:
#line 968 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER3D, NULL); }
#line 4346 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 172:
#line 969 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLERCUBE, NULL); }
#line 4352 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 173:
#line 970 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER1DARRAY, NULL); }
#line 4358 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 174:
#line 971 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER2DARRAY, NULL); }
#line 4364 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 175:
#line 972 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLERCUBEARRAY, NULL); }
#line 4370 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 176:
#line 973 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER1D, NULL); }
#line 4376 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 177:
#line 974 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER2D, NULL); }
#line 4382 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 178:
#line 975 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER3D, NULL); }
#line 4388 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 179:
#line 976 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLERCUBE, NULL); }
#line 4394 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 180:
#line 977 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER1DARRAY, NULL); }
#line 4400 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 181:
#line 978 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER2DARRAY, NULL); }
#line 4406 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 182:
#line 979 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLERCUBEARRAY, NULL); }
#line 4412 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 183:
#line 980 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DRECT, NULL); }
#line 4418 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 184:
#line 981 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DRECTSHADOW, NULL); }
#line 4424 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 185:
#line 982 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER2DRECT, NULL); }
#line 4430 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 186:
#line 983 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER2DRECT, NULL); }
#line 4436 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 187:
#line 984 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLERBUFFER, NULL); }
#line 4442 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 188:
#line 985 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLERBUFFER, NULL); }
#line 4448 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 189:
#line 986 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLERBUFFER, NULL); }
#line 4454 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 190:
#line 987 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DMS, NULL); }
#line 4460 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 191:
#line 988 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER2DMS, NULL); }
#line 4466 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 192:
#line 989 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER2DMS, NULL); }
#line 4472 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 193:
#line 990 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLER2DMSARRAY, NULL); }
#line 4478 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 194:
#line 991 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ISAMPLER2DMSARRAY, NULL); }
#line 4484 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 195:
#line 992 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, USAMPLER2DMSARRAY, NULL); }
#line 4490 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 196:
#line 993 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE1D, NULL); }
#line 4496 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 197:
#line 994 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE1D, NULL); }
#line 4502 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 198:
#line 995 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE1D, NULL); }
#line 4508 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 199:
#line 996 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE2D, NULL); }
#line 4514 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 200:
#line 997 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE2D, NULL); }
#line 4520 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 201:
#line 998 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE2D, NULL); }
#line 4526 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 202:
#line 999 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE3D, NULL); }
#line 4532 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 203:
#line 1000 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE3D, NULL); }
#line 4538 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 204:
#line 1001 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE3D, NULL); }
#line 4544 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 205:
#line 1002 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE2DRECT, NULL); }
#line 4550 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 206:
#line 1003 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE2DRECT, NULL); }
#line 4556 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 207:
#line 1004 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE2DRECT, NULL); }
#line 4562 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 208:
#line 1005 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGECUBE, NULL); }
#line 4568 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 209:
#line 1006 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGECUBE, NULL); }
#line 4574 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 210:
#line 1007 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGECUBE, NULL); }
#line 4580 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 211:
#line 1008 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGEBUFFER, NULL); }
#line 4586 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 212:
#line 1009 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGEBUFFER, NULL); }
#line 4592 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 213:
#line 1010 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGEBUFFER, NULL); }
#line 4598 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 214:
#line 1011 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE1DARRAY, NULL); }
#line 4604 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 215:
#line 1012 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE1DARRAY, NULL); }
#line 4610 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 216:
#line 1013 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE1DARRAY, NULL); }
#line 4616 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 217:
#line 1014 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE2DARRAY, NULL); }
#line 4622 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 218:
#line 1015 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE2DARRAY, NULL); }
#line 4628 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 219:
#line 1016 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE2DARRAY, NULL); }
#line 4634 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 220:
#line 1017 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGECUBEARRAY, NULL); }
#line 4640 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 221:
#line 1018 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGECUBEARRAY, NULL); }
#line 4646 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 222:
#line 1019 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGECUBEARRAY, NULL); }
#line 4652 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 223:
#line 1020 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE2DMS, NULL); }
#line 4658 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 224:
#line 1021 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE2DMS, NULL); }
#line 4664 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 225:
#line 1022 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE2DMS, NULL); }
#line 4670 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 226:
#line 1023 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IMAGE2DMSARRAY, NULL); }
#line 4676 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 227:
#line 1024 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IIMAGE2DMSARRAY, NULL); }
#line 4682 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 228:
#line 1025 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UIMAGE2DMSARRAY, NULL); }
#line 4688 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 229:
#line 1026 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4694 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 230:
#line 1027 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4700 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 231:
#line 1031 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_SPECIFIER, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-1])), NULL);}
#line 4706 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 232:
#line 1034 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_SPECIFIER,
						new_glsl_identifier(context, NULL),
						(*(glsl_node **)(&yyvsp[-1])),
						NULL); }
#line 4715 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 233:
#line 1041 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATION_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4721 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 234:
#line 1043 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATION_LIST, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4727 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 235:
#line 1047 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATION,
					new_glsl_node(context, TYPE_QUALIFIER_LIST, NULL),
					(*(glsl_node **)(&yyvsp[-2])),
					(*(glsl_node **)(&yyvsp[-1])),
					NULL); }
#line 4737 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 236:
#line 1054 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATION, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 4743 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 237:
#line 1058 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATOR_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4749 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 238:
#line 1061 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATOR_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4755 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 239:
#line 1065 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATOR, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4761 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 240:
#line 1068 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STRUCT_DECLARATOR, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4767 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 241:
#line 1072 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TYPE_QUALIFIER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4773 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 242:
#line 1074 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TYPE_QUALIFIER_LIST, (*(glsl_node **)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4779 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 243:
#line 1077 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4785 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 244:
#line 1078 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4791 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 245:
#line 1079 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4797 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 246:
#line 1080 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4803 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 247:
#line 1081 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4809 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 248:
#line 1082 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4815 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 249:
#line 1085 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[-1])); }
#line 4821 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 250:
#line 1088 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 4827 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 251:
#line 1091 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LAYOUT_QUALIFIER_ID_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4833 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 252:
#line 1095 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LAYOUT_QUALIFIER_ID, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 4839 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 253:
#line 1098 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LAYOUT_QUALIFIER_ID, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL);}
#line 4845 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 254:
#line 1101 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SHARED, NULL); }
#line 4851 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 255:
#line 1104 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, HIGHP, NULL); }
#line 4857 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 256:
#line 1105 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, MEDIUMP, NULL); }
#line 4863 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 257:
#line 1106 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LOWP, NULL); }
#line 4869 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 258:
#line 1109 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SMOOTH, NULL); }
#line 4875 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 259:
#line 1110 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FLAT, NULL); }
#line 4881 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 260:
#line 1111 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, NOPERSPECTIVE, NULL); }
#line 4887 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 261:
#line 1114 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INVARIANT, NULL); }
#line 4893 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 262:
#line 1117 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PRECISE, NULL); }
#line 4899 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 263:
#line 1120 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CONST, NULL); }
#line 4905 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 264:
#line 1121 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INOUT, NULL); }
#line 4911 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 265:
#line 1122 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, IN, NULL); }
#line 4917 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 266:
#line 1123 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, OUT, NULL); }
#line 4923 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 267:
#line 1124 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CENTROID, NULL); }
#line 4929 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 268:
#line 1125 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PATCH, NULL); }
#line 4935 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 269:
#line 1126 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SAMPLE, NULL); }
#line 4941 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 270:
#line 1127 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UNIFORM, NULL); }
#line 4947 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 271:
#line 1128 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, BUFFER, NULL); }
#line 4953 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 272:
#line 1129 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SHARED, NULL); }
#line 4959 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 273:
#line 1130 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, COHERENT, NULL); }
#line 4965 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 274:
#line 1131 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VOLATILE, NULL); }
#line 4971 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 275:
#line 1132 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, RESTRICT, NULL); }
#line 4977 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 276:
#line 1133 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, READONLY, NULL); }
#line 4983 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 277:
#line 1134 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, WRITEONLY, NULL); }
#line 4989 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 278:
#line 1135 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SUBROUTINE, NULL); }
#line 4995 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 279:
#line 1137 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SUBROUTINE_TYPE,
					new_glsl_node(context, TYPE_NAME_LIST, (*(glsl_node **)(&yyvsp[-1])), NULL),
					NULL); }
#line 5003 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 280:
#line 1142 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5009 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 281:
#line 1144 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TYPE_NAME_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5015 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 282:
#line 1147 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5021 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 283:
#line 1149 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, COMMA, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5027 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 284:
#line 1152 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5033 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 285:
#line 1154 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context,(*(int*)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5039 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 286:
#line 1157 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = EQUAL; }
#line 5045 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 287:
#line 1158 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = MUL_ASSIGN; }
#line 5051 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 288:
#line 1159 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = DIV_ASSIGN; }
#line 5057 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 289:
#line 1160 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = MOD_ASSIGN; }
#line 5063 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 290:
#line 1161 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = ADD_ASSIGN; }
#line 5069 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 291:
#line 1162 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = SUB_ASSIGN; }
#line 5075 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 292:
#line 1163 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = LEFT_ASSIGN; }
#line 5081 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 293:
#line 1164 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = RIGHT_ASSIGN; }
#line 5087 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 294:
#line 1165 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = AND_ASSIGN; }
#line 5093 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 295:
#line 1166 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = XOR_ASSIGN; }
#line 5099 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 296:
#line 1167 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = OR_ASSIGN; }
#line 5105 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 297:
#line 1170 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5111 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 298:
#line 1173 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5117 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 299:
#line 1175 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TERNARY_EXPRESSION, (*(glsl_node **)(&yyvsp[-4])), (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5123 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 300:
#line 1178 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5129 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 301:
#line 1180 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, OR_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5135 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 302:
#line 1183 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5141 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 303:
#line 1185 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, XOR_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5147 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 304:
#line 1188 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5153 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 305:
#line 1190 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, AND_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5159 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 306:
#line 1193 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5165 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 307:
#line 1195 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, VERTICAL_BAR, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5171 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 308:
#line 1198 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5177 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 309:
#line 1200 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, CARET, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5183 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 310:
#line 1203 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5189 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 311:
#line 1205 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, AMPERSAND, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5195 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 312:
#line 1208 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5201 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 313:
#line 1211 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, EQ_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5207 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 314:
#line 1214 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, NE_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5213 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 315:
#line 1217 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5219 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 316:
#line 1220 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LEFT_ANGLE, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5225 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 317:
#line 1223 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, RIGHT_ANGLE, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5231 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 318:
#line 1226 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LE_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5237 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 319:
#line 1229 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, GE_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5243 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 320:
#line 1232 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5249 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 321:
#line 1235 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, LEFT_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5255 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 322:
#line 1238 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, RIGHT_OP, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5261 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 323:
#line 1241 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5267 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 324:
#line 1244 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PLUS, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5273 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 325:
#line 1247 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DASH, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5279 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 326:
#line 1250 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5285 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 327:
#line 1253 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, STAR, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5291 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 328:
#line 1256 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, SLASH, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5297 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 329:
#line 1259 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PERCENT, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5303 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 330:
#line 1262 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5309 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 331:
#line 1265 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PRE_INC_OP, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5315 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 332:
#line 1268 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PRE_DEC_OP, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5321 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 333:
#line 1271 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context,(*(int*)(&yyvsp[-1])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5327 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 334:
#line 1274 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = UNARY_PLUS; }
#line 5333 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 335:
#line 1275 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = UNARY_DASH; }
#line 5339 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 336:
#line 1276 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = BANG; }
#line 5345 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 337:
#line 1277 "glsl.y" /* yacc.c:1660  */
    { (*(int*)(&yyval)) = TILDE; }
#line 5351 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 338:
#line 1280 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5357 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 339:
#line 1283 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, ARRAY_REF_OP, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 5363 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 340:
#line 1285 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5369 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 341:
#line 1288 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DOT, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL);}
#line 5375 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 342:
#line 1291 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, POST_INC_OP, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 5381 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 343:
#line 1294 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, POST_DEC_OP, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 5387 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 344:
#line 1297 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5393 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 345:
#line 1300 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5399 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 346:
#line 1303 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5405 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 347:
#line 1307 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_CALL, (*(glsl_node **)(&yyvsp[-3])), (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 5411 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 348:
#line 1310 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_CALL,
					(*(glsl_node **)(&yyvsp[-2])),
					new_glsl_node(context, FUNCTION_CALL_PARAMETER_LIST, NULL),
					NULL); }
#line 5420 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 349:
#line 1316 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_CALL,
					(*(glsl_node **)(&yyvsp[-3])),
					new_glsl_node(context, FUNCTION_CALL_PARAMETER_LIST, NULL),
					NULL); }
#line 5429 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 350:
#line 1323 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_CALL_PARAMETER_LIST, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5435 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 351:
#line 1326 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FUNCTION_CALL_PARAMETER_LIST, (*(glsl_node **)(&yyvsp[-2])), (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5441 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 352:
#line 1329 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5447 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 353:
#line 1332 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, POSTFIX_EXPRESSION, (*(glsl_node **)(&yyvsp[0])), NULL); }
#line 5453 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 354:
#line 1335 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = (*(glsl_node **)(&yyvsp[0])); }
#line 5459 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 355:
#line 1338 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, INTCONSTANT, NULL); (*(glsl_node **)(&yyval))->data.i = (*(int*)(&yyvsp[0])); }
#line 5465 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 356:
#line 1341 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, UINTCONSTANT, NULL); (*(glsl_node **)(&yyval))->data.ui = (*(unsigned int*)(&yyvsp[0])); }
#line 5471 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 357:
#line 1344 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FLOATCONSTANT, NULL); (*(glsl_node **)(&yyval))->data.f = (*(float*)(&yyvsp[0])); }
#line 5477 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 358:
#line 1347 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, TRUE_VALUE, NULL); }
#line 5483 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 359:
#line 1350 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, FALSE_VALUE, NULL); }
#line 5489 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 360:
#line 1353 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, DOUBLECONSTANT, NULL); (*(glsl_node **)(&yyval))->data.d = (*(double*)(&yyvsp[0])); }
#line 5495 "glsl.parser.cpp" /* yacc.c:1660  */
    break;

  case 361:
#line 1356 "glsl.y" /* yacc.c:1660  */
    { (*(glsl_node **)(&yyval)) = new_glsl_node(context, PAREN_EXPRESSION, (*(glsl_node **)(&yyvsp[-1])), NULL); }
#line 5501 "glsl.parser.cpp" /* yacc.c:1660  */
    break;


#line 5505 "glsl.parser.cpp" /* yacc.c:1660  */
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
      yyerror (&yylloc, context, YY_("syntax error"));
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
        yyerror (&yylloc, context, yymsgp);
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
                      yytoken, &yylval, &yylloc, context);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, context);
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
  yyerror (&yylloc, context, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, context);
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
#line 1359 "glsl.y" /* yacc.c:1903  */


#include "glsl_ast.h"

//The scanner macro, needed for integration with flex, causes problems below
#undef scanner

static void glsl_error(GLSL_LTYPE *loc, glsl_parse_context *c, const char *s)
{
	c->error = true;
	if (c->error_cb)
		c->error_cb(s, loc->first_line, loc->first_column, loc->last_column);
}

int list_length(glsl_node *n, int list_token)
{
	if (n->code != list_token) {
		return 1;
	} else {
		int i;
		int count = 0;
		for (i = 0; i < n->child_count; i++) {
			count += list_length(n->children[i], list_token);
		}
		return count;
	}
}

static void list_gather(glsl_node *n, glsl_node *new_list, int list_token)
{
	int i;
	for (i = 0; i < n->child_count; i++) {
		glsl_node *child = n->children[i];
		if (child->code != list_token)
			new_list->children[new_list->child_count++] = child;
		else
			list_gather(child, new_list, list_token);
	}
}

static void list_collapse(glsl_parse_context *context, glsl_node *n)
{
	int i;
	for (i = 0; i < n->child_count; i++) {
		glsl_node *child = n->children[i];
		if (glsl_ast_is_list_node(child)) {
			int list_token = child->code;
			int length = list_length(child, list_token);
			glsl_node *g = (glsl_node *)glsl_parse_alloc(context, offsetof(glsl_node, children[length]), 8);
			g->code = list_token;
			g->child_count = 0;
			list_gather(child, g, list_token);
			n->children[i] = g;
			child = g;
		}
		list_collapse(context, child);
	}
}

static bool parse_internal(glsl_parse_context *context)
{
	context->error = false;
	glsl_parse(context);
	if (context->root) {
		if (glsl_ast_is_list_node(context->root)) {
			//
			// list_collapse() can't combine all the TRANSLATION_UNIT nodes
			// since it would need to replace g_glsl_node_root so we combine
			// the TRANSLATION_UNIT nodes here.
			//
			int list_code = context->root->code;
			int length = list_length(context->root, list_code);
			glsl_node *new_root = (glsl_node *)glsl_parse_alloc(context, offsetof(glsl_node, children[length]), 8);
			new_root->code = TRANSLATION_UNIT;
			new_root->child_count = 0;
			list_gather(context->root, new_root, list_code);
			assert(new_root->child_count == length);
			context->root = new_root;
		}
		//
		// Collapse other list nodes
		//
		list_collapse(context, context->root);
	}
	return context->error;
}

bool glsl_parse_file(glsl_parse_context *context, FILE *file)
{
	glsl_lex_init(&(context->scanner));

	glsl_set_in(file, context->scanner);

	bool error;

	error = parse_internal(context);

	glsl_lex_destroy(context->scanner);
	context->scanner = NULL;
	return error;
}

bool glsl_parse_string(glsl_parse_context *context, const char *str)
{
	char *text;
	size_t sz;
	bool error;

	glsl_lex_init(&(context->scanner));

	sz = strlen(str);
	text = new char[sz + 2];
	strcpy(text, str);
	text[sz + 1] = 0;
	glsl__scan_buffer(text, sz + 2, context->scanner);

	error = parse_internal(context);

	free(text);
	glsl_lex_destroy(context->scanner);
	context->scanner = NULL;
	return error;
}

void glsl_parse_context_init(glsl_parse_context *context)
{
	context->root = NULL;
	context->scanner = NULL;
	context->first_buffer = NULL;
	context->cur_buffer_start = NULL;
	context->cur_buffer = NULL;
	context->cur_buffer_end = NULL;
	context->error_cb = NULL;
	context->error = false;
}

void glsl_parse_set_error_cb(glsl_parse_context *context, glsl_parse_error_cb_t error_cb)
{
	context->error_cb = error_cb;
}


void glsl_parse_context_destroy(glsl_parse_context *context)
{
	glsl_parse_dealloc(context);
}
