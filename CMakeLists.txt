cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)


option(BUILD_TESTS "Build test programs" OFF)

include_directories(/usr/include/antlr4-runtime)
include_directories(includes)

# setup xilinx fp model c library
include_directories(third_party/fp_ip_cmodel/includes)
link_directories(third_party/fp_ip_cmodel/lib)

install (FILES third_party/fp_ip_cmodel/lib/libgmp.so.11 DESTINATION /usr/lib/x86_64-linux-gnu)
install (FILES third_party/fp_ip_cmodel/lib/libmpfr.so.4 DESTINATION /usr/lib/x86_64-linux-gnu)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
add_link_options(-fprofile-arcs -ftest-coverage)

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)


add_subdirectory(src)

if(${BUILD_TESTS})
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)



