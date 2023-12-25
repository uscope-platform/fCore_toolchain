cmake_minimum_required(VERSION 3.15)

project(fCore_toolchain)

include(GNUInstallDirs)

option(BUILD_TESTS "Build test programs" OFF)
option(INCLUDE_EMULATOR "Include the emulator in the build" OFF)
option(INCLUDE_COVERAGE "Build with support for code coverage" OFF)
option(INCLUDE_DEVTOOLS "Include compiler development tools in the build" OFF)
option(USE_CONAN "Use the conan package manager for dependency management" OFF)

set(ANTLR_VERSION 4.13.1)
SET(ANTLR_JAR antlr-${ANTLR_VERSION}-complete.jar)
set(ANTLR_CLASSPATH ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar/${ANTLR_JAR})
set(ANTLR_OPTIONS -Dlanguage=Cpp -visitor -listener  -encoding iso-8859-1)

include_directories(includes)

if(${INCLUDE_EMULATOR})
    # setup xilinx fp model c library
    include_directories(third_party/fp_ip_cmodel/includes)
    link_directories(third_party/fp_ip_cmodel/lib)

    install(FILES third_party/fp_ip_cmodel/lib/libgmp.so.11 DESTINATION lib/x86_64-linux-gnu)
    install(FILES third_party/fp_ip_cmodel/lib/libmpfr.so.4 DESTINATION lib/x86_64-linux-gnu)
endif(${INCLUDE_EMULATOR})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=undefined -fsanitize=address)
    add_link_options(-fsanitize=undefined -fsanitize=address)
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
message(STATUS "include dir = ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/includes")

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(valijson REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)


add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)

install(FILES schemas/compiler_spec_schema.json DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/fcore_toolchain)
install(FILES schemas/emulator_spec_schema.json DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/fcore_toolchain)

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
