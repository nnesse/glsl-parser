%{
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "glsl.tab.h"

#include "glsl_common.h"

#include "lex.glsl.h"
void glslerror(const char *s);
int glsllex (void);

int8_t *buffer = NULL;
int8_t *buffer_end = NULL;
int remaining = 0;

static int8_t *myalloc(size_t size, int align)
{
	int8_t *ret;

	if (size + align > (buffer_end - buffer)) {
		buffer = (int8_t *)malloc(1024*1024);
		buffer_end = buffer + 1024*1024;
	}

	ret = buffer;

	int8_t *trunc = (int8_t *)((~((intptr_t)align - 1)) & ((intptr_t)ret));
	if (trunc != ret) {
		ret = trunc + align;
	}
	buffer = ret + size;
	return ret;
}

static char *mystrdup(const char *c)
{
	int len = strlen(c);
	char *ret = (char *)myalloc(len + 1, 1);
	strcpy(ret, c);
	return ret;
}

#define NEW_STRUCT(TYPE) ((struct TYPE *)myalloc(sizeof(struct TYPE), sizeof(intptr_t)))

struct node *new_node(int code, ...)
{
	struct node *temp;
	int i;
	int n = 0;
	va_list vl;
	va_start(vl, code);
	while (1) {
		temp = va_arg(vl, struct node *);
		if (temp)
			n++;
		else
			break;
	}
	va_end(vl);
	struct node *g = (struct node *)myalloc(offsetof(struct node, children[n]), 8);
	g->code = code;
	va_start(vl, code);
	for (i = 0; i < n; i++) {
		temp = va_arg(vl, struct node *);
		g->children[n] = (intptr_t)temp;
	}
	va_end(vl);
	return g;
}

const char *token_to_str[4096] = {
	[CONST] = "const",
	[BOOL] = "bool",
	[FLOAT] = "float",
	[DOUBLE] = "double",
	[INT] = "int",
	[UINT] = "uint",
	[BREAK] = "break",
	[CONTINUE] = "continue",
	[DO] = "do",
	[ELSE] = "else",
	[FOR] = "for",
	[IF] = "if",
	[DISCARD] = "discard",
	[RETURN] = "return",
	[SWITCH] = "switch",
	[CASE] = "case",
	[DEFAULT] = "default",
	[SUBROUTINE] = "subroutine",
	[BVEC2] = "bvec2",
	[BVEC3] = "bvec3",
	[BVEC4] = "bvec4",
	[IVEC2] = "ivec2",
	[IVEC3] = "ivec3",
	[IVEC4] = "ivec4",
	[UVEC2] = "uvec2",
	[UVEC3] = "uvec3",
	[UVEC4] = "uvec4",
	[VEC2] = "vec2",
	[VEC3] = "vec3",
	[VEC4] = "vec4",
	[MAT2] = "mat2",
	[MAT3] = "mat3",
	[MAT4] = "mat4",
	[CENTROID] = "centroid",
	[IN] = "in",
	[OUT] = "out",
	[INOUT] = "inout",
	[UNIFORM] = "uniform",
	[PATCH] = "patch",
	[SAMPLE] = "sample",
	[BUFFER] = "buffer",
	[SHARED] = "shared",
	[COHERENT] = "coherent",
	[VOLATILE] = "volatile",
	[RESTRICT] = "restrict",
	[READONLY] = "readonly",
	[WRITEONLY] = "writeonly",
	[DVEC2] = "dvec2",
	[DVEC3] = "dvec3",
	[DVEC4] = "dvec4",
	[DMAT2] = "dmat2",
	[DMAT3] = "dmat3",
	[DMAT4] = "dmat4",
	[NOPERSPECTIVE] = "noperspective",
	[FLAT] = "flat",
	[SMOOTH] = "smooth",
	[LAYOUT] = "layout",
	[MAT2X2] = "mat2x2",
	[MAT2X3] = "mat2x3",
	[MAT2X4] = "mat2x4",
	[MAT3X2] = "mat3x2",
	[MAT3X3] = "mat3x3",
	[MAT3X4] = "mat3x4",
	[MAT4X2] = "mat4x2",
	[MAT4X3] = "mat4x3",
	[MAT4X4] = "mat4x4",
	[DMAT2X2] = "dmat2x2",
	[DMAT2X3] = "dmat2x3",
	[DMAT2X4] = "dmat2x4",
	[DMAT3X2] = "dmat3x2",
	[DMAT3X3] = "dmat3x3",
	[DMAT3X4] = "dmat3x4",
	[DMAT4X2] = "dmat4x2",
	[DMAT4X3] = "dmat4x3",
	[DMAT4X4] = "dmat4x4",
	[ATOMIC_UINT] = "atomic_uint",
	[SAMPLER1D] = "sampler1d",
	[SAMPLER2D] = "sampler2d",
	[SAMPLER3D] = "sampler3d",
	[SAMPLERCUBE] = "samplercube",
	[SAMPLER1DSHADOW] = "sampler1dshadow",
	[SAMPLER2DSHADOW] = "sampler2dshadow",
	[SAMPLERCUBESHADOW] = "samplercubeshadow",
	[SAMPLER1DARRAY] = "sampler1darray",
	[SAMPLER2DARRAY] = "sampler2darray",
	[SAMPLER1DARRAYSHADOW] = "sampler1darrayshadow",
	[SAMPLER2DARRAYSHADOW] = "sampler2darrayshadow",
	[ISAMPLER1D] = "isampler1d",
	[ISAMPLER2D] = "isampler2d",
	[ISAMPLER3D] = "isampler3d",
	[ISAMPLERCUBE] = "isamplercube",
	[ISAMPLER1DARRAY] = "isampler1darray",
	[ISAMPLER2DARRAY] = "isampler2darray",
	[USAMPLER1D] = "usampler1d",
	[USAMPLER2D] = "usampler2d",
	[USAMPLER3D] = "usampler3d",
	[USAMPLERCUBE] = "usamplercube",
	[USAMPLER1DARRAY] = "usampler1darray",
	[USAMPLER2DARRAY] = "usampler2darray",
	[SAMPLER2DRECT] = "sampler2drect",
	[SAMPLER2DRECTSHADOW] = "sampler2drectshadow",
	[ISAMPLER2DRECT] = "isampler2drect",
	[USAMPLER2DRECT] = "usampler2drect",
	[SAMPLERBUFFER] = "samplerbuffer",
	[ISAMPLERBUFFER] = "isamplerbuffer",
	[USAMPLERBUFFER] = "usamplerbuffer",
	[SAMPLERCUBEARRAY] = "samplercubearray",
	[SAMPLERCUBEARRAYSHADOW] = "samplercubearrayshadow",
	[ISAMPLERCUBEARRAY] = "isamplercubearray",
	[USAMPLERCUBEARRAY] = "usamplercubearray",
	[SAMPLER2DMS] = "sampler2dms",
	[ISAMPLER2DMS] = "isampler2dms",
	[USAMPLER2DMS] = "usampler2dms",
	[SAMPLER2DMSARRAY] = "sampler2dmsarray",
	[ISAMPLER2DMSARRAY] = "isampler2dmsarray",
	[USAMPLER2DMSARRAY] = "usampler2dmsarray",
	[IMAGE1D] = "image1d",
	[IIMAGE1D] = "iimage1d",
	[UIMAGE1D] = "uimage1d",
	[IMAGE2D] = "image2d",
	[IIMAGE2D] = "iimage2d",
	[UIMAGE2D] = "uimage2d",
	[IMAGE3D] = "image3d",
	[IIMAGE3D] = "iimage3d",
	[UIMAGE3D] = "uimage3d",
	[IMAGE2DRECT] = "image2drect",
	[IIMAGE2DRECT] = "iimage2drect",
	[UIMAGE2DRECT] = "uimage2drect",
	[IMAGECUBE] = "imagecube",
	[IIMAGECUBE] = "iimagecube",
	[UIMAGECUBE] = "uimagecube",
	[IMAGEBUFFER] = "imagebuffer",
	[IIMAGEBUFFER] = "iimagebuffer",
	[UIMAGEBUFFER] = "uimagebuffer",
	[IMAGE1DARRAY] = "image1darray",
	[IIMAGE1DARRAY] = "iimage1darray",
	[UIMAGE1DARRAY] = "uimage1darray",
	[IMAGE2DARRAY] = "image2darray",
	[IIMAGE2DARRAY] = "iimage2darray",
	[UIMAGE2DARRAY] = "uimage2darray",
	[IMAGECUBEARRAY] = "imagecubearray",
	[IIMAGECUBEARRAY] = "iimagecubearray",
	[UIMAGECUBEARRAY] = "uimagecubearray",
	[IMAGE2DMS] = "image2dms",
	[IIMAGE2DMS] = "iimage2dms",
	[UIMAGE2DMS] = "uimage2dms",
	[IMAGE2DMSARRAY] = "image2dmsarray",
	[IIMAGE2DMSARRAY] = "iimage2dmsarray",
	[UIMAGE2DMSARRAY] = "uimage2dmsarray",
	[STRUCT] = "struct",
	[VOID] = "void",
	[WHILE] = "while",
	[LEFT_OP] = "<<",
	[RIGHT_OP] = ">>",
	[INC_OP] = "++",
	[DEC_OP] = "--",
	[LE_OP] = "<=",
	[GE_OP] = ">=",
	[EQ_OP] = "==",
	[NE_OP] = "!=",
	[AND_OP] = "&&",
	[OR_OP] = "||",
	[XOR_OP] = "^^",
	[MUL_ASSIGN] = "*=",
	[DIV_ASSIGN] = "/=",
	[ADD_ASSIGN] = "+=",
	[MOD_ASSIGN] = "%=",
	[LEFT_ASSIGN] = "<<=",
	[RIGHT_ASSIGN] = ">>=",
	[AND_ASSIGN] = "&=",
	[XOR_ASSIGN] = "^=",
	[OR_ASSIGN] = "|=",
	[SUB_ASSIGN] = "-=",
	[LEFT_PAREN] = "(",
	[RIGHT_PAREN] = ")",
	[LEFT_BRACKET] = "[",
	[RIGHT_BRACKET] = "]",
	[LEFT_BRACE] = "{",
	[RIGHT_BRACE] = "}",
	[DOT] = ".",
	[COMMA] = ",",
	[COLON] = ":",
	[EQUAL] = "=",
	[SEMICOLON] = ";",
	[BANG] = "!",
	[DASH] = "-",
	[TILDE] = "~",
	[PLUS] = "+",
	[STAR] = "*",
	[SLASH] = "/",
	[PERCENT] = "%",
	[LEFT_ANGLE] = "<",
	[RIGHT_ANGLE] = ">",
	[VERTICAL_BAR] = "|",
	[CARET] = "^",
	[AMPERSAND] = "&",
	[QUESTION] = "?",
	[INVARIANT] = "invariant",
	[PRECISE] = "precise",
	[HIGHP] = "highp",
	[MEDIUMP] = "mediump",
	[LOWP] = "lowp",
	[PRECISION] = "precision",
	[AT] = "@"
};

%}

%defines

%define api.prefix {glsl}

%define api.value.type union


%type <struct node *> translation_unit 

%type <struct node *> external_declaration 
%type <struct node *> function_definition
%type <struct node *> compound_statement_no_new_scope
%type <struct node *> statement
%type <struct node *> statement_list
%type <struct node *> compound_statement 
%type <struct node *> simple_statement
%type <struct node *> declaration_statement
%type <struct node *> declaration_tag
%type <struct node *> declaration_tag_list
%type <struct node *> end_declaration 
%type <struct node *> declaration 
%type <struct node *> identifier_list
%type <struct node *> init_declarator_list 
%type <struct node *> single_declaration 
%type <struct node *> initializer 
%type <struct node *> initializer_list

%type <struct node *> expression_statement
%type <struct node *> selection_statement
%type <struct node *> switch_statement
%type <struct node *> switch_statement_list
%type <struct node *> case_label
%type <struct node *> iteration_statement
%type <struct node *> statement_no_new_scope
%type <struct node *> for_init_statement
%type <struct node *> conditionopt

%type <struct node *> condition
%type <struct node *> for_rest_statement 
%type <struct node *> jump_statement 
%type <struct node *> function_prototype 
%type <struct node *> function_declarator
%type <struct node *> parameter_declaration
%type <struct node *> parameter_declarator
%type <struct node *> function_header
%type <struct node *> function_parameter_list
%type <struct node *> fully_specified_type
%type <struct node *> parameter_type_specifier

%type <struct node *> primary_expression
%type <struct node *> expression
%type <struct node *> assignment_expression
%type <struct node *> conditional_expression
%type <struct node *> logical_or_expression 
%type <struct node *> logical_xor_expression 
%type <struct node *> logical_and_expression 
%type <struct node *> exclusive_or_expression 
%type <struct node *> constant_expression 
%type <struct node *> and_expression 
%type <struct node *> equality_expression 
%type <struct node *> relational_expression 
%type <struct node *> shift_expression 
%type <struct node *> additive_expression 
%type <struct node *> multiplicative_expression 
%type <struct node *> unary_expression 
%type <struct node *> postfix_expression 
%type <struct node *> integer_expression 
%type <struct node *> inclusive_or_expression 

%type <struct node *> function_call
%type <struct node *> function_call_or_method
%type <struct node *> function_call_generic
%type <struct node *> function_call_header_no_parameters
%type <struct node *> function_call_header_with_parameters
%type <struct node *> function_call_header
%type <struct node *> function_identifier

%type <struct node *> type_specifier
%type <struct node *> type_specifier_nonarray
%type <struct node *> struct_specifier
%type <struct node *> array_specifier
%type <struct node *> array_specifier_list

%type <struct node *> struct_declaration_list
%type <struct node *> struct_declaration
%type <struct node *> struct_declarator_list
%type <struct node *> struct_declarator
%type <struct node *> type_qualifier 
%type <struct node *> single_type_qualifier 
%type <struct node *> layout_qualifier 
%type <struct node *> layout_qualifier_id_list 
%type <struct node *> layout_qualifier_id

%type <struct node *> precision_qualifier
%type <struct node *> invariant_qualifier
%type <struct node *> precise_qualifier
%type <struct node *> storage_qualifier
%type <struct node *> interpolation_qualifier
%type <struct node *> type_name_list 

%type <const char *> variable_identifier 
%type <struct node*> decl_identifier 
%type <struct node *> block_identifier 
%type <const char *> struct_name 
%type <const char *> type_name 
%type <const char *> param_name 
%type <const char *> function_name 
%type <const char *> field_selection 
%type <const char *> declaration_tag_identifier 
%type <const char *> type_specifier_identifier 

%type <int> assignment_operator
%type <int> unary_operator

%token CONST
%token BOOL
%token FLOAT
%token DOUBLE
%token INT
%token UINT
%token BREAK
%token CONTINUE
%token DO
%token ELSE
%token FOR
%token IF
%token DISCARD
%token RETURN
%token SWITCH
%token CASE
%token DEFAULT
%token SUBROUTINE
%token BVEC2
%token BVEC3
%token BVEC4
%token IVEC2
%token IVEC3
%token IVEC4
%token UVEC2
%token UVEC3
%token UVEC4
%token VEC2
%token VEC3
%token VEC4
%token MAT2
%token MAT3
%token MAT4
%token CENTROID
%token IN
%token OUT
%token INOUT
%token UNIFORM
%token PATCH
%token SAMPLE
%token BUFFER
%token SHARED
%token COHERENT
%token VOLATILE
%token RESTRICT
%token READONLY
%token WRITEONLY
%token DVEC2
%token DVEC3
%token DVEC4
%token DMAT2
%token DMAT3
%token DMAT4
%token NOPERSPECTIVE
%token FLAT
%token SMOOTH
%token LAYOUT
%token MAT2X2
%token MAT2X3
%token MAT2X4
%token MAT3X2
%token MAT3X3
%token MAT3X4
%token MAT4X2
%token MAT4X3
%token MAT4X4
%token DMAT2X2
%token DMAT2X3
%token DMAT2X4
%token DMAT3X2
%token DMAT3X3
%token DMAT3X4
%token DMAT4X2
%token DMAT4X3
%token DMAT4X4
%token ATOMIC_UINT
%token SAMPLER1D
%token SAMPLER2D
%token SAMPLER3D
%token SAMPLERCUBE
%token SAMPLER1DSHADOW
%token SAMPLER2DSHADOW
%token SAMPLERCUBESHADOW
%token SAMPLER1DARRAY
%token SAMPLER2DARRAY
%token SAMPLER1DARRAYSHADOW
%token SAMPLER2DARRAYSHADOW
%token ISAMPLER1D
%token ISAMPLER2D
%token ISAMPLER3D
%token ISAMPLERCUBE
%token ISAMPLER1DARRAY
%token ISAMPLER2DARRAY
%token USAMPLER1D
%token USAMPLER2D
%token USAMPLER3D
%token USAMPLERCUBE
%token USAMPLER1DARRAY
%token USAMPLER2DARRAY
%token SAMPLER2DRECT
%token SAMPLER2DRECTSHADOW
%token ISAMPLER2DRECT
%token USAMPLER2DRECT
%token SAMPLERBUFFER
%token ISAMPLERBUFFER
%token USAMPLERBUFFER
%token SAMPLERCUBEARRAY
%token SAMPLERCUBEARRAYSHADOW
%token ISAMPLERCUBEARRAY
%token USAMPLERCUBEARRAY
%token SAMPLER2DMS
%token ISAMPLER2DMS
%token USAMPLER2DMS
%token SAMPLER2DMSARRAY
%token ISAMPLER2DMSARRAY
%token USAMPLER2DMSARRAY
%token IMAGE1D
%token IIMAGE1D
%token UIMAGE1D
%token IMAGE2D
%token IIMAGE2D
%token UIMAGE2D
%token IMAGE3D
%token IIMAGE3D
%token UIMAGE3D
%token IMAGE2DRECT
%token IIMAGE2DRECT
%token UIMAGE2DRECT
%token IMAGECUBE
%token IIMAGECUBE
%token UIMAGECUBE
%token IMAGEBUFFER
%token IIMAGEBUFFER
%token UIMAGEBUFFER
%token IMAGE1DARRAY
%token IIMAGE1DARRAY
%token UIMAGE1DARRAY
%token IMAGE2DARRAY
%token IIMAGE2DARRAY
%token UIMAGE2DARRAY
%token IMAGECUBEARRAY
%token IIMAGECUBEARRAY
%token UIMAGECUBEARRAY
%token IMAGE2DMS
%token IIMAGE2DMS
%token UIMAGE2DMS
%token IMAGE2DMSARRAY
%token IIMAGE2DMSARRAY
%token UIMAGE2DMSARRAY
%token STRUCT
%token VOID
%token WHILE
%token <char *> IDENTIFIER
%token <float> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <int> INTCONSTANT
%token <unsigned int> UINTCONSTANT
%token <bool> BOOLCONSTANT
%token LEFT_OP
%token RIGHT_OP
%token INC_OP
%token DEC_OP
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token AND_OP
%token OR_OP
%token XOR_OP
%token MUL_ASSIGN
%token DIV_ASSIGN
%token ADD_ASSIGN
%token MOD_ASSIGN
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token AND_ASSIGN
%token XOR_ASSIGN
%token OR_ASSIGN
%token SUB_ASSIGN
%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_BRACE
%token RIGHT_BRACE
%token DOT
%token COMMA
%token COLON
%token EQUAL
%token SEMICOLON
%token BANG
%token DASH
%token TILDE
%token PLUS
%token STAR
%token SLASH
%token PERCENT
%token LEFT_ANGLE
%token RIGHT_ANGLE
%token VERTICAL_BAR
%token CARET
%token AMPERSAND
%token QUESTION
%token INVARIANT
%token PRECISE
%token HIGHP
%token MEDIUMP
%token LOWP
%token PRECISION
%token AT

%token POST_INC_OP
%token POST_DEC_OP
%token ARRAY_REF_OP
%token FUNCTION_CALL 

%token TYPE_NAME_LIST
%token TYPE_SPECIFIER 
%token POSTFIX_EXPRESSION 
%token TYPE_QUALIFIER_LIST
%token STRUCT_DECLARATION
%token STRUCT_DECLARATOR
%token STRUCT_SPECIFIER

%token FUNCTION_DEFINITION
%token DECLARATION 
%token STATEMENT_LIST 
%token TRANSLATION_UNIT
%token DECLARATION_TAG 
%token DECLARATION_TAG_LIST 
%token END_DECLARATION

%token PRECISION_DECLARATION 
%token BLOCK_DECLARATION 
%token BLOCK_IDENTIFIER
%token TYPE_QUALIFIER_DECLARATION 

%token IDENTIFIER_LIST
%token DECL_IDENTIFIER 
%token INIT_DECLARATOR_LIST 
%token FULLY_SPECIFIED_TYPE 
%token SINGLE_DECLARATION 
%token INITIALIZER_LIST 

%token EXPRESSION_STATEMENT 
%token SELECTION_STATEMENT 
%token SWITCH_STATEMENT 
%token FOR_REST_STATEMENT 
%token WHILE_STATEMENT
%token DO_STATEMENT
%token FOR_STATEMENT

%token CASE_LABEL 
%token CONDITION_OPT 

%token ASSIGNMENT_CONDITION
%token EXPRESSION_CONDITION


%token FUNCTION_PROTOTYPE
%token FUNCTION_HEADER
%token FUNCTION_DECLARATION
%token FUNCTION_PARAMETER_LIST

%token PARAMETER_DECLARATION 
%token PARAMETER_DECLARATOR 

%token UNINITIALIZED_DECLARATION 

%token ARRAY_SPECIFIER
%token ARRAY_SPECIFIER_LIST 

%token NUM_TOKEN
%%

translation_unit	: external_declaration { $$ = $1; }
			| translation_unit external_declaration { $$ = new_node(TRANSLATION_UNIT, $1, $2, NULL); }
			;

block_identifier	: IDENTIFIER { $$ = new_node(BLOCK_IDENTIFIER, NULL); $$->data.str = mystrdup($1); }
			;

decl_identifier		: IDENTIFIER { $$ = new_node(DECL_IDENTIFIER, NULL); $$->data.str = mystrdup($1); }
			;

struct_name		: IDENTIFIER { $$ = mystrdup($1); }
			;

type_name		: IDENTIFIER { $$ = mystrdup($1); }
			;

param_name		: IDENTIFIER { $$ = mystrdup($1); }
			;

function_name		: IDENTIFIER { $$ = mystrdup($1); }
			;

field_selection		: IDENTIFIER { $$ = mystrdup($1); }
			;

variable_identifier	: IDENTIFIER { $$ = mystrdup($1); }

declaration_tag_identifier : IDENTIFIER { $$ = mystrdup($1); }
			;

type_specifier_identifier : IDENTIFIER { $$ = mystrdup($1); }
			;

external_declaration	: function_definition { $$ = $1; }
			| declaration { $$ = $1; }
			;

function_definition	: function_prototype compound_statement_no_new_scope { $$ = new_node(FUNCTION_DEFINITION, $1, NULL); }
			| function_prototype { $$ = new_node(FUNCTION_DEFINITION,$1, NULL); }
			;

compound_statement_no_new_scope : LEFT_BRACE RIGHT_BRACE { $$ = new_node(STATEMENT_LIST, NULL); }
			| LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2; }
			;

statement		: compound_statement { $$ = $1; }
			| simple_statement { $$ = $1; }
			;

statement_list		: statement { $$ = $1; }
			| statement_list statement { $$ = new_node(STATEMENT_LIST, $1, $2, NULL); }
			;

compound_statement	: LEFT_BRACE RIGHT_BRACE { $$ = new_node(STATEMENT_LIST, NULL); }
			| LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2; }
			;

simple_statement	: declaration_statement { $$ = $1; }
			| expression_statement { $$ = $1; }
			| selection_statement { $$ = $1; }
			| switch_statement { $$ = $1; }
			| case_label { $$= $1; }
			| iteration_statement { $$ = $1; }
			| jump_statement { $$ = $1; }
			;

declaration_statement	: declaration { $$ = $1; }
			;

declaration_tag		: declaration_tag_identifier { $$ = new_node(DECLARATION_TAG, NULL); $$->data.str = $1; } 
			| declaration_tag_identifier EQUAL primary_expression { $$ = new_node(DECLARATION_TAG, $3, NULL); $$->data.str = $1; }
			;

declaration_tag_list	: declaration_tag { $$ = $1; }
			| declaration_tag_list COMMA declaration_tag { $$ = new_node(DECLARATION_TAG_LIST, $1, $3, NULL); }
			;

end_declaration		: AT declaration_tag_list AT SEMICOLON { $$ = new_node(END_DECLARATION, $2, NULL); }
			| SEMICOLON { $$ = new_node(END_DECLARATION, NULL); }
			;

declaration		: function_prototype SEMICOLON { $$ = $1; }
			| init_declarator_list end_declaration { $$ = $1; }
			| PRECISION precision_qualifier type_specifier SEMICOLON { $$ = new_node(PRECISION_DECLARATION, $2, $3, NULL); }
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE SEMICOLON { $$ = new_node(BLOCK_DECLARATION, $1, $2, $4, NULL);}
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE decl_identifier SEMICOLON { $$ = new_node(BLOCK_DECLARATION, $1, $2, $4, $6, NULL);}
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE decl_identifier array_specifier_list SEMICOLON { $$ = new_node(BLOCK_DECLARATION, $1, $2, $4, $6, $7, NULL);}
			| type_qualifier SEMICOLON { $$ = new_node(UNINITIALIZED_DECLARATION, $1, NULL); }
			| type_qualifier type_name SEMICOLON { $$ = new_node(UNINITIALIZED_DECLARATION, $1, NULL); $$->data.str = $2; }
			| type_qualifier type_name identifier_list SEMICOLON { $$ = new_node(UNINITIALIZED_DECLARATION, $1, $3, NULL); $$->data.str = $2; }
			;

identifier_list		: COMMA decl_identifier { $$ = $2; }
			| identifier_list COMMA decl_identifier { $$ = new_node(IDENTIFIER_LIST, $1, $3, NULL); } 
			;

init_declarator_list	: single_declaration { $$ = $1; }
			| init_declarator_list COMMA decl_identifier { $$ = new_node(INIT_DECLARATOR_LIST, $1, $3, NULL); }
			| init_declarator_list COMMA decl_identifier array_specifier_list { $$ = new_node(INIT_DECLARATOR_LIST, $1, $3, $4, NULL); }
			| init_declarator_list COMMA decl_identifier array_specifier_list EQUAL initializer { $$ = new_node(INIT_DECLARATOR_LIST, $1, $3, $4, $6, NULL); }
			| init_declarator_list COMMA decl_identifier EQUAL initializer { $$ = new_node(INIT_DECLARATOR_LIST, $1, $3, new_node(ARRAY_SPECIFIER_LIST, NULL), $5, NULL); }
			;

single_declaration	: fully_specified_type { $$ = new_node(SINGLE_DECLARATION, $1, NULL); }
			| fully_specified_type decl_identifier { $$ = new_node(SINGLE_DECLARATION, $1, $2, NULL); }
			| fully_specified_type decl_identifier array_specifier_list { $$ = new_node(SINGLE_DECLARATION, $1, $2, $3, NULL); }
			| fully_specified_type decl_identifier array_specifier_list EQUAL initializer { $$ = new_node(SINGLE_DECLARATION, $1, $2, $3, $5, NULL); }
			| fully_specified_type decl_identifier EQUAL initializer { $$ = new_node(SINGLE_DECLARATION, $1, $2,  new_node(ARRAY_SPECIFIER_LIST, NULL), $4, NULL); }
			;

initializer		: assignment_expression { $$ = $1; }
			| LEFT_BRACE initializer_list RIGHT_BRACE { $$ = $2; }
			| LEFT_BRACE initializer_list COMMA RIGHT_BRACE { $$ = $2; }
			;

initializer_list	: initializer { $$ = $1; }
			| initializer_list COMMA initializer { $$ = new_node(INITIALIZER_LIST, $1, $3, NULL); }
			;

expression_statement	: SEMICOLON { $$ = new_node(EXPRESSION_STATEMENT, NULL); }
			| expression SEMICOLON { $$ = new_node(EXPRESSION_STATEMENT, $1, NULL); }
			;

selection_statement	: IF LEFT_PAREN expression RIGHT_PAREN statement { $$ = new_node(SELECTION_STATEMENT, $3, $5, NULL); }
			| IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement { $$ = new_node(SELECTION_STATEMENT, $3, $5, $7, NULL); }
			;

switch_statement	: SWITCH LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE switch_statement_list RIGHT_BRACE { $$ = new_node(SWITCH_STATEMENT, $3, $6, NULL); }
			;

switch_statement_list	: { $$ = new_node(STATEMENT_LIST, NULL); }
			| statement_list { $$ = $1; }
			;

case_label		: CASE expression COLON { $$ = new_node(CASE_LABEL, $2, NULL); }
			| DEFAULT COLON { $$ = new_node(CASE_LABEL, NULL); }
			;

iteration_statement	: WHILE LEFT_PAREN condition RIGHT_PAREN statement_no_new_scope { $$ = new_node(WHILE_STATEMENT, $3, $5, NULL); }
			| DO statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON { $$ = new_node(DO_STATEMENT, $2, $5, NULL); }
			| FOR LEFT_PAREN for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope { $$ = new_node(FOR_STATEMENT, $3, $4, $6, NULL); }
			;

statement_no_new_scope	: compound_statement_no_new_scope { $$ = $1; }
			| simple_statement { $$ = $1; }
			;

for_init_statement	: expression_statement { $$ = $1; }
			| declaration_statement { $$ = $1; }
			;

conditionopt		: condition { $$ = new_node(CONDITION_OPT, $1, NULL); }
			| { $$ = new_node(CONDITION_OPT, NULL); }
			;

condition		: expression { $$ = new_node(EXPRESSION_CONDITION, $1, NULL); }
			| fully_specified_type variable_identifier EQUAL initializer { $$ = new_node(ASSIGNMENT_CONDITION, $1, $2, $4, NULL); }
			;

for_rest_statement	: conditionopt SEMICOLON { $$ = new_node(FOR_REST_STATEMENT, $1, NULL); }
			| conditionopt SEMICOLON expression { $$ = new_node(FOR_REST_STATEMENT, $1, $3, NULL); }
			;

jump_statement		: CONTINUE SEMICOLON { $$ = new_node(CONTINUE, NULL); }
			| BREAK SEMICOLON { $$ = new_node(BREAK, NULL); }
			| RETURN SEMICOLON { $$ = new_node(RETURN, NULL); }
			| RETURN expression SEMICOLON { $$ = new_node(RETURN, $2, NULL); }
			| DISCARD SEMICOLON { $$ = new_node(DISCARD, NULL); }
			;

function_prototype	: function_declarator RIGHT_PAREN { $$ = new_node(FUNCTION_PROTOTYPE, $1, NULL); }
			;

function_declarator	: function_header { $$ = new_node(FUNCTION_DECLARATION, $1, NULL); }
			| function_header function_parameter_list { $$ = new_node(FUNCTION_DECLARATION, $1, $2, NULL); }
			;

function_parameter_list : parameter_declaration { $$ = $1; }
			| function_parameter_list COMMA parameter_declaration { $$ = new_node(FUNCTION_PARAMETER_LIST, $1, $3, NULL); } 
			;

parameter_declaration	: type_qualifier parameter_declarator { $$ = new_node(PARAMETER_DECLARATION, $1, $2, NULL); }
			| parameter_declarator { $$ = new_node(PARAMETER_DECLARATION, new_node(TYPE_QUALIFIER_LIST, NULL), $1, NULL); }
			| type_qualifier parameter_type_specifier { $$ = new_node(PARAMETER_DECLARATION, $1, $2, NULL); }
			| parameter_type_specifier { $$ = new_node(PARAMETER_DECLARATION, new_node(TYPE_QUALIFIER_LIST, NULL), $1, NULL); }
			;

parameter_declarator	: type_specifier param_name { $$ = new_node(PARAMETER_DECLARATOR, $1, NULL); $$->data.str = $2; }
			| type_specifier param_name array_specifier_list { $$ = new_node(PARAMETER_DECLARATOR, $1, $3, NULL); $$->data.str = $2; }
			;

function_header		: fully_specified_type function_name LEFT_PAREN { $$ = new_node(FUNCTION_HEADER, $1, NULL); $$->data.str = $2; }
			;

fully_specified_type	: type_specifier { $$ = new_node(PARAMETER_DECLARATION, new_node(TYPE_QUALIFIER_LIST, NULL), $1, NULL); }
			| type_qualifier type_specifier { $$ = new_node(PARAMETER_DECLARATION, $1, $2, NULL); }
			;

parameter_type_specifier : type_specifier { $$ = new_node(PARAMETER_DECLARATOR, $1, NULL); $$->data.str = NULL; }
			;

type_specifier		: type_specifier_nonarray { $$ = new_node(TYPE_SPECIFIER, $1, NULL); }
			| type_specifier_nonarray array_specifier { $$ = new_node(TYPE_SPECIFIER, $1, $2, NULL); }
			;

array_specifier_list	: array_specifier { $$ = $1; }
		     	| array_specifier_list array_specifier { $$ = new_node(ARRAY_SPECIFIER_LIST, $1, $2, NULL); }
			;

array_specifier		: LEFT_BRACKET RIGHT_BRACKET { $$ = new_node(ARRAY_SPECIFIER, NULL); }
			| LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = new_node(ARRAY_SPECIFIER, $2, NULL); }
			;

type_specifier_nonarray : VOID { $$ = new_node(VOID, NULL); }
			| FLOAT { $$ = new_node(FLOAT, NULL); }
			| DOUBLE { $$ = new_node(DOUBLE, NULL); }
			| INT { $$ = new_node(INT, NULL); }
			| UINT { $$ = new_node(UINT, NULL); }
			| BOOL { $$ = new_node(BOOL, NULL); }
			| VEC2 { $$ = new_node(VEC2, NULL); }
			| VEC3 { $$ = new_node(VEC3, NULL); }
			| VEC4 { $$ = new_node(VEC4, NULL); }
			| DVEC2 { $$ = new_node(DVEC2, NULL); }
			| DVEC3 { $$ = new_node(DVEC3, NULL); }
			| DVEC4 { $$ = new_node(DVEC4, NULL); }
			| BVEC2 { $$ = new_node(BVEC2, NULL); }
			| BVEC3 { $$ = new_node(BVEC3, NULL); }
			| BVEC4 { $$ = new_node(BVEC4, NULL); }
			| IVEC2 { $$ = new_node(IVEC2, NULL); }
			| IVEC3 { $$ = new_node(IVEC3, NULL); }
			| IVEC4 { $$ = new_node(IVEC4, NULL); }
			| UVEC2 { $$ = new_node(UVEC2, NULL); }
			| UVEC3 { $$ = new_node(UVEC3, NULL); }
			| UVEC4 { $$ = new_node(UVEC4, NULL); }
			| MAT2 { $$ = new_node(MAT2, NULL); }
			| MAT3 { $$ = new_node(MAT3, NULL); }
			| MAT4 { $$ = new_node(MAT4, NULL); }
			| MAT2X2 { $$ = new_node(MAT2X2, NULL); }
			| MAT2X3 { $$ = new_node(MAT2X3, NULL); }
			| MAT2X4 { $$ = new_node(MAT2X4, NULL); }
			| MAT3X2 { $$ = new_node(MAT3X2, NULL); }
			| MAT3X3 { $$ = new_node(MAT3X3, NULL); }
			| MAT3X4 { $$ = new_node(MAT3X4, NULL); }
			| MAT4X2 { $$ = new_node(MAT4X2, NULL); }
			| MAT4X3 { $$ = new_node(MAT4X3, NULL); }
			| MAT4X4 { $$ = new_node(MAT4X4, NULL); }
			| DMAT2 { $$ = new_node(DMAT2, NULL); }
			| DMAT3 { $$ = new_node(DMAT3, NULL); }
			| DMAT4 { $$ = new_node(DMAT4, NULL); }
			| DMAT2X2 { $$ = new_node(DMAT2X2, NULL); }
			| DMAT2X3 { $$ = new_node(DMAT2X3, NULL); }
			| DMAT2X4 { $$ = new_node(DMAT2X4, NULL); }
			| DMAT3X2 { $$ = new_node(DMAT3X2, NULL); }
			| DMAT3X3 { $$ = new_node(DMAT3X3, NULL); }
			| DMAT3X4 { $$ = new_node(DMAT3X4, NULL); }
			| DMAT4X2 { $$ = new_node(DMAT4X2, NULL); }
			| DMAT4X3 { $$ = new_node(DMAT4X3, NULL); }
			| DMAT4X4 { $$ = new_node(DMAT4X4, NULL); }
			| ATOMIC_UINT { $$ = new_node(UINT, NULL); }
			| SAMPLER1D { $$ = new_node(SAMPLER1D, NULL); }
			| SAMPLER2D { $$ = new_node(SAMPLER2D, NULL); }
			| SAMPLER3D { $$ = new_node(SAMPLER3D, NULL); }
			| SAMPLERCUBE { $$ = new_node(SAMPLERCUBE, NULL); }
			| SAMPLER1DSHADOW { $$ = new_node(SAMPLER1DSHADOW, NULL); }
			| SAMPLER2DSHADOW { $$ = new_node(SAMPLER2DSHADOW, NULL); }
			| SAMPLERCUBESHADOW { $$ = new_node(SAMPLERCUBESHADOW, NULL); }
			| SAMPLER1DARRAY { $$ = new_node(SAMPLER1DARRAY, NULL); }
			| SAMPLER2DARRAY { $$ = new_node(SAMPLER2DARRAY, NULL); }
			| SAMPLER1DARRAYSHADOW { $$ = new_node(SAMPLER1DARRAYSHADOW, NULL); }
			| SAMPLER2DARRAYSHADOW { $$ = new_node(SAMPLER2DARRAYSHADOW, NULL); }
			| SAMPLERCUBEARRAY { $$ = new_node(SAMPLERCUBEARRAY, NULL); }
			| SAMPLERCUBEARRAYSHADOW { $$ = new_node(SAMPLERCUBEARRAYSHADOW, NULL); }
			| ISAMPLER1D { $$ = new_node(ISAMPLER1D, NULL); }
			| ISAMPLER2D { $$ = new_node(ISAMPLER2D, NULL); }
			| ISAMPLER3D { $$ = new_node(ISAMPLER3D, NULL); }
			| ISAMPLERCUBE { $$ = new_node(ISAMPLERCUBE, NULL); }
			| ISAMPLER1DARRAY { $$ = new_node(ISAMPLER1DARRAY, NULL); }
			| ISAMPLER2DARRAY { $$ = new_node(ISAMPLER2DARRAY, NULL); }
			| ISAMPLERCUBEARRAY { $$ = new_node(ISAMPLERCUBEARRAY, NULL); }
			| USAMPLER1D { $$ = new_node(USAMPLER1D, NULL); }
			| USAMPLER2D { $$ = new_node(USAMPLER2D, NULL); }
			| USAMPLER3D { $$ = new_node(USAMPLER3D, NULL); }
			| USAMPLERCUBE { $$ = new_node(USAMPLERCUBE, NULL); }
			| USAMPLER1DARRAY { $$ = new_node(USAMPLER1DARRAY, NULL); }
			| USAMPLER2DARRAY { $$ = new_node(USAMPLER2DARRAY, NULL); }
			| USAMPLERCUBEARRAY { $$ = new_node(USAMPLERCUBEARRAY, NULL); }
			| SAMPLER2DRECT { $$ = new_node(SAMPLER2DRECT, NULL); }
			| SAMPLER2DRECTSHADOW { $$ = new_node(SAMPLER2DRECTSHADOW, NULL); }
			| ISAMPLER2DRECT { $$ = new_node(ISAMPLER2DRECT, NULL); }
			| USAMPLER2DRECT { $$ = new_node(USAMPLER2DRECT, NULL); }
			| SAMPLERBUFFER { $$ = new_node(SAMPLERBUFFER, NULL); }
			| ISAMPLERBUFFER { $$ = new_node(ISAMPLERBUFFER, NULL); }
			| USAMPLERBUFFER { $$ = new_node(USAMPLERBUFFER, NULL); }
			| SAMPLER2DMS { $$ = new_node(SAMPLER2DMS, NULL); }
			| ISAMPLER2DMS { $$ = new_node(ISAMPLER2DMS, NULL); }
			| USAMPLER2DMS { $$ = new_node(USAMPLER2DMS, NULL); }
			| SAMPLER2DMSARRAY { $$ = new_node(SAMPLER2DMSARRAY, NULL); }
			| ISAMPLER2DMSARRAY { $$ = new_node(ISAMPLER2DMSARRAY, NULL); }
			| USAMPLER2DMSARRAY { $$ = new_node(USAMPLER2DMSARRAY, NULL); }
			| IMAGE1D { $$ = new_node(IMAGE1D, NULL); }
			| IIMAGE1D { $$ = new_node(IIMAGE1D, NULL); }
			| UIMAGE1D { $$ = new_node(UIMAGE1D, NULL); }
			| IMAGE2D { $$ = new_node(IMAGE2D, NULL); }
			| IIMAGE2D { $$ = new_node(IIMAGE2D, NULL); }
			| UIMAGE2D { $$ = new_node(UIMAGE2D, NULL); }
			| IMAGE3D { $$ = new_node(IMAGE3D, NULL); }
			| IIMAGE3D { $$ = new_node(IIMAGE3D, NULL); }
			| UIMAGE3D { $$ = new_node(UIMAGE3D, NULL); }
			| IMAGE2DRECT { $$ = new_node(IMAGE2DRECT, NULL); }
			| IIMAGE2DRECT { $$ = new_node(IIMAGE2DRECT, NULL); }
			| UIMAGE2DRECT { $$ = new_node(UIMAGE2DRECT, NULL); }
			| IMAGECUBE { $$ = new_node(IMAGECUBE, NULL); }
			| IIMAGECUBE { $$ = new_node(IIMAGECUBE, NULL); }
			| UIMAGECUBE { $$ = new_node(UIMAGECUBE, NULL); }
			| IMAGEBUFFER { $$ = new_node(IMAGEBUFFER, NULL); }
			| IIMAGEBUFFER { $$ = new_node(IIMAGEBUFFER, NULL); }
			| UIMAGEBUFFER { $$ = new_node(UIMAGEBUFFER, NULL); }
			| IMAGE1DARRAY { $$ = new_node(IMAGE1DARRAY, NULL); }
			| IIMAGE1DARRAY { $$ = new_node(IIMAGE1DARRAY, NULL); }
			| UIMAGE1DARRAY { $$ = new_node(UIMAGE1DARRAY, NULL); }
			| IMAGE2DARRAY { $$ = new_node(IMAGE2DARRAY, NULL); }
			| IIMAGE2DARRAY { $$ = new_node(IIMAGE2DARRAY, NULL); }
			| UIMAGE2DARRAY { $$ = new_node(UIMAGE2DARRAY, NULL); }
			| IMAGECUBEARRAY { $$ = new_node(IMAGECUBEARRAY, NULL); }
			| IIMAGECUBEARRAY { $$ = new_node(IIMAGECUBEARRAY, NULL); }
			| UIMAGECUBEARRAY { $$ = new_node(UIMAGECUBEARRAY, NULL); }
			| IMAGE2DMS { $$ = new_node(IMAGE2DMS, NULL); }
			| IIMAGE2DMS { $$ = new_node(IIMAGE2DMS, NULL); }
			| UIMAGE2DMS { $$ = new_node(UIMAGE2DMS, NULL); }
			| IMAGE2DMSARRAY { $$ = new_node(IMAGE2DMSARRAY, NULL); }
			| IIMAGE2DMSARRAY { $$ = new_node(IIMAGE2DMSARRAY, NULL); }
			| UIMAGE2DMSARRAY { $$ = new_node(UIMAGE2DMSARRAY, NULL); }
			| struct_specifier { $$ = $1; }
			| type_specifier_identifier { $$ = new_node(IDENTIFIER, NULL); $$->data.str = $1; }
			;

struct_specifier	: STRUCT struct_name LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new_node(STRUCT_SPECIFIER, $4, NULL); $$->data.str = $2; } 
			| STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new_node(STRUCT_SPECIFIER, $3, NULL); $$->data.str = NULL; }
			;

struct_declaration_list : struct_declaration { $$ = $1; }
			| struct_declaration_list struct_declaration { $$ = new_node(SEMICOLON, $1, $2, NULL); }
			;

struct_declaration	: type_specifier struct_declarator_list SEMICOLON { $$ = new_node(STRUCT_DECLARATION, new_node(TYPE_QUALIFIER_LIST, NULL), $1, $2, NULL); } 
			| type_qualifier type_specifier struct_declarator_list SEMICOLON { $$ = new_node(STRUCT_DECLARATION, $1, $2, $3, NULL); }
			;

struct_declarator_list	: struct_declarator { $$ = $1; }
			| struct_declarator_list COMMA struct_declarator { $$ = new_node(COMMA, $1, $3, NULL); }
			;

struct_declarator	: decl_identifier { $$ = new_node(STRUCT_DECLARATOR, $1, NULL); }
			| decl_identifier array_specifier { $$ = new_node(STRUCT_DECLARATOR, $1, $2, NULL); }
			;

type_qualifier		: single_type_qualifier { $$ = new_node(TYPE_QUALIFIER_LIST, $1, NULL); }
			| type_qualifier single_type_qualifier { $$ = new_node(TYPE_QUALIFIER_LIST, $1, $2, NULL); }
			;

single_type_qualifier	: storage_qualifier { $$ = $1; }
			| layout_qualifier { $$ = $1; }
			| precision_qualifier { $$ = $1; }
			| interpolation_qualifier { $$ = $1; }
			| invariant_qualifier { $$ = $1; }
			| precise_qualifier { $$ = $1; }
			;

layout_qualifier	: LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN { $$ = new_node(LAYOUT, $3, NULL); }
			;

layout_qualifier_id_list: layout_qualifier_id { $$ = $1; }
			| layout_qualifier_id_list COMMA layout_qualifier_id { $$ = new_node(COMMA, $1, $3, NULL); }
			;

layout_qualifier_id	: IDENTIFIER { $$ = new_node(IDENTIFIER, NULL); $$->data.str = $1;}
			| IDENTIFIER EQUAL constant_expression { $$ = new_node(IDENTIFIER, $3, NULL); $$->data.str = $1; }
			| SHARED { $$ = new_node(SHARED, NULL); }
			;

precision_qualifier	: HIGHP { $$ = new_node(HIGHP, NULL); }
			| MEDIUMP { $$ = new_node(MEDIUMP, NULL); }
			| LOWP { $$ = new_node(LOWP, NULL); }
			;

interpolation_qualifier : SMOOTH { $$ = new_node(SMOOTH, NULL); }
			| FLAT { $$ = new_node(FLAT, NULL); }
			| NOPERSPECTIVE { $$ = new_node(NOPERSPECTIVE, NULL); }
			;

invariant_qualifier	: INVARIANT { $$ = new_node(INVARIANT, NULL); }
			;

precise_qualifier 	: PRECISE { $$ = new_node(PRECISE, NULL); }
			;

storage_qualifier	: CONST { $$ = new_node(CONST, NULL); }
			| INOUT { $$ = new_node(INOUT, NULL); }
			| IN { $$ = new_node(IN, NULL); }
			| OUT { $$ = new_node(OUT, NULL); }
			| CENTROID { $$ = new_node(CENTROID, NULL); }
			| PATCH { $$ = new_node(PATCH, NULL); }
			| SAMPLE { $$ = new_node(SAMPLE, NULL); }
			| UNIFORM { $$ = new_node(UNIFORM, NULL); }
			| BUFFER { $$ = new_node(BUFFER, NULL); }
			| SHARED { $$ = new_node(SHARED, NULL); }
			| COHERENT { $$ = new_node(COHERENT, NULL); }
			| VOLATILE { $$ = new_node(VOLATILE, NULL); }
			| RESTRICT { $$ = new_node(RESTRICT, NULL); }
			| READONLY { $$ = new_node(READONLY, NULL); }
			| WRITEONLY { $$ = new_node(WRITEONLY, NULL); }
			| SUBROUTINE { $$ = new_node(SUBROUTINE, NULL); }
			| SUBROUTINE LEFT_PAREN type_name_list RIGHT_PAREN  { $$ = new_node(SUBROUTINE, NULL); }
			;

type_name_list		: type_name { $$ = new_node(TYPE_NAME_LIST, NULL); $$->data.str = $1; }
			| type_name_list COMMA type_name { $$ = new_node(COMMA, $1, NULL); $$->data.str = $3; }
			;

expression		: assignment_expression { $$ = $1; }
			| expression COMMA assignment_expression { $$ = new_node(COMMA, $1, $3, NULL); }
			;

assignment_expression	: conditional_expression { $$ = $1; }
			| unary_expression assignment_operator assignment_expression { $$ = new_node($2, $1, $3, NULL); }
			;

assignment_operator	: EQUAL { $$ = EQUAL; }
			| MUL_ASSIGN { $$ = MUL_ASSIGN; }
			| DIV_ASSIGN { $$ = DIV_ASSIGN; }
			| MOD_ASSIGN { $$ = MOD_ASSIGN; }
			| ADD_ASSIGN { $$ = ADD_ASSIGN; }
			| SUB_ASSIGN { $$ = SUB_ASSIGN; }
			| LEFT_ASSIGN { $$ = LEFT_ASSIGN; }
			| RIGHT_ASSIGN { $$ = RIGHT_ASSIGN; }
			| AND_ASSIGN { $$ = AND_ASSIGN; }
			| XOR_ASSIGN { $$ = XOR_ASSIGN; }
			| OR_ASSIGN { $$ = OR_ASSIGN; }
			;

constant_expression	: conditional_expression { $$ = $1; }
			;

conditional_expression	: logical_or_expression { $$ = $1; }
			| logical_or_expression QUESTION expression COLON assignment_expression { $$ = new_node(QUESTION, $1, $3, $5, NULL); }
			;

logical_or_expression	: logical_xor_expression { $$ = $1; }
			| logical_or_expression OR_OP logical_xor_expression { $$ = new_node(OR_OP, $1, $3, NULL); }
			;

logical_xor_expression	: logical_and_expression { $$ = $1; }
			| logical_xor_expression XOR_OP logical_and_expression { $$ = new_node(XOR_OP, $1, $3, NULL); }
			;

logical_and_expression	: inclusive_or_expression { $$ = $1; }
			| logical_and_expression AND_OP inclusive_or_expression { $$ = new_node(AND_OP, $1, $3, NULL); }
			;

inclusive_or_expression : exclusive_or_expression { $$ = $1; }
			| inclusive_or_expression VERTICAL_BAR exclusive_or_expression { $$ = new_node(VERTICAL_BAR, $1, $3, NULL); }
			;

exclusive_or_expression	: and_expression { $$ = $1; }
			| exclusive_or_expression CARET and_expression { $$ = new_node(CARET, $1, $3, NULL); }
			;

and_expression		: equality_expression { $$ = $1; }
			| and_expression AMPERSAND equality_expression { $$ = new_node(AMPERSAND, $1, $3, NULL); }
			;

equality_expression	: relational_expression { $$ = $1; }
			| equality_expression EQ_OP relational_expression { $$ = new_node(EQ_OP, $1, $3, NULL); }
			| equality_expression NE_OP relational_expression { $$ = new_node(NE_OP, $1, $3, NULL); }
			;

relational_expression	: shift_expression { $$ = $1; }
			| relational_expression LEFT_ANGLE shift_expression { $$ = new_node(LEFT_ANGLE, $1, $3, NULL); }
			| relational_expression RIGHT_ANGLE shift_expression { $$ = new_node(RIGHT_ANGLE, $1, $3, NULL); }
			| relational_expression LE_OP shift_expression { $$ = new_node(LE_OP, $1, $3, NULL); }
			| relational_expression GE_OP shift_expression { $$ = new_node(GE_OP, $1, $3, NULL); }
			;

shift_expression	: additive_expression { $$ = $1; }
			| shift_expression LEFT_OP additive_expression { $$ = new_node(LEFT_OP, $1, $3, NULL); }
			| shift_expression RIGHT_OP additive_expression { $$ = new_node(RIGHT_OP, $1, $3, NULL); }
			;

additive_expression	: multiplicative_expression { $$ = $1; }
			| additive_expression PLUS multiplicative_expression { $$ = new_node(PLUS, $1, $3, NULL); }
			| additive_expression DASH multiplicative_expression { $$ = new_node(DASH, $1, $3, NULL); }
			;

multiplicative_expression : unary_expression { $$ = $1; }
			| multiplicative_expression STAR unary_expression { $$ = new_node(STAR, $1, $3, NULL); }
			| multiplicative_expression SLASH unary_expression { $$ = new_node(SLASH, $1, $3, NULL); }
			| multiplicative_expression PERCENT unary_expression { $$ = new_node(PERCENT, $1, $3, NULL); }
			;

unary_expression	: postfix_expression { $$ = $1; }
			| INC_OP unary_expression { $$ = new_node(INC_OP, $2, NULL); }
			| DEC_OP unary_expression { $$ = new_node(DEC_OP, $2, NULL); }
			| unary_operator unary_expression { $$ = new_node($1, $2, NULL); }
			;

unary_operator		: PLUS { $$ = PLUS; }
			| DASH { $$ = DASH; }
			| BANG { $$ = BANG; }
			| TILDE { $$ = TILDE; }
			;

postfix_expression	: primary_expression { $$ = $1; }
			| postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET { $$ = new_node(ARRAY_REF_OP, $1, $3, NULL); }
			| function_call { $$ = $1; }
			| postfix_expression DOT field_selection { $$ = new_node(DOT, $1, NULL); $$->data.str = $3; }
			| postfix_expression INC_OP { $$ = new_node(POST_INC_OP, $1, NULL); }
			| postfix_expression DEC_OP { $$ = new_node(POST_DEC_OP, $1, NULL); }
			;

integer_expression	: expression { $$ = $1; }
			;

function_call		: function_call_or_method { $$ = $1; }
			;

function_call_or_method	: function_call_generic { $$ = $1; }
			;

function_call_generic	: function_call_header_with_parameters RIGHT_PAREN { $$ = $1; }
			| function_call_header_no_parameters RIGHT_PAREN { $$ = $1; }
			;

function_call_header_no_parameters: function_call_header VOID { $$ = new_node(FUNCTION_CALL, $1, NULL); }
			| function_call_header { $$ = new_node(FUNCTION_CALL, $1, NULL); }
			;

function_call_header_with_parameters: function_call_header assignment_expression { $$ = new_node(FUNCTION_CALL, $1, $2, NULL); }
			| function_call_header_with_parameters COMMA assignment_expression { $$ = new_node(COMMA, $1, $3, NULL); }
			;

function_call_header	: function_identifier LEFT_PAREN { $$ = $1; }
			;

function_identifier	: type_specifier { $$ = new_node(TYPE_SPECIFIER, $1, NULL); }
			| postfix_expression { $$ = new_node(POSTFIX_EXPRESSION, $1, NULL); }
			;

primary_expression	: variable_identifier { $$ = new_node(IDENTIFIER, NULL); $$->data.str = $1; }
			| INTCONSTANT { $$ = new_node(INTCONSTANT, NULL); $$->data.i = $1; }
			| UINTCONSTANT { $$ = new_node(UINTCONSTANT, NULL); $$->data.ui = $1; }
			| FLOATCONSTANT { $$ = new_node(FLOATCONSTANT, NULL); $$->data.f = $1; }
			| BOOLCONSTANT { $$ = new_node(BOOLCONSTANT, NULL); $$->data.b = $1; }
			| DOUBLECONSTANT { $$ = new_node(DOUBLECONSTANT, NULL); $$->data.d = $1; }
			| LEFT_PAREN expression RIGHT_PAREN { $$ = $2; }
			;

%%
