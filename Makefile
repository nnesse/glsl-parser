OBJS=glsl.parser.o glsl.lexer.o glsl_ast.o glsl_parser_test.o

all: glsl_parser_test

glsl.lexer.cpp: glsl.l
	flex  --header-file=glsl.lexer.h -o $@ $<

glsl.parser.cpp: glsl.y
	bison --defines=glsl.parser.h $< -o $@

%.o: %.cpp
	g++ -g -O0 -std=c++14 -c -Wall $< -o $@

glsl.lexer.o: glsl_parser.h glsl.parser.cpp
glsl.parser.o: glsl_parser.h glsl.lexer.cpp glsl.parser.cpp

glsl_ast.o: glsl_ast.cpp glsl_parser.h glsl.lexer.cpp glsl.parser.cpp
glsl_parser_test.o: glsl_parser_test.cpp glsl_parser.h glsl.parser.cpp

glsl_parser_test: $(OBJS)
	g++ $(OBJS) -o $@

clean:
	@-rm -f glsl_parser_test
	@-rm -f glsl.parser.cpp
	@-rm -f glsl.parser.h
	@-rm -f glsl.lexer.cpp
	@-rm -f glsl.lexer.h
	@-rm -f *.o

