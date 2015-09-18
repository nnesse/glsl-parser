#ifndef GLSL_AST_H
#define GLSL_AST_H

#include "glsl_parser.h"

bool glsl_is_list_node(struct glsl_node *n);

void glsl_print_ast_tree(struct glsl_node *n, int depth);

#endif
