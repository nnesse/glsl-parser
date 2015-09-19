glsl-parser
=========

This is a GLSL parser implemented with `flex` and `bison`. The grammar is based on the OpenGL 4.5 reference specs. The parser generates an AST represented in C data structures. The AST structure is documented in AstNodes.md.

Using
=====

The header files `glsl_parser.h` documents the interface to the parser. The header file `glsl_ast.h` defines some useful functions for working with the AST generated
by the parser including the function `glsl_regen_tree()` which generates GLSL from the AST.

This project contains a makefile that creates a test program called `glsl_parse_test` that reads a shader from standard input and prints out a human readable version of the shader's AST and attempts to regenerate the input shader from the AST. 
