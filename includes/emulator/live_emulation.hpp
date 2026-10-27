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

#ifndef FCORE_TOOLCHAIN_LIVE_EMULATION_HPP
#define FCORE_TOOLCHAIN_LIVE_EMULATION_HPP

#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include <thread>

#include <nlohmann/json.hpp>

#include "emulator/emulator_dispatcher.hpp"
#include "emulator/v2/backend/live_capture_sink.hpp"
#include "errors/result.hpp"

namespace fcore {

    /// An emulation that runs on its own thread, like the hardware does, and is observed through the blocks of a
    /// capture. It runs flat out: whoever takes the blocks does not slow it down, a block that is not taken in time
    /// is lost (see live_capture_sink).
    ///
    /// load, start, stop and the destructor are for the thread that owns the emulation. The other calls can be made
    /// from any thread, while the emulation runs.
    class live_emulation {
    public:
        /// \param n_channels the channels of the capture
        /// \param block_samples the samples of a channel in a block
        live_emulation(uint32_t n_channels, uint32_t block_samples);
        ~live_emulation();
        live_emulation(const live_emulation &) = delete;
        live_emulation &operator=(const live_emulation &) = delete;

        /// Sets up the emulation, stopping the one that is running. The outputs of the capture have to be selected
        /// again after it.
        [[nodiscard]] result<void> load(const nlohmann::json &specs);
        /// Runs the emulation, from where it was stopped
        [[nodiscard]] result<void> start();
        void stop();
        bool running() const { return is_running; }
        /// The error that stopped the emulation, if one did
        std::optional<error> get_error() const;

        /// Sets a constant input of a core. It takes effect within a few rounds.
        [[nodiscard]] result<void> set_input(const std::string &core, const std::string &name, uint32_t channel, double value);
        [[nodiscard]] result<void> select_output(uint32_t capture_channel, const emulator_v2::output_selection &output);
        [[nodiscard]] result<void> unselect_output(uint32_t capture_channel);

        bool wait_for_block(std::chrono::milliseconds timeout);
        std::optional<emulator_v2::live_block> take_block();
        uint64_t dropped_blocks() const;
        /// The samples per second of the time of the emulation: it does not run at that speed.
        uint32_t get_sampling_frequency() const;

    private:
        void run(std::stop_token stop);

        std::shared_ptr<emulator_v2::live_capture_sink> sink;
        emulator_dispatcher dispatcher;
        std::jthread worker;
        bool loaded = false;
        std::atomic<bool> is_running = false;

        // what can be set, from the specs that were loaded
        struct core_inputs {
            uint32_t channels = 0;
            std::set<std::string> constants;
            std::set<std::string> others;
        };
        std::map<std::string, core_inputs> inputs_of_cores;

        mutable std::mutex failure_mutex;
        std::optional<error> failure;
    };
}

#endif //FCORE_TOOLCHAIN_LIVE_EMULATION_HPP
