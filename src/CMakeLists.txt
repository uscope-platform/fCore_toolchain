set(FCORE_LIB_SRCS code_elements/instruction.cpp
        frontend/asm/Tree_visitor.cpp
        frontend/asm/file_parser.cpp
        backend/output_generator.cpp
        code_elements/code_element.cpp
        passes/pass_manager.cpp
        passes/loop_implementation_pass.cpp
        code_elements/for_loop.cpp
        passes/pseudo_instructions_pass.cpp
        passes/instruction_counting_pass.cpp
        code_elements/variable.cpp
        passes/register_allocation_pass.cpp
        frontend/variable_map.cpp
        passes/variable_lifetime_mapping.cpp
        frontend/asm/register_map.cpp
        passes/load_intercalation_pass.cpp
        fcore_has.cpp
        frontend/asm/ErrorHandling.cpp
        frontend/C/file_parser.cpp )

add_library(fCore_lib_internal ${FCORE_LIB_SRCS})

target_link_libraries(fCore_lib_internal asm_parser_lib)
target_link_libraries(fCore_lib_internal c_parser)

add_executable(fCore_has main.cpp)
target_link_libraries(fCore_has fCore_lib_internal)

#make shared library for use with uscope server


add_library(fchas SHARED ${FCORE_LIB_SRCS})
target_link_libraries(fchas asm_parser_libs)
set_property(TARGET fchas PROPERTY POSITION_INDEPENDENT_CODE 1)

install(TARGETS fchas
        LIBRARY DESTINATION /usr/local/lib/fcore_has)

install(DIRECTORY ../includes/fcore_has # source directory
        DESTINATION /usr/local/include # target directory
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
        )

if(NOT ${PY_MODULE_EXCLUDE})
    add_definitions(-DPYTHON_MODULE)
    pybind11_add_module(fCore_has_py  ${FCORE_LIB_SRCS})
    target_link_libraries(fCore_has_py PRIVATE asm_parser_libs)
    target_link_libraries(fCore_has_py PRIVATE antlr4-runtime)
endif(NOT ${PY_MODULE_EXCLUDE})
