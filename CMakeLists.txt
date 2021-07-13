cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)


option(BUILD_TESTS "Build test programs" OFF)

include_directories(/usr/include/antlr4-runtime)
include_directories(includes)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")


add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)


add_subdirectory(src)

if(${BUILD_TESTS})
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)



