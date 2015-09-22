OBJS=glsl.parser.o glsl.lexer.o glsl_ast.o glsl_parser_test.o

all: glsl_parser_test

glsl.lexer.c: glsl.lex
	flex -o $@ $<

glsl.parser.c: glsl.y
	bison $< -o $@

%.o: %.c
	gcc -g -O0 -std=gnu99 -c -Wall $< -o $@

glsl.lexer.o: glsl_parser.h glsl.parser.c
glsl.parser.o: glsl_parser.h glsl.lexer.c glsl.parser.c

glsl_ast.o: glsl_ast.c glsl_parser.h glsl.lexer.c glsl.parser.c
glsl_parser_test.o: glsl_parser_test.c glsl_parser.h glsl.parser.c

glsl_parser_test: $(OBJS)
	gcc $(OBJS) -o $@

clean:
	@-rm -f glsl_parser_test
	@-rm -f glsl.parser.c
	@-rm -f glsl.parser.h
	@-rm -f glsl.lexer.c
	@-rm -f glsl.lexer.h
	@-rm -f *.o
