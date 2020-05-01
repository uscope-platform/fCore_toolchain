cmake_minimum_required(VERSION 3.15)
project(fCore_has)

include_directories(include/antlr4-runtime)

ADD_LIBRARY(antlr4 STATIC IMPORTED)
SET_TARGET_PROPERTIES(antlr4 PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/include/antlr4-runtime/libantlr4-runtime.a")

find_package(Catch2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)
add_subdirectory(include/fs_parser)
add_subdirectory(src)
add_subdirectory(test)



