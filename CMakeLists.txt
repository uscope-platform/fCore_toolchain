cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)

include(GNUInstallDirs)

option(BUILD_TESTS "Build test programs" OFF)
option(INCLUDE_EMULATOR "Include the emulator in the build" OFF)
option(INCLUDE_COVERAGE "Build with support for code coverage" OFF)


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

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)

add_subdirectory(src)

if(${BUILD_TESTS})
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)

include(ExternalProject)

ExternalProject_Add(antlr_runtime
        GIT_REPOSITORY https://github.com/antlr/antlr4.git
        GIT_TAG ${ANTLR_VERSION}
        SOURCE_SUBDIR runtime/Cpp
        INSTALL_COMMAND DESTDIR=${CMAKE_BINARY_DIR}/antlr_runtime/dist make install
        )

add_custom_target(parsers)
add_dependencies(parsers c_parser_gen asm_parser_gen antlr_runtime)

ExternalProject_Add(antlr_jar
        URL https://github.com/antlr/website-antlr4/blob/gh-pages/download/${ANTLR_JAR}?raw=true
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar
        DOWNLOAD_NAME ${ANTLR_JAR}
        DOWNLOAD_NO_EXTRACT ON
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        )
