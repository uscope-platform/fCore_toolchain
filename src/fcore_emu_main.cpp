// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



#include <iostream>
#include <string>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <CLI/CLI.hpp>

#include "emulator/v2/emulator_manager.hpp"
#include "instrumentation/instrumentation_core.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore Emulator"};

    bool output_force = false;
    bool verbose_logging = false;
    bool debug_autogen = false;
    bool dump_bus = false;
    std::string inputs_file;
    std::string output_file;
    std::string spec_file;
    app.add_option("spec", spec_file , "JSON specification file path")->check(CLI::ExistingFile);
    app.add_flag("--log", verbose_logging, "Enable verbose logging.");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    app.add_flag("--debug_autogen", debug_autogen, "Write intermediate steps for autogen emulation debugging");
    app.add_flag("--dump_bus", dump_bus, "Dump the bus allocations");
    CLI11_PARSE(app, argc, argv);

    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("logger", spdlog::color_mode::automatic);

    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            spdlog::critical("The Specified output file already exists, to force the file to be rewritten use the --f flag");
            exit(-1);
        }
    }

    std::ifstream stream;

    if(spec_file.empty()){
        spdlog::critical("The provvided specifications file is empty");
        exit(-1);
    }


    if(verbose_logging){
        spdlog::set_level(spdlog::level::info);
    } else {
        spdlog::set_level(spdlog::level::critical);
    }

    nlohmann::json specs;
    std::ifstream spec_stream(spec_file);
    spec_stream >> specs;

    nlohmann::json results;

    std::shared_ptr<fcore::instrumentation_core> profiler = std::make_shared<fcore::instrumentation_core>();

    nlohmann::json profiling_data;
    try{
        fcore::emulator_v2::emulator_manager emu_manager;
        emu_manager.set_specs(specs);
        if(debug_autogen) emu_manager.enable_debug_mode();
        emu_manager.set_profiler(profiler);
        emu_manager.process();
        profiler->set_phase("emulation");
        profiler->start_event("execution", true);
        emu_manager.emulate();
        profiler->end_event("execution");
        results = emu_manager.get_results();
        profiling_data = profiler->dump();

        if(dump_bus) {
            auto bus = emu_manager.dump_bus();
            std::ofstream ss("bus.txt");
            for(auto &b: bus) {
             ss << b.first << " --- " << b.second << std::endl;
            }
            ss.close();
            exit(0);
        }
    } catch (std::runtime_error &err) {
        spdlog::critical(err.what());
        exit(-1);
    } catch (std::domain_error &err){
        spdlog::critical("Duplicate bus address detected");
        std::ofstream ss("duplicates.json");
        ss<<err.what();
        ss.close();
        exit(-1);
    }




    results["profiling"] = profiling_data;
    std::ofstream ss(output_file);
    ss<< results.dump(4);
    ss.close();


    return 0;
}