AST structure
=============

Each node in the AST has the same type `struct glsl_node`. The `glsl_node` struct stores a variable number of children in an array past the end of the structure. It also contains a `code` field that identifies what type of node it is and how to interpret it's child nodes. The node types are documented in the list below.

In each entry below the value on the left side of the ":" is a node type and the values on the right define the type of child nodes the type has. Nodes surrounded by brackets are optional and a "|" separated list denotes that the child can be any one of the types in the list. If a node is followed by `...` then it matches an arbitrary number of nodes (including zero) of that type. Entries in all lower case simply assign a label to an "|" list and do not define a node type.

AST node types
--------------
	TRANSLATION_UNIT        : DECLARATION | FUNCTION_DEFINITON

	FUNCTION_DEFINITION     : FUNCTION_DECLARATION STATEMENT_LIST

	FUNCTION_DECLARATION    : FUNCTION_HEADER FUNCTION_PARAMETER_LIST

	FUNCTION_HEADER         : FULLY_SPECIFIED_TYPE IDENTIFIER

	FUNCTION_PARAMETER_LIST : PARAMETER_DECLARATION ...

	PARAMETER_DECLARATION   : TYPE_QUALIFIER_LIST PARAMETER_DECLARATOR

	FULLY_SPECIFIED_TYPE    : TYPE_QUALIFIER_LIST TYPE_SPECIFIER

	TYPE_SPECIFIER          : type_specifier_nonarray ARRAY_SPECIFIER_LIST

	type_specifier_nonarray : type_token | STRUCT_SPECIFIER | IDENTIFIER

	STRUCT_SPECIFIER        : IDENTIFIER STRUCT_DECLARATION_LIST

	STRUCT_DECLARATION_LIST : STRUCT_DECLARATION ...

	STRUCT_DECLARATION      : TYPE_QUALIFIER_LIST TYPE_SPECIFIER STRUCT_DECLARATOR_LIST

	STRUCT_DECLARATOR_LIST  : STRUCT_DECLARATOR ...

	STRUCT_DECLARATOR       : IDENTIFIER ARRAY_SPECIFIER_LIST

	type_token              : VOID | FLOAT | DOUBLE | INT | UINT | BOOL
	                        | VEC2 | VEC3 | VEC4
	                        | DVEC2 | DVEC3 | DVEC4
	                        | BVEC2 | BVEC3 | BVEC4
	                        | IVEC2 | IVEC3 | IVEC4
	                        | UVEC2 | UVEC3 | UVEC4
	                        | MAT2 | MAT3 | MAT4
	                        | MAT2X2 | MAT2X3 | MAT2X4
	                        | MAT3X2 | MAT3X3 | MAT3X4
	                        | MAT4X2 | MAT4X3 | MAT4X4
	                        | DMAT2 | DMAT3 | DMAT4
	                        | DMAT2X2 | DMAT2X3 | DMAT2X4
	                        | DMAT3X2 | DMAT3X3 | DMAT3X4
	                        | DMAT4X2 | DMAT4X3 | DMAT4X4
	                        | ATOMIC_UINT
	                        | SAMPLER1D | SAMPLER2D | SAMPLER3D
	                        | SAMPLERCUBE
	                        | SAMPLER1DSHADOW | SAMPLER2DSHADOW | SAMPLERCUBESHADOW
	                        | SAMPLER1DARRAY | SAMPLER2DARRAY
	                        | SAMPLER1DARRAYSHADOW | SAMPLER2DARRAYSHADOW
	                        | SAMPLERCUBEARRAY | SAMPLERCUBEARRAYSHADOW
	                        | ISAMPLER1D | ISAMPLER2D | ISAMPLER3D
	                        | ISAMPLERCUBE
	                        | ISAMPLER1DARRAY | ISAMPLER2DARRAY | ISAMPLERCUBEARRAY
	                        | USAMPLER1D | USAMPLER2D | USAMPLER3D
	                        | USAMPLERCUBE | USAMPLER1DARRAY
	                        | USAMPLER2DARRAY | USAMPLERCUBEARRAY | SAMPLER2DRECT
	                        | SAMPLER2DRECTSHADOW | ISAMPLER2DRECT | USAMPLER2DRECT
	                        | SAMPLERBUFFER | ISAMPLERBUFFER | USAMPLERBUFFER
	                        | SAMPLER2DMS | ISAMPLER2DMS | USAMPLER2DMS
	                        | SAMPLER2DMSARRAY | ISAMPLER2DMSARRAY | USAMPLER2DMSARRAY
	                        | IMAGE1D | IIMAGE1D | UIMAGE1D
	                        | IMAGE2D | IIMAGE2D | UIMAGE2D
	                        | IMAGE3D | IIMAGE3D | UIMAGE3D
	                        | IMAGE2DRECT | IIMAGE2DRECT | UIMAGE2DRECT
	                        | IMAGECUBE | IIMAGECUBE | UIMAGECUBE
	                        | IMAGEBUFFER | IIMAGEBUFFER | UIMAGEBUFFER
	                        | IMAGE1DARRAY | IIMAGE1DARRAY | UIMAGE1DARRAY
	                        | IMAGE2DARRAY | IIMAGE2DARRAY | UIMAGE2DARRAY
	                        | IMAGECUBEARRAY | IIMAGECUBEARRAY | UIMAGECUBEARRAY
	                        | IMAGE2DMS | IIMAGE2DMS | UIMAGE2DMS
	                        | IMAGE2DMSARRAY | IIMAGE2DMSARRAY | UIMAGE2DMSARRAY

	PARAMETER_DECLARATOR    : TYPE_SPECIFIER IDENTIFIER ARRAY_SPECIFIER_LIST

	type_qualifier          : LAYOUT_QUALIFIER_ID_LIST | HIGHP | MEDIUMP
	                        | LOWP | SMOOTH | FLAT| NOPERSPECTIVE
	                        | INVARIANT | PRECISE | storage_qualifier

	TYPE_QUALIFIER_LIST     : type_qualifier ...

	storage_qualifier       : CONST | INOUT | IN | OUT | CENTROID
	                        | PATCH | SAMPLE | UNIFORM | BUFFER | SHARED
	                        | COHERENT | VOLATILE | RESTRICT | READONLY | WRITEONLY
	                        | SUBROUTINE | SUBROUTINE_TYPE

	SUBROUTINE_TYPE         : TYPE_NAME_LIST | IDENTIFIER

	TYPE_NAME_LIST          : IDENTIFIER ...

	LAYOUT_QUALIFIER_ID_LIST: (LAYOUT_QUALIFIER_ID | SHARED ) ...

	LAYOUT_QUALIFIER_ID     : (TODO)

	STATEMENT_LIST          : statement ...

	statement               : DECLARATION | EXPRESSION_STATEMENT | SELECTION_STATEMENT
	                        | RETURN | RETURN_VALUE | BREAK | FOR_STATEMENT | WHILE_STATEMENT
	                        | DO_STATEMENT

	DECLARATION		: INIT_DECLARATOR_LIST | BLOCK_DECLARATION | FUNCTION_DECLARATION

	INIT_DECLARATOR_LIST	: (SINGLE_DECLARATION | SINGLE_INIT_DECLARATION) INIT_DECLARATOR ...

	INIT_DECLARATOR		: IDENTIFIER ARRAY_SPECIFIER_LIST INITIALIZER

	INITIALIZER		: expression | INITIALIZER_LIST

	INITIALIZER_LIST	: INITIALIZER...

	EXPRESSION_STATEMENT	: expression

	expression              : binary_expression | prefix_expression | postfix_expression

	binary_expression       : EQUAL | MUL_ASSIGN | DIV_ASSIGN | MOD_ASSIGN
	                        | ADD_ASSIGN | SUB_ASSIGN | LEFT_ASSIGN
	                        | RIGHT_ASSIGN | AND_ASSIGN | XOR_ASSIGN
	                        | OR_ASSIGN | PLUS | DASH | STAR | SLASH
	                        | PERCENT | AMPERSAND | EQ_OP | NE_OP
	                        | LEFT_ANGLE | RIGHT_ANGLE | LE_OP | GE_OP
	                        | LEFT_OP | RIGHT_OP | CARET | VERTICAL_BAR
	                        | AND_OP | OR_OP | XOR_OP

	prefix_expression       : PRE_INC_OP | PRE_DEC_OP | UNARY_PLUS
	                        | UNARY_DASH | TILDE | BANG

	POSTFIX_EXPRESSION      : expression

	postfix_expression      : POST_INC_OP | POST_DEC_OP | FUNCTION_CALL | ARRAY_REF_OP | DOT
	                        | IDENTIFIER | INTCONSTANT | UINTCONSTANT | FLOATCONSTANT | TRUE
		                | FALSE

	DOT                     : expression IDENTIFIER

	SINGLE_DECLARATION      : FULLY_SPECIFIED_TYPE IDENTIFIER ARRAY_SPECIFIER_LIST

	SINGLE_INIT_DECLARATION : FULLY_SPECIFIED_TYPE IDENTIFIER ARRAY_SPECIFIER_LIST INITIALIZER

	BLOCK_DECLARATION       : TYPE_QUALIFIER_LIST IDENTIFIER STRUCT_DECLARATION_LIST IDENTIFIER ARRAY_SPECIFIER_LIST

	FUNCTION_CALL           : (TYPE_SPECIFIER | POSTFIX_EXPRESSION) FUNCITON_CALL_PARAMETER_LIST

	ARRAY_REF_OP            : expression expression

	BREAK                   : (empty)

	SELECTION_STATEMENT     : expression statement

	SELECTION_STATEMENT_ELSE: expression statement statement

	WHILE_STATEMENT         : condition statement

	DO_STATEMENT            : statement expression

	FOR_STATEMENT           : for_init_statement FOR_REST_STATEMENT

	for_init_statement      : EXPRESSION_STATEMENT | DECLARATION

	FOR_REST_STATEMENT      : CONDITION_OPT [expression]

	CONDITION_OPT           : [condition]

	condition               :  EXPRESSION_CONDITION | ASSIGNMENT_CONDITION

	EXPRESSION_CONDITION    : expression

	ASSIGNMENT_CONDITION    : FULLY_SPECIFIED_TYPE IDENTIFIER INITIALIZER

	RETURN                  : (none)

	RETURN_VALUE            : expression
