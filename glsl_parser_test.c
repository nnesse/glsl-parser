#include <stdio.h>
#include <stdlib.h>
#include "glsl_parser.h"
#include "glsl_ast.h"

void error_cb(const char *str, int lineno, int first_col, int last_col)
{
	fprintf(stderr, "GLSL parse error line %d(%d-%d): %s\n", lineno, first_col, last_col, str);
}

int main()
{
	struct glsl_parse_context context;

	glsl_parse_context_init(&context);

	glsl_parse_set_error_cb(&context, error_cb);

	bool error = glsl_parse_file(&context, stdin);

	if (!error && context.root) {
		printf("\nAST tree:\n\n");
		glsl_ast_print(context.root, 0);

		printf("\nRegenerated GLSL:\n\n");
		char *out = glsl_ast_generate_glsl(context.root);
		printf("%s", out);
		free(out);
	}

	glsl_parse_context_destroy(&context);
}
