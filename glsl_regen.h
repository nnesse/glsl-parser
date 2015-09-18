#ifndef GLSL_REGEN_H
#define GLSL_REGEN_H
#include "glsl.tab.h"
#include "glsl_parser.h"

void glsl_regen_tree(struct glsl_node *n, int depth);

#endif
