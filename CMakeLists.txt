cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)

include(GNUInstallDirs)

option(BUILD_TESTS "Build test programs" OFF)
option(INCLUDE_EMULATOR "Include the emulator in the build" OFF)
option(INCLUDE_COVERAGE "Build with support for code coverage" OFF)
option(INCLUDE_DEVTOOLS "Include compiler development tools in the build" OFF)

set(ANTLR_VERSION 4.10.1)
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

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=undefined -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DSCHEMAS_FOLDER="${CMAKE_SOURCE_DIR}/schemas")
else()
    add_definitions(-DSCHEMAS_FOLDER="/usr/local/etc/fcore_toolchain")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(${INCLUDE_COVERAGE})
    add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif(${INCLUDE_COVERAGE})

message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/antlr_runtime_src-src/runtime/Cpp/runtime/src)

find_package(nlohmann_json REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(antlr4-runtime REQUIRED)
find_package(GTest REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)


if(${INCLUDE_DEVTOOLS})
    find_package(cpprestsdk REQUIRED)

endif(${INCLUDE_DEVTOOLS})

add_subdirectory(src)

if(${BUILD_TESTS})
    enable_testing()
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)

include(ExternalProject)

add_custom_target(parsers)
add_dependencies(parsers c_parser_gen asm_parser_gen)
