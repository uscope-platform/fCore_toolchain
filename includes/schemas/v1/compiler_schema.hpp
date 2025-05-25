

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_COMPILER_SCHEMA_HPP
#define FCORE_TOOLCHAIN_COMPILER_SCHEMA_HPP


#include <string>


constexpr std::string_view compiler_schema_v1 = R"~(
{
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "title": "Root Schema",
    "required": [
        "input_file",
        "output"
    ],
    "properties": {
        "input_file": {
            "type": "string",
            "title": "Path of the input file"
        },
        "output": {
            "type": "object",
            "title": "Object that specifies the compiler output",
            "required": [
                "format",
                "file"
                ],
            "properties": {
                "format": {
                    "type": "string",
                    "enum": ["mem", "hex", "json"],
                    "title": "Format of the output file"
                },
                "file": {
                    "type": "string",
                    "title": "Name of the output file to produce"
                }
            }
        },
        "dump_ast": {
            "type": "integer",
            "title": "Specify whether and how much the AST should be dumped during compilation"
        },
        "force": {
            "type": "boolean",
            "title": "Force overwriting of existing output products"
        },
        "dma_io": {
            "type": "object",
            "title": "Object associating dma Inputs and outputs with the relevant io space register",
            "additionalProperties": {
                "type": "object",
                "title":"Object describing Inputs and outputs of a femtocore program",
                "required": [
                    "type",
                    "address",
                    "common_io"
                ],
                "properties": {
                    "type": {
                        "type": "string",
                        "title": "Direction of the DMA variable"
                    },
                    "address": {
                        "type": [
                            "array",
                            "integer"
                        ],
                        "title": "Address for the relevant DMA variable",
                        "items": {
                            "type": "integer",
                            "title": "Address for a single scalar DMA variable or vector element"
                        }
                    },
                    "common_io":{
                        "type": "boolean",
                        "title": "Flag specifying if the common_io address space should be used forthis IO"
                    }
                }
            }
        },
        "header": {
            "title": "Paths of header files to include in the current file",
            "type": "array",
            "items": {
                "type": "string",
                "title": "Include File path"
            }
        }
    }
}
)~";


#endif //FCORE_TOOLCHAIN_COMPILER_SCHEMA_HPP
