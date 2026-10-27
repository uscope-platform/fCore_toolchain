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

#include "emulator/v2/backend/live_capture_sink.hpp"

#include <algorithm>
#include <utility>

namespace fcore::emulator_v2 {

    live_capture_sink::live_capture_sink(uint32_t n_channels, uint32_t block_samples)
        : n_channels(n_channels), block_samples(block_samples),
          outputs(n_channels), pending_outputs(n_channels) {
        start_new_block();
    }

        void live_capture_sink::start_new_block() {
        block_being_written.n_channels = n_channels;
        block_being_written.n_samples = block_samples;
        block_being_written.samples.assign(static_cast<size_t>(n_channels) * block_samples, 0);
        block_being_written.channels.assign(n_channels, live_channel_info{});
        for (uint32_t c = 0; c < n_channels; c++) {
            if (outputs[c].has_value()) block_being_written.channels[c] = outputs[c]->info;
        }
        block_being_written.sampling_frequency = sampling_frequency;
        samples_written = 0;
    }

    result<void> live_capture_sink::select_output(uint32_t capture_channel, const output_selection &output) {
        if (capture_channel >= n_channels) {
            return fail(error_code::invalid_argument, "The capture has " + std::to_string(n_channels) + " channels, channel "
                + std::to_string(capture_channel) + " does not exist");
        }
        std::lock_guard lock(mutex);
        if (!bus_engine) return fail(error_code::invalid_argument, "The emulation is not set up, there is no output to select yet");

        for (const auto &out : bus_engine->get_outputs()) {
            if (out.core_name != output.core || out.port_name != output.name) continue;
            if (output.channel >= out.channels) {
                return fail(error_code::invalid_argument, "The output " + output.core + "." + output.name + " has "
                    + std::to_string(out.channels) + " channels, channel " + std::to_string(output.channel) + " does not exist");
            }
            if (output.index >= out.vector_size) {
                return fail(error_code::invalid_argument, "The output " + output.core + "." + output.name + " has "
                    + std::to_string(out.vector_size) + " elements, element " + std::to_string(output.index) + " does not exist");
            }
            selected_output chosen;
            chosen.selection = output;
            chosen.address = bus_engine->get_output_address(output.core, output.name, output.index);
            chosen.info = live_channel_info{true, out.metadata.type, out.metadata.width, out.metadata.is_signed};
            pending_outputs[capture_channel] = chosen;
            outputs_changed = true;
            return {};
        }
        return fail(error_code::invalid_argument, "The emulation has no output " + output.core + "." + output.name);
    }

    result<void> live_capture_sink::unselect_output(uint32_t capture_channel) {
        if (capture_channel >= n_channels) {
            return fail(error_code::invalid_argument, "The capture has " + std::to_string(n_channels) + " channels, channel "
                + std::to_string(capture_channel) + " does not exist");
        }
        std::lock_guard lock(mutex);
        pending_outputs[capture_channel].reset();
        outputs_changed = true;
        return {};
    }

    void live_capture_sink::unselect_all() {
        std::lock_guard lock(mutex);
        for (auto &o : pending_outputs) o.reset();
        outputs_changed = true;
    }

    bool live_capture_sink::wait_for_block(std::chrono::milliseconds timeout) {
        std::unique_lock lock(mutex);
        return block_ready.wait_for(lock, timeout, [this] { return has_block_ready; });
    }

    std::optional<live_block> live_capture_sink::take_block() {
        std::lock_guard lock(mutex);
        if (!has_block_ready) return std::nullopt;
        has_block_ready = false;
        return std::move(block_ready_to_take);
    }

    uint64_t live_capture_sink::dropped_blocks() const {
        std::lock_guard lock(mutex);
        return dropped;
    }

    void live_capture_sink::set_runners(const std::shared_ptr<std::map<std::string, emulator_runner>> &r) {
        runners = r;
    }

    void live_capture_sink::process_specs(const std::shared_ptr<bus_allocator> &engine) {
        std::lock_guard lock(mutex);
        bus_engine = engine;
    }

    void live_capture_sink::set_simulation_frequency(uint32_t freq) {
        sampling_frequency = freq;
        block_being_written.sampling_frequency = freq;
    }

    void live_capture_sink::apply_pending() {
        std::lock_guard lock(mutex);
        if (!outputs_changed) return;
        outputs = pending_outputs;
        outputs_changed = false;
        // a block is made of the samples of one selection only
        start_new_block();
    }

    void live_capture_sink::hand_over_block() {
        {
            std::lock_guard lock(mutex);
            if (has_block_ready) dropped++;
            block_being_written.sequence = next_sequence++;
            std::swap(block_ready_to_take, block_being_written);
            has_block_ready = true;
        }
        block_ready.notify_one();
        start_new_block();
    }

    void live_capture_sink::finish_round() {
        samples_written++;
        calls_in_round = 0;
        if (samples_written >= block_samples) hand_over_block();
    }

    result<void> live_capture_sink::process_outputs(const std::vector<core_step_metadata> &metadata, const std::string &core) {
        // the selection changes between rounds only, before any core is sampled
        if (calls_in_round == 0) apply_pending();
        for (uint32_t c = 0; c < n_channels; c++) {
            if (!outputs[c].has_value()) continue;
            const auto &chosen = outputs[c].value();
            if (!core.empty() && chosen.selection.core != core) continue;

            const auto runner = runners->find(chosen.selection.core);
            if (runner == runners->end()) return fail(error_code::invalid_argument, "Could not find core " + chosen.selection.core);
            auto value = runner->second.dma_read(chosen.address, chosen.selection.channel);
            if (!value) return fail(std::move(value).error().with_context("sampling the output " + chosen.selection.core + "." + chosen.selection.name));
            block_being_written.samples[static_cast<size_t>(c) * block_samples + samples_written] = value.value();
        }

        // every core is called once in a round: when all of them were, the round is complete
        calls_in_round = core.empty() ? static_cast<uint32_t>(metadata.size()) : calls_in_round + 1;
        if (calls_in_round >= metadata.size()) finish_round();
        return {};
    }

    void live_capture_sink::clear() {
        std::lock_guard lock(mutex);
        bus_engine.reset();
        std::fill(outputs.begin(), outputs.end(), std::nullopt);
        std::fill(pending_outputs.begin(), pending_outputs.end(), std::nullopt);
        outputs_changed = false;
        has_block_ready = false;
        calls_in_round = 0;
        start_new_block();
    }
}
