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

#ifndef FCORE_TOOLCHAIN_PASS_BASE_HPP
#define FCORE_TOOLCHAIN_PASS_BASE_HPP

#include <memory>
#include <utility>
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include "errors/result.hpp"
#include "data_structures/high_level_ast/ast_code_block.hpp"

namespace fcore{

    class ast_definition;

    typedef result<std::shared_ptr<ast_code_block>> pass_result;

    class pass_base {
    public:
        virtual ~pass_base() = default;

        explicit pass_base(std::string n) {
            name = std::move(n);
            n_passes = 1;
        };

        virtual pass_result process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) {
            return element;
        };
        std::string get_name() {return name;};
    protected:
        /// Records a failure found inside a visitor callback, which can not return it. Only the first one is kept.
        void report(error e) {
            if(!failure) failure = std::move(e);
        }
        [[nodiscard]] bool failed() const {return failure.has_value();}

        /// Condition to hand to the visitors so that they stop as soon as a callback reported a failure
        [[nodiscard]] std::function<bool()> stop_condition() const {
            return [this]{return failed();};
        }

        /// The tree if nothing was reported, otherwise the reported failure. Clears the failure for the next run.
        pass_result finish(const std::shared_ptr<ast_code_block> &tree) {
            if(failure) return fail_with_reported();
            return tree;
        }

        /// Same as above for passes built on the acting visitor, a failure of the visitor itself wins
        pass_result finish(pass_result visited) {
            if(!visited){
                failure.reset();
                return visited;
            }
            if(failure) return fail_with_reported();
            return visited;
        }

        /// Same as above for passes built on the observing visitor, that does not produce a tree
        pass_result finish(const result<void> &visited, const std::shared_ptr<ast_code_block> &tree) {
            if(!visited){
                failure.reset();
                return fail(visited.error());
            }
            return finish(tree);
        }
    private:
        std::unexpected<error> fail_with_reported() {
            error reported = std::move(failure).value();
            failure.reset();
            return fail(std::move(reported));
        }
        std::optional<error> failure;
        std::string name;
        uint8_t n_passes;
    };
}

#endif //FCORE_TOOLCHAIN_PASS_BASE_HPP
