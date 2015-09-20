#ifndef GLSL_PARSER_H
#define GLSL_PARSER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

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

struct glsl_parse_context {
	void *scanner; //Opaque handle to lexer context
	struct glsl_node *root;

	/* Internal state of the parser's stack allocator */
	uint8_t *first_buffer;
	uint8_t *cur_buffer_start;
	uint8_t *cur_buffer;
	uint8_t *cur_buffer_end;
};

//
// Create a new node for the AST. All values following 'code' will be
// placed in the node's child array.
//
struct glsl_node *new_glsl_node(struct glsl_parse_context *context, int code, ...) __attribute__ ((sentinel));

//
// Allocate memory in the parser's stack allocator
//
uint8_t *glsl_parse_alloc(struct glsl_parse_context *context, size_t size, int align);

//
// Deallocate all memory previously allocated by glsl_parse_alloc()
// The parser internally uses this allocator so any generated
// AST data will become invalid when glsl_parse_dealloc() is called.
//
void glsl_parse_dealloc(struct glsl_parse_context *context);

//
// Initialize a parsing context
//
void glsl_parse_context_init(struct glsl_parse_context *context);

//
// Destroy a parsing context.
//
void glsl_parse_context_destroy(struct glsl_parse_context *context);

//
// Parse the supplied file and generate an AST in context->root.
//
void glsl_parse_file(struct glsl_parse_context *context, FILE *file);

//
// Include glsl.parse.h to get the enum values that are stored in the 'code'
// field of glsl_node.
//
#include "glsl.parser.h"
#endif
