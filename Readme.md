glsl-parser
=========

This is a GLSL parser implemented in C using `flex` and `bison`. The grammar is based on the OpenGL 4.5 reference specs. The parser generates an AST which should be complete but lacks documentation at this time.

Using
=====

This project contains a makefile that creates a test program called `glsl_parse` that reads a shader from standard input and prints out a human readable version of the shader's AST. To use the parser in your program or library remove the `main()` function from `glsl.y` and call `glslparse()` from a separate file. Consult the `flex` and `bison` documentation for more information.
