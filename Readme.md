glsl-parser
=========

A GLSL parser implemented in C using `flex` and `bison`. It generates an AST using a single node type that stores a variable number of children. The grammar is based on the OpenGL 4.5 reference specs with some small fixes and edits. The AST should be complete but it needs more testing.

The node types are relatively intuitive but need some documentations. For now it should be possible to figure out how to interpret them by studying the bison input file `glsl.y`. The parser could be useful to a real-time shader editor to detect shader inputs, a node based material editor, or to create a GLSL dialect that could be converted to actual GLSL files(s).

Using
=====

You can build the parser with the Makefile but it is only used to generate a test program called `glsl_parse` which takes a shader from standard input and prints out a human readable version of the AST. To use the parser you should remove the `main()` function from `glsl.y` and call `glslparse()` from a separate file in your project. `glslparse` places the root node of the AST in a global variable
called `g_glsl_node_root`.
