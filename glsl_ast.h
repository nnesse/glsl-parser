#ifndef GLSL_AST_H
#define GLSL_AST_H

#include "glsl_parser.h"

struct glsl_ast_walk_data;

//
// glsl_is_list_node()
//
// Returns true if the children of this node form
// a list
//
bool glsl_ast_is_list_node(struct glsl_node *n);

//
// glsl_ast_print()
//
// Print the AST tree as text for debugging purposes.
// The 'depth' parameter represents amount to indent the
// the printed text.
//
void glsl_ast_print(struct glsl_node *n, int depth);

//
// glsl_ast_generate_glsl()
//
// Translate AST into GLSL
//
// Returns a string containing the GLSL corresponding to
// the AST or NULL on error. The returned string must be
// deallocataed with free()
//
char *glsl_ast_generate_glsl(struct glsl_node *n);

//
// glsl_ast_walk_init()
//
// Initialize a glsl_ast_walk_data structure for
// subsequent use
//
void glsl_ast_walk_init(struct glsl_ast_walk_data *data);

//
// glsl_ast_walk_push_node()
//
// Queue node for traversal in glsl_ast_walk(). In a typical
// use case you would call this once outside of glsl_ast_walk()
// and inside of any nodes of interest in the glsl_ast_walk()'s
// enter_node() callback.
//
void glsl_ast_walk_push_node(struct glsl_ast_walk_data *data, struct glsl_node *n);

//
// glsl_ast_walk()
//
// Traverse tree nodes previously pushed with glsl_ast_walk_push_node(). When a node is processed
// enter_node() will be called. This callback should call glsl_ast_walk_push_node() if any of
// it's children also need processing. When all of a node's children are processed exit_node()
// will be called.
//
void glsl_ast_walk(struct glsl_ast_walk_data *data, intptr_t userdata,
	void (*enter_node)(struct glsl_ast_walk_data *data, struct glsl_node *n, intptr_t userdata),
	void (*exit_node)(struct glsl_ast_walk_data *data, struct glsl_node *n, intptr_t userdata));

struct glsl_ast_walk_data {
	struct glsl_node *node_stack[1024];
	int node_stack_level;

	struct glsl_node *parent_stack[1024];
	int parent_stack_idx[1024];
	int parent_stack_level;
};
#endif
