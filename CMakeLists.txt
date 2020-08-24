cmake_minimum_required(VERSION 3.15)
project(fCore_has)

include_directories(/usr/include/antlr4-runtime)
include_directories(includes)

find_package(Catch2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)
add_subdirectory(includes/fcore_has/fs_parser)
add_subdirectory(src)
add_subdirectory(test)



