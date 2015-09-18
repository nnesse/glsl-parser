#ifndef GLSL_PARSER_H
#define GLSL_PARSER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct glsl_node {
	//Type of this node. These values are all members of the enum
	int code:16;

	//Number of child nodes
	int child_count:16;

	//Meta data for this node. Only uses for some nodes. The
	//field in this unions that should be read (if any)
	//is determined by 'code'
	union {
		double d;
		float f;
		int i;
		unsigned int ui;
		bool b;
		const char *str;
	} data;

	//
	// Child nodes. Extra data will be allocated past the end
	// of the structure to hold the child nodes.
	//
	struct glsl_node *children[];
};

//
// Create a new node for the AST. All values following 'code' will be
// placed in the node's child array.
//
struct glsl_node *new_glsl_node(int code, ...) __attribute__ ((sentinel));

//
// Allocate memory
//
int8_t *glsl_parse_alloc(size_t size, int align);

struct glsl_parse_context {
	void *scanner;
	struct glsl_node *root;
};

/*

//
// Includes enum glsltokentype contains tokens that can be placed in glsl_node.code
// Some tokens are only used to communicate between the lexer and the parser.
// some are used in the AST and the lexer, and some are only used in the AST.
//
#include "glsl.tab.h"
*/
#endif
