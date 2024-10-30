

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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SCHEMA_CPP_HPP
#define FCORE_TOOLCHAIN_EMULATOR_SCHEMA_CPP_HPP


#include <string>


const std::string emulator_schema = R"~(
{
  "$schema": "https://json-schema.org/draft/2019-09/schema",
  "type": "object",
  "title": "Root Schema",
  "required": [
    "cores",
    "interconnect",
    "emulation_time",
    "deployment_mode"
  ],
  "properties": {
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
          "input_data",
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
                "reg_n",
                "channel",
                "metadata",
                "source",
                "name"
              ],
              "properties": {
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
                "reg_n": {
                  "anyOf": [
                    {
                      "type": "integer",
                      "title": "IO address (or register address if remapping is not active) to push the input to"
                    },
                    {
                      "type": "array",
                      "title": "array of IO addresses (or register addresses if remapping is not active) to push the input to",
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
                      "enum": ["constant", "file", "external"],
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
                          "type": "string",
                          "value": ""
                        }
                      ]
                    },
                    "file": {
                      "anyOf": [
                        {
                          "type": "string",
                          "title": "name of the file containing the data series source"
                        },
                        {
                          "type": "array",
                          "title": "names of the files containing the data series source (one per channel)",
                          "items": {
                            "type": "string"
                          }
                        }
                      ]
                    },
                    "series": {
                      "anyOf": [
                        {
                          "type": "string",
                          "title": "name of the data series chosen"
                        },
                        {
                          "type": "array",
                          "title": "names of the data series chosen (one per channel)",
                          "items": {
                            "type": "string"
                          }
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
              }
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
                "reg_n",
                "metadata",
                "name"
              ],
              "properties": {
                "reg_n":{
                  "type": "array",
                  "title": "array register address of the vector output variable",
                  "items": {
                    "type": "integer"
                  }
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
                "reg_n",
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
                "reg_n": {
                  "anyOf": [
                    {
                      "type": "integer",
                      "title": "register address of the state variable to initialize"
                    },
                    {
                      "type": "array",
                      "title": "register address of the state variable to initialize",
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
          "input_data": {
            "type": "array",
            "title": "Array of object containing possible input data series",
            "items": {
              "type": "object",
              "title": "input series collections object",
              "required": [
                "data",
                "name"
              ],
              "data":{
                "type": "object"
              }
            }
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
          "destination",
          "channels"
        ],
        "properties": {
          "source": {
            "type": "string",
            "title": "source core id"
          },
          "destination": {
            "type": "string",
            "title": "Destination core id"
          },
          "channels": {
            "type": "array",
            "title": "Array specifying the data for each dma channel",
            "items": {
              "type": "object",
              "title": "Object that specifies the data for a single dma channel",
              "required": [
                "name",
                "source",
                "length",
                "destination",
                "type"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "scalar_transfer",
                    "scatter_transfer",
                    "vector_transfer",
                    "gather_transfer",
                    "2d_vector_transfer"
                  ]
                },
                "length": {
                  "type": "integer",
                  "title": "Size of the vector transfer"
                },
                "stride": {
                  "type": "integer",
                  "title": "Second dimension for the 2d vector transfer"
                },
                "name": {
                  "type": "string",
                  "title": "Name of the connection"
                },
                "source": {
                  "type": "object",
                  "default": [],
                  "title": "array that specifies the channel and address of the source data",
                  "items": {
                    "type": "object",
                    "title": "Object describing the source",
                    "required": [
                      "register",
                      "channel"
                    ],
                    "properties": {
                      "channel": {
                        "type": "integer",
                        "title": "Number of the source channel"
                      },
                      "register": {
                        "type": "integer",
                        "title": "Address of the source register"
                      }
                    }
                  }
                },
                "destination": {
                  "type": "object",
                  "default": [],
                  "title": "array that specifies the channel and address of the destination data",
                  "items": {
                    "type": "object",
                    "title": "Object describing the destination",
                    "required": [
                      "register",
                      "channel"
                    ],
                    "properties": {
                      "channel": {
                        "type": "integer",
                        "title": "Number of the destination channel"
                      },
                      "register": {
                        "type": "integer",
                        "title": "Address of the destination register"
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    },
    "emulation_time": {
      "type": "number",
      "title": "Length of time to emulate"
    },
    "deployment_mode": {
      "type": "boolean",
      "title": "Enable custom image deployment mode"
    }
  }
}
)~";


#endif //FCORE_TOOLCHAIN_EMULATOR_SCHEMA_CPP_HPP
