#include <stdio.h>
#include <stdlib.h>
#include "glsl_parser.h"
#include "glsl_ast.h"

int main()
{
	struct glsl_parse_context context;

	glsl_parse_context_init(&context);

	glsl_parse_file(&context, stdin);

	if (context.root) {
		printf("\nAST tree:\n\n");
		glsl_print_ast_tree(context.root, 0);

		printf("\nRegenerated GLSL:\n\n");
		char *out = glsl_regen_tree(context.root);
		printf("%s", out);
		free(out);
	}

	glsl_parse_context_destroy(&context);
}
