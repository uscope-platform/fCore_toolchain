cmake_minimum_required(VERSION 3.15)
project(fCore_has)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)
add_subdirectory(include/fs_parser)
add_subdirectory(src)
add_subdirectory(test)
