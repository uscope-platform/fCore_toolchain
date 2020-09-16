cmake_minimum_required(VERSION 3.15)
project(fCore_has)

option(BUILD_TESTS "Build test programs" OFF)

include_directories(/usr/include/antlr4-runtime)
include_directories(includes)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)
add_subdirectory(includes/pybind11)
add_subdirectory(includes/fcore_has/fs_parser)
add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
    find_package(Catch2 REQUIRED PATH)
endif(BUILD_TESTS)
unset(BUILD_TESTS CACHE)



