cmake_minimum_required(VERSION 3.5.0)
project(glsl_parser VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(glsl_parser glsl_ast.cpp glsl.lexer.cpp glsl.parser.cpp)
target_include_directories(glsl_parser PUBLIC ${HEADERS})

add_executable(parse_glsl ${SOURCES})
target_link_libraries(parse_glsl glsl_parser)
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
