//   Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include "emulator/live_emulation.hpp"

namespace fcore {

    live_emulation::live_emulation(uint32_t n_channels, uint32_t block_samples)
        : sink(std::make_shared<emulator_v2::live_capture_sink>(n_channels, block_samples)) {}

    live_emulation::~live_emulation() {
        stop();
    }

    result<void> live_emulation::load(const nlohmann::json &specs) {
        stop();
        loaded = false;
        if(auto set = dispatcher.set_output_sink(sink); !set) return set;
        if(auto set = dispatcher.set_specs(specs); !set) return set;
        if(auto processed = dispatcher.process(); !processed) return processed;
        if(auto started = dispatcher.start_live(); !started) return started;

        inputs_of_cores.clear();
        for(const auto &core: specs["cores"]) {
            auto &inputs = inputs_of_cores[core["id"]];
            inputs.channels = core["channels"];
            for(const auto &in: core["inputs"]) {
                const bool scalar_constant = in["source"]["type"] == "constant" && !in["is_vector"];
                (scalar_constant ? inputs.constants : inputs.others).insert(in["name"]);
            }
        }
        loaded = true;
        return {};
    }

    result<void> live_emulation::start() {
        if(!loaded) return fail(error_code::invalid_argument, "There is no emulation to run, load one first");
        if(is_running) return {};
        // the thread of an emulation that stopped on its own is still to be joined
        stop();
        {
            std::lock_guard lock(failure_mutex);
            failure.reset();
        }
        is_running = true;
        worker = std::jthread([this](std::stop_token stop_request) { run(stop_request); });
        return {};
    }

    void live_emulation::stop() {
        if(worker.joinable()) {
            worker.request_stop();
            worker.join();
        }
    }

    void live_emulation::run(std::stop_token stop_request) {
        if(auto ran = dispatcher.run_live(stop_request); !ran) {
            std::lock_guard lock(failure_mutex);
            failure = ran.error();
        }
        is_running = false;
    }

    std::optional<error> live_emulation::get_error() const {
        std::lock_guard lock(failure_mutex);
        return failure;
    }

    result<void> live_emulation::set_input(const std::string &core, const std::string &name, uint32_t channel, double value) {
        if(!loaded) return fail(error_code::invalid_argument, "There is no emulation loaded");
        const auto inputs = inputs_of_cores.find(core);
        if(inputs == inputs_of_cores.end()) return fail(error_code::invalid_argument, "The emulation has no core " + core);
        if(inputs->second.others.contains(name)) {
            return fail(error_code::invalid_argument, "The input " + core + "." + name + " is not a constant, it can not be set while the emulation runs");
        }
        if(!inputs->second.constants.contains(name)) return fail(error_code::invalid_argument, "The core " + core + " has no input " + name);
        if(channel >= inputs->second.channels) {
            return fail(error_code::invalid_argument, "The core " + core + " has " + std::to_string(inputs->second.channels)
                + " channels, channel " + std::to_string(channel) + " does not exist");
        }
        sink->set_input(core, name, channel, value);
        return {};
    }

    result<void> live_emulation::select_output(uint32_t capture_channel, const emulator_v2::output_selection &output) {
        return sink->select_output(capture_channel, output);
    }

    result<void> live_emulation::unselect_output(uint32_t capture_channel) {
        return sink->unselect_output(capture_channel);
    }

    bool live_emulation::wait_for_block(std::chrono::milliseconds timeout) {
        return sink->wait_for_block(timeout);
    }

    std::optional<emulator_v2::live_block> live_emulation::take_block() {
        return sink->take_block();
    }

    uint64_t live_emulation::dropped_blocks() const {
        return sink->dropped_blocks();
    }

    uint32_t live_emulation::get_sampling_frequency() const {
        return sink->get_sampling_frequency();
    }
}
