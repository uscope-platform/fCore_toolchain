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

#ifndef FCORE_TOOLCHAIN_LIVE_CAPTURE_SINK_V2_HPP
#define FCORE_TOOLCHAIN_LIVE_CAPTURE_SINK_V2_HPP

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "emulator/v2/backend/output_sink.hpp"

namespace fcore::emulator_v2 {

    /// An output of a core, to be sampled into a channel of the capture
    struct output_selection {
        std::string core;
        std::string name;
        /// the channel of the core
        uint32_t channel = 0;
        /// the element, for the outputs that are vectors
        uint32_t index = 0;
    };

    /// What the samples of a channel are, so that whoever consumes the block can interpret the raw words
    struct live_channel_info {
        bool selected = false;
        register_data_type type = type_uint;
        uint16_t width = 32;
        bool is_signed = false;
    };

    /// A full capture: the raw 32 bit words of the outputs, the samples of a channel are together
    struct live_block {
        uint32_t n_channels = 0;
        uint32_t n_samples = 0;
        /// samples[channel * n_samples + i], zero for the channels that have no output selected
        std::vector<uint32_t> samples;
        std::vector<live_channel_info> channels;
        uint32_t sampling_frequency = 0;
        /// increments for every block that is produced, a gap means that blocks were not taken in time
        uint64_t sequence = 0;
    };

    /// Samples the selected outputs after every round into a buffer and hands it over when it is full, like the
    /// scope of the hardware does. Two buffers: one is being filled while the other one waits to be taken, they swap
    /// when the one that is filling is complete. The emulation never waits for who takes the blocks, a block that was
    /// not taken before the next one is complete is lost.
    ///
    /// The samples are taken at the same point of the round as the batch emulation records its outputs.
    /// select_output, unselect_output, unselect_all, wait_for_block and take_block can be called from any thread, the
    /// rest is for the emulation.
    class live_capture_sink : public output_sink {
    public:
        live_capture_sink(uint32_t n_channels, uint32_t block_samples);

        /// Samples the output into the channel of the capture. It takes effect at the next round and starts a new block,
        /// so a block never mixes the old and the new output. Fails if the output is not one of the emulation.
        [[nodiscard]] result<void> select_output(uint32_t capture_channel, const output_selection &output);
        [[nodiscard]] result<void> unselect_output(uint32_t capture_channel);
        void unselect_all();

        /// \return true if a block is waiting to be taken
        bool wait_for_block(std::chrono::milliseconds timeout);
        /// \return the block that is waiting, if any: it is taken, so it is returned once
        std::optional<live_block> take_block();
        /// The blocks that were complete and replaced by the next one before they were taken
        uint64_t dropped_blocks() const;

        void set_runners(const std::shared_ptr<std::map<std::string, emulator_runner>> &r) override;
        void process_specs(const std::shared_ptr<bus_allocator> &engine) override;
        void set_initial_values(const std::map<std::string, std::map<std::string, std::vector<uint32_t>>> &) override {}
        void set_simulation_frequency(uint32_t freq) override;
        [[nodiscard]] result<void> process_outputs(
            const std::vector<core_step_metadata> &metadata,
            const std::string &core
        ) override;
        void clear() override;

    private:
        struct selected_output {
            output_selection selection;
            uint32_t address = 0;
            live_channel_info info;
        };

        void apply_pending();
        void finish_round();
        void start_new_block();
        void hand_over_block();

        const uint32_t n_channels;
        const uint32_t block_samples;

        std::shared_ptr<std::map<std::string, emulator_runner>> runners;
        std::shared_ptr<bus_allocator> bus_engine;
        uint32_t sampling_frequency = 0;

        // the part that is only touched by the emulation
        std::vector<std::optional<selected_output>> outputs;
        live_block block_being_written;
        uint32_t samples_written = 0;
        uint32_t calls_in_round = 0;

        // the part that is shared, guarded by the mutex
        mutable std::mutex mutex;
        std::condition_variable block_ready;
        std::vector<std::optional<selected_output>> pending_outputs;
        bool outputs_changed = false;
        live_block block_ready_to_take;
        bool has_block_ready = false;
        uint64_t next_sequence = 0;
        uint64_t dropped = 0;
    };
}

#endif //FCORE_TOOLCHAIN_LIVE_CAPTURE_SINK_V2_HPP
