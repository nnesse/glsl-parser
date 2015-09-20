#include "glsl_parser.h"
#include "glsl_ast.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static const char *token_to_str[4096] = {
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
	[TRUE] = "true",
	[FALSE] = "false",
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
	[PRE_INC_OP] = "++",
	[PRE_DEC_OP] = "--",
	[POST_INC_OP] = "++",
	[POST_DEC_OP] = "--",
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
	[AT] = "@",
	[UNARY_PLUS] = "+",
	[UNARY_DASH] = "-",
	[NUM_TOKEN] = ""
};

bool is_optional_list(struct glsl_node *n)
{
	switch(n->code) {
	case ARRAY_SPECIFIER_LIST:
	case TYPE_QUALIFIER_LIST:
		return true;
	}
	return false;
}

struct string {
	char *s;
	int len;
	int capacity;
};

static void _glsl_regen_tree(struct glsl_node *n, struct string *out, int depth);

static void string_cat(struct string *str, const char *format, ...)
{
	int n;
	va_list vl;
	do {
		int left = str->capacity - str->len;
		va_start(vl, format);
		n = vsnprintf(str->s + str->len, left, format, vl);
		va_end(vl);
		if (n < left) {
			break;
		} else {
			str->capacity *= 2;
			str->s = realloc(str->s, str->capacity);
		}
	} while (1);
	str->len += n;
}

static void print_list_as_glsl(struct glsl_node *n, const char *prefix, const char *delim, const char *postfix, struct string *out, int depth)
{
	int i, c = 0;
	string_cat(out,"%s", prefix);
	for (i = 0; i < n->child_count; i++) {
		if (!n->children[i]->child_count && is_optional_list(n->children[i]))
			continue;
		if (c)
			string_cat(out,"%s", delim);
		c++;
		_glsl_regen_tree(n->children[i], out, depth);
	}
	string_cat(out,"%s", postfix);
}

static void _glsl_regen_tree(struct glsl_node *n, struct string *out, int depth)
{
	int i;
	int j;
	switch(n->code) {
	case IDENTIFIER:
		if (n->data.str)
			string_cat(out,"%s", n->data.str);
		break;
	case FLOATCONSTANT:
		string_cat(out,"%f", n->data.f);
		break;
	case DOUBLECONSTANT:
		string_cat(out,"%f", n->data.d);
		break;
	case INTCONSTANT:
		string_cat(out,"%d", n->data.i);
		break;
	case UINTCONSTANT:
		string_cat(out,"%u", n->data.ui);
		break;
	case TRANSLATION_UNIT:
		print_list_as_glsl(n, "", "\n", "\n", out, depth);
		break;
	case ARRAY_SPECIFIER_LIST:
		print_list_as_glsl(n, "", "", "", out, depth);
		break;
	case ARRAY_SPECIFIER:
		print_list_as_glsl(n, "[", "", "]", out, depth);
		break;
	case EQUAL:
	case MUL_ASSIGN:
	case DIV_ASSIGN:
	case MOD_ASSIGN:
	case ADD_ASSIGN:
	case SUB_ASSIGN:
	case LEFT_ASSIGN:
	case RIGHT_ASSIGN:
	case AND_ASSIGN:
	case XOR_ASSIGN:
	case OR_ASSIGN:
	case PLUS:
	case DASH:
	case STAR:
	case SLASH:
	case PERCENT:
	case AMPERSAND:
	case EQ_OP:
	case NE_OP:
	case LEFT_ANGLE:
	case RIGHT_ANGLE:
	case LE_OP:
	case GE_OP:
	case LEFT_OP:
	case RIGHT_OP:
	case CARET:
	case VERTICAL_BAR:
	case AND_OP:
	case OR_OP:
	case XOR_OP:
		_glsl_regen_tree(n->children[0], out, depth);
		if (token_to_str[n->code]) {
			string_cat(out," %s ", token_to_str[n->code]);
		} else {
			string_cat(out," <unknown operator %d> ", n->code);
		}
		_glsl_regen_tree(n->children[1], out, depth);
		break;
	case DOT:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,".");
		_glsl_regen_tree(n->children[1], out, depth);
		break;
	case PRE_INC_OP:
	case PRE_DEC_OP:
	case UNARY_PLUS:
	case UNARY_DASH:
	case TILDE:
	case BANG:
		print_list_as_glsl(n, token_to_str[n->code], "", "", out, depth);
		break;
	case PAREN_EXPRESSION:
		print_list_as_glsl(n, "(", "", ")", out, depth);
		break;
	case POST_INC_OP:
	case POST_DEC_OP:
		print_list_as_glsl(n, "", "", token_to_str[n->code], out, depth);
		break;
	case FUNCTION_DECLARATION:
	case FUNCTION_HEADER:
	case FULLY_SPECIFIED_TYPE:
	case PARAMETER_DECLARATION:
	case PARAMETER_DECLARATOR:
	case TYPE_QUALIFIER_LIST:
		print_list_as_glsl(n, "", " ", "", out, depth);
		break;
	case FUNCTION_DEFINITION:
		print_list_as_glsl(n, "", " ", "\n", out, depth);
		break;
	case FUNCTION_CALL:
		_glsl_regen_tree(n->children[0], out, depth);
		_glsl_regen_tree(n->children[1], out, depth);
		break;
	case SELECTION_STATEMENT:
		string_cat(out,"if (");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,") ");
		_glsl_regen_tree(n->children[1], out, depth);
		break;
	case ARRAY_REF_OP:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,"[");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out,"]");
		break;
	case RETURN:
		string_cat(out,"return;\n");
		break;
	case RETURN_VALUE:
		string_cat(out,"return ");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,";\n");
		break;
	case SELECTION_STATEMENT_ELSE:
		string_cat(out,"if (");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,") ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out," else ");
		_glsl_regen_tree(n->children[2], out, depth);
		string_cat(out,"\n");
		break;
	case SINGLE_DECLARATION:
		print_list_as_glsl(n, "", " ", ";", out, depth);
		break;
	case SINGLE_INIT_DECLARATION:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out," ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out," = ");
		_glsl_regen_tree(n->children[3], out, depth);
		string_cat(out,";");
		break;
	case WHILE_STATEMENT:
		string_cat(out,"while (");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,") ");
		_glsl_regen_tree(n->children[1], out, depth);
		break;
	case DO_STATEMENT:
		string_cat(out,"do ");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out," while ( ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out," );");
		break;
	case FOR_STATEMENT:
		string_cat(out,"for (");
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out," ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out,") ");
		_glsl_regen_tree(n->children[2], out, depth);
		break;
	case ASSIGNMENT_CONDITION:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out," ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out," = ");
		_glsl_regen_tree(n->children[2], out, depth);
		break;
	case STATEMENT_LIST:
		string_cat(out,"{\n");
		for (i = 0; i < n->child_count; i++) {
			for (j = 0; j < depth + 1; j++) string_cat(out,"\t");
			_glsl_regen_tree(n->children[i], out, depth + 1);
			string_cat(out,"\n");
		}
		for (j = 0; j < depth; j++) string_cat(out,"\t");
		string_cat(out,"}");
		break;
	case STRUCT_DECLARATION_LIST:
		for (i = 0; i < n->child_count; i++) {
			for (j = 0; j < depth + 1; j++) string_cat(out,"\t");
			_glsl_regen_tree(n->children[i], out, depth + 1);
			string_cat(out,"\n");
		}
		for (j = 0; j < depth; j++) string_cat(out,"\t");
		break;
	case BLOCK_DECLARATION:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out," ");
		_glsl_regen_tree(n->children[1], out, depth);
		string_cat(out," {\n");
		_glsl_regen_tree(n->children[2], out, depth);
		string_cat(out,"} ");
		_glsl_regen_tree(n->children[3], out, depth);
		if (n->children[4]->child_count) {
			string_cat(out," ");
			_glsl_regen_tree(n->children[4], out, depth);
		}
		string_cat(out,";");
		break;
	case BREAK:
		string_cat(out,"break;");
		break;
	case STRUCT_DECLARATOR:
		print_list_as_glsl(n, "", " ", "", out, depth);
		break;
	case STRUCT_DECLARATOR_LIST:
		print_list_as_glsl(n, "", ",", "", out, depth);
		break;
	case STRUCT_DECLARATION:
		print_list_as_glsl(n, "", " ", ";", out, depth);
		break;
	case FUNCTION_PARAMETER_LIST:
	case FUNCTION_CALL_PARAMETER_LIST:
		print_list_as_glsl(n, "(", ", ", ")", out, depth);
		break;
	case FOR_REST_STATEMENT:
		_glsl_regen_tree(n->children[0], out, depth);
		string_cat(out,"; ");
		if (n->child_count == 2) {
			_glsl_regen_tree(n->children[1], out, depth);
		}
		break;
	case DECLARATION_STATEMENT:
		_glsl_regen_tree(n->children[0], out, depth);
		break;
	case TYPE_SPECIFIER:
	case POSTFIX_EXPRESSION:
	case CONDITION_OPT:
	case EXPRESSION_CONDITION:
		print_list_as_glsl(n, "", "", "", out, depth);
		break;
	case EXPRESSION_STATEMENT:
		print_list_as_glsl(n, "", "", ";", out, depth);
		break;
	default:
		if (token_to_str[n->code])
			string_cat(out,"%s", token_to_str[n->code]);
		else
			string_cat(out,"<unknown token %d>", n->code);
		break;
	}
}

char *glsl_regen_tree(struct glsl_node *n)
{
	struct string s;
	s.s = malloc(1024);
	s.len = 0;
	s.capacity = 1024;
	_glsl_regen_tree(n, &s, 0);
	return s.s;
}
