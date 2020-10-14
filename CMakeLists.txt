cmake_minimum_required(VERSION 3.15)
project(fCore_has)


option(BUILD_TESTS "Build test programs" OFF)
option(PY_MODULE "Build python module" OFF)

include_directories(/usr/include/antlr4-runtime)
include_directories(includes)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)
if(PY_MODULE)
    add_subdirectory(includes/pybind11)
endif(PY_MODULE)
add_subdirectory(includes/fcore_has/fs_parser)
add_subdirectory(src)

#if(BUILD_TESTS)
add_subdirectory(test)
#endif(BUILD_TESTS)
unset(BUILD_TESTS CACHE)



