glsl-parser
=========

This is a GLSL parser implemented with `flex` and `bison`. The grammar is based on the OpenGL 4.5 reference specs. The parser generates an AST represented in C data structures. The AST structure is documented in AstNodes.md.

Using
=====

This project contains a makefile that creates a test program called `glsl_parse`. `glsl_parse` reads a shader from standard input and prints out a human readable version of the shader's AST and attempts to regenerate the shader from the AST. To use the parser in your program or library remove the `main()` function from `glsl.y` and call `glslparse()` from a separate file.
