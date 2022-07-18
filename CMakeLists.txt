cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)

include(GNUInstallDirs)

option(BUILD_TESTS "Build test programs" OFF)
option(INCLUDE_EMULATOR "Include the emulator in the build" OFF)
option(INCLUDE_COVERAGE "Build with support for code coverage" OFF)
option(CROSS_COMPILE "Cross compile for arm 32 bit" OFF)

set(ANTLR_VERSION 4.9.3)
SET(ANTLR_JAR antlr-${ANTLR_VERSION}-complete.jar)
set(ANTLR_CLASSPATH ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar/${ANTLR_JAR})
set(ANTLR_OPTIONS -Dlanguage=Cpp -visitor -listener  -encoding iso-8859-1)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/antlr_runtime/dist/usr/local/include/antlr4-runtime)
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


if(${INCLUDE_COVERAGE})
    add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif(${INCLUDE_COVERAGE})

if(${CROSS_COMPILE})

    set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif(${CROSS_COMPILE})

message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/antlr_runtime_src-src/runtime/Cpp/runtime/src)

add_subdirectory(src)

if(${BUILD_TESTS})
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)

include(ExternalProject)

add_custom_target(parsers)
add_dependencies(parsers c_parser_gen asm_parser_gen)

include(FetchContent)

FetchContent_Declare(
        antlr_runtime_src
        GIT_REPOSITORY https://github.com/antlr/antlr4.git
        SOURCE_SUBDIR runtime/Cpp
        GIT_TAG ${ANTLR_VERSION}
)

FetchContent_MakeAvailable(antlr_runtime_src)


FetchContent_Declare(
        antlr_jar
        URL https://github.com/antlr/website-antlr4/blob/gh-pages/download/${ANTLR_JAR}?raw=true
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar
        DOWNLOAD_NAME ${ANTLR_JAR}
        DOWNLOAD_NO_EXTRACT ON
)
FetchContent_MakeAvailable(antlr_jar)