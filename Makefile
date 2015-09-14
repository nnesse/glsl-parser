all: glsl.tab.o lex.glsl.o


lex.glsl.c: glsl.lex | glsl.tab.c
	flex --header-file=lex.glsl.h -P glsl -o lex.glsl.c glsl.lex

glsl.tab.c: glsl.y 
	bison glsl.y

glsl.tab.o: lex.glsl.c

%.o: %.c
	gcc -std=gnu99 -c -Wall $< -o $@

clean:
	@-rm -f glsl.tab.c
	@-rm -f glsl.tab.h
	@-rm -f lex.glsl.c
	@-rm -f lex.glsl.h
	@-rm *.o
