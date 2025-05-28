

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP


#include <string>


const std::string emulator_schema_v2 = R"~(
{
  "$schema": "https://json-schema.org/draft/2019-09/schema",
  "type": "object",
  "title": "Root Schema",
  "required": [
    "version",
    "cores",
    "interconnect",
    "emulation_time",
    "deployment_mode"
  ],
  "properties": {
    "version":{
      "type": "integer",
      "title": "input file schema version"
    },
    "cores": {
      "type": "array",
      "title": "Array of core objects describing one or more cores in a multicore cluster",
      "items": {
        "type": "object",
        "title": "Object describing a core to emulate",
        "required": [
          "id",
          "order",
          "program",
          "channels",
          "options",
          "sampling_frequency",
          "deployment"
        ],
        "properties": {
          "id": {
            "type": "string",
            "title": "Identification string of the core"
          },
          "channels": {
            "type": "integer",
            "title": "number of channels active on this core"
          },
          "order": {
            "type": "integer",
            "title": "Field indicating the order in which cores must be run in a multicore emulation session"
          },
          "sampling_frequency": {
            "type": "integer",
            "title": "Sampling frequency for the core. "
          },
          "options": {
            "type": "object",
            "default": {},
            "title": "Core behaviour configuration options",
            "required": [
              "comparators"
            ],
            "properties": {
              "comparators": {
                "type": "string",
                "title": "Type of comparator implementation implemented for this core"
              },
              "efi_implementation": {
                "type": "string",
                "title": "EFI implementation selector"
              }
            }
          },
          "inputs": {
            "type": "array",
            "default": [],
            "title": "Array of objects that specify the external inputs to the core",
            "items": {
              "type": "object",
              "title": "Object describing a single external input",
              "required": [
                "channel",
                "metadata",
                "source",
                "name",
                "type"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "scalar",
                    "vector"
                  ],
                  "title": "type of input"
                },
                "array_size": {
                  "type": "integer",
                  "title": "size of the array port"
                },
                "channel": {
                  "anyOf": [
                    {
                      "type": "integer",
                      "title": "Channel to push the input to"
                    },
                    {
                      "type": "array",
                      "title": "Channels to push the input to",
                      "items": {
                        "type": "integer"
                      }
                    }
                  ]
                },
                "metadata": {
                  "type": "object",
                  "title": "Object describing the raw data format on the wire",
                  "required": [
                    "type",
                    "width",
                    "signed",
                    "common_io"
                  ],
                  "properties": {
                    "type": {
                      "type": "string",
                      "enum": [
                        "float",
                        "integer"
                      ],
                      "title": "type to use for the output"
                    },
                    "width": {
                      "type": "integer",
                      "title": "Size of the data on the wire"
                    },
                    "signed": {
                      "type": "boolean",
                      "title": "flag indicating whether the data is signed"
                    },
                    "common_io": {
                      "type": "boolean",
                      "title":"Flag specifying if the common_io address space should be used for this IO"
                    }
                  }
                },
                "name": {
                  "type": "string",
                  "title": "Name of this input (tied to the CSV column title)"
                },
                "source": {
                  "type": "object",
                  "title": "Object describing a single external input",
                  "required": [
                    "type"
                  ],
                  "properties": {
                    "type": {
                      "type": "string",
                      "enum": ["constant", "series", "external"],
                      "title": "Type of source"
                    },
                    "value": {
                      "anyOf": [
                        {
                          "type": "number",
                          "title": "Constant to be used as input"
                        },
                        {
                          "type": "array",
                          "title": "Constants to be used as input",
                          "items": {
                            "type": "number"
                          }
                        },
                        {
                          "type": "array",
                          "title": "Constants to be used as input",
                          "items": {
                            "type": "array"
                          }
                        },
                        {
                          "type": "string",
                          "value": ""
                        }
                      ]
                    }
                  },
                  "allOf": [
                    {
                      "if": {"properties": {"type": { "enum": ["constant"] }}},
                      "then": { "required": ["value"] }
                    },
                    {
                      "if": {"properties": {"type": { "enum": ["file"] }}},
                      "then": { "required": ["series", "file"] }
                    }
                  ]
                }
              },
              "allOf": [
                {
                  "if": {"properties": {"type": { "enum": ["vector"] }}},
                  "then": { "required": ["array_size"] }
                }
              ]
            }
          },
          "outputs": {
            "type": "array",
            "default": [],
            "title": "Array of objects that specify the emulation outputs from the core",
            "items": {
              "type": "object",
              "title": "Object describing a single emulation output",
              "required": [
                "type",
                "metadata",
                "name"
              ],
              "properties": {
                "metadata": {
                  "type": "object",
                  "title": "Object describing the raw data format on the wire",
                  "required": [
                    "type",
                    "width",
                    "signed",
                    "common_io"
                  ],
                  "properties": {
                    "type": {
                      "type": "string",
                      "enum": [
                        "float",
                        "integer"
                      ],
                      "title": "type to use for the output"
                    },
                    "width": {
                      "type": "integer",
                      "title": "Size of the data on the wire"
                    },
                    "signed": {
                      "type": "boolean",
                      "title": "flag indicating whether the data is signed"
                    },
                    "common_io": {
                      "type": "boolean",
                      "title": "flag indicating whether the data is in common io"
                    }
                  }
                },
                "name": {
                  "type": "string",
                  "title": "Name to give to this output"
                }
              }
            }
          },
          "memory_init": {
            "type": "array",
            "default": [],
            "title": "Array of objects that specify the initial values for state variables",
            "items": {
              "type": "object",
              "title": "Object describing the initial value for a single state variable",
              "required": [
                "value",
                "metadata",
                "name"
              ],
              "properties": {
                "value": {
                  "anyOf": [
                    {
                      "type": "number",
                      "title": "register address of the state variable to initialize"
                    },
                    {
                      "type": "array",
                      "title": "register address of the state variable to initialize",
                      "items": {
                        "type": "number"
                      }
                    }
                  ]
                },
                "metadata": {
                  "type": "object",
                  "title": "Object describing the raw data format on the wire",
                  "required": [
                    "type",
                    "width",
                    "signed"
                  ],
                  "properties": {
                    "type": {
                      "type": "string",
                      "enum": [
                        "float",
                        "integer"
                      ],
                      "title": "type to use for the output"
                    },
                    "width": {
                      "type": "integer",
                      "title": "Size of the data on the wire"
                    },
                    "signed": {
                      "type": "boolean",
                      "title": "flag indicating whether the data is signed"
                    }
                  }
                },
                "name": {
                  "type": "string",
                  "title": "Name of the state variable (For documentation purposes only, not used internally)"
                }
              }
            }
          },
          "program": {
            "type": "object",
            "title": "Description of the program to run on this core",
            "properties": {
              "headers": {
                "type": "array",
                "title": "array of strings containing the headers to be included",
                "items": {
                  "type": "string",
                  "title": "single header content"
                }
              },
              "content": {
                "type": "string",
                "title": "source code of the selected program"
              },
              "type":{
                "type": "string",
                "enum": ["c", "asm"]
              },
              "io": {
                "type": "object",
                "title": "Object listing input, output and memories for the program",
                "properties": {
                  "inputs": {
                    "type": "array",
                    "default": [],
                    "title": "List of program inputs",
                    "items": {
                      "type": "string"
                    }
                  },
                  "outputs": {
                    "type": "array",
                    "default": [],
                    "title": "List of program Outputs",
                    "items": {
                      "type": "string"
                    }
                  },
                  "memories": {
                    "type": "array",
                    "default": [],
                    "title": "List of program memories",
                    "items": {
                      "type": "string"
                    }
                  }
                }
              }
            },
            "required": [
              "content",
              "headers",
              "build_settings"
            ]
          },
          "deployment": {
            "title": "options for custom deployment",
            "type": "object",
            "properties": {
              "rom_address":{
                "type": "number",
                "title": "Address of the target core complex ROM bus"
              },
              "control_address": {
                "type": "number",
                "title": "Address of the target core complex control bus"
              },
              "has_reciprocal": {
                "type": "boolean",
                "title": "Flag indicating the implementation of reciprocal operation in correspondent core"
              }
            },
            "required": [
              "control_address",
              "rom_address",
              "has_reciprocal"
            ]
          }
        }
      }
    },
    "interconnect": {
      "type": "array",
      "title": "Array of object describing how the cores should be connected",
      "items": {
        "type": "object",
        "title": "Object describing the connection between two cores",
        "required": [
          "source",
          "destination"
        ],
        "properties": {
          "source":  {
            "type": "string",
            "title": "source endpoint id"
          },
          "destination":  {
            "type": "string",
            "title": "source endpoint id"
          }
        }
      }
    },
    "emulation_time": {
      "type": "number",
      "title": "Length of time to emulation_phase"
    },
    "deployment_mode": {
      "type": "boolean",
      "title": "Enable custom image deployment mode"
    }
  }
}
)~";


#endif //FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP
