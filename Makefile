OBJS=glsl.tab.o lex.glsl.o

all: glsl_parse

lex.glsl.c: glsl.lex | glsl.tab.c
	flex --header-file=lex.glsl.h -P glsl -o lex.glsl.c glsl.lex

glsl.tab.c: glsl.y 
	bison glsl.y

glsl.tab.o: lex.glsl.c glsl_common.h

lex.glsl.o: glsl_common.h

%.o: %.c
	gcc -g -O0 -std=gnu99 -c -Wall $< -o $@

glsl_parse: $(OBJS)
	gcc $(OBJS) -o $@

clean:
	@-rm -f glsl.tab.c
	@-rm -f glsl.tab.h
	@-rm -f lex.glsl.c
	@-rm -f lex.glsl.h
	@-rm *.o
