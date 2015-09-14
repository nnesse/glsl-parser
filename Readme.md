glsl-parser
=========

This is a GLSL parser implemented in C using `flex` and `bison`. It generates an AST using a single node type that stores a variable number of children. The grammar is based on the OpenGL 4.5 reference specs with some small fixes and edits. The AST should be complete but it needs more testing and documentation. Until proper documentation is created it should be possible to determine how to interpret the AST by studying the bison input file `glsl.y` and experimenting with the test program `glsl_parse`. The parser could be useful to a real-time shader editor to detect shader inputs, a node based material editor, or to create a GLSL dialect that could be converted to actual GLSL files(s).

Using
=====

This project contains a makefile that can be used to generate a test program called `glsl_parse` which takes a shader from standard input and prints out a human readable version of the AST. To use the parser in your program or library you should remove the `main()` function from `glsl.y` and call `glslparse()` from a separate file in your project. Consult the `flex` and `bison` documentation for more information on how to setup the parser for your environment.
