OBJS=glsl.tab.o lex.glsl.o glsl_regen.o glsl_ast.o glsl_parser_test.o

all: glsl_parser_test

lex.glsl.c: glsl.lex | glsl.tab.c
	flex --header-file=lex.glsl.h -P glsl -o lex.glsl.c glsl.lex

glsl.tab.c: glsl.y 
	bison glsl.y

lex.glsl.o: glsl.tab.c glsl_parser.h
glsl.tab.o: glsl_parser.h

glsl_regen.o: lex.glsl.c glsl.tab.c glsl_parser.h
glsl_ast.o: lex.glsl.c glsl.tab.c glsl_parser.h
glsl_parser_test.o: glsl_parser_test.c glsl_parser.h glsl.tab.c

%.o: %.c
	gcc -g -O0 -std=gnu99 -c -Wall $< -o $@

glsl_parser_test: $(OBJS)
	gcc $(OBJS) -o $@

clean:
	@-rm -f glsl.tab.c
	@-rm -f glsl.tab.h
	@-rm -f lex.glsl.c
	@-rm -f lex.glsl.h
	@-rm -f *.o
