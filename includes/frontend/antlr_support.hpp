// Copyright 2025 Filippo Savi <filssavi@gmail.com>
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


#ifndef FCORE_TOOLCHAIN_ANTLR_SUPPORT_HPP
#define FCORE_TOOLCHAIN_ANTLR_SUPPORT_HPP

#include <functional>
#include <utility>
#include <vector>

#include "antlr4-runtime.h"
#include "support/Casts.h"

#include "errors/result.hpp"

namespace fcore {

    /// Parser error listener that records the syntax errors instead of throwing them out of the parser.
    /// ANTLR recovers on its own, check status() once the parse is done and before walking the tree.
    class syntax_error_collector : public antlr4::BaseErrorListener {
    public:
        void syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t line, size_t column,
                         const std::string &msg, std::exception_ptr) override {
            errors_.push_back(error(error_code::parse_error, msg).at(line, column + 1));
        }

        [[nodiscard]] bool has_errors() const { return !errors_.empty(); }
        [[nodiscard]] const std::vector<error> &errors() const { return errors_; }

        /// The first syntax error, annotated with how many others were found.
        [[nodiscard]] result<void> status() const {
            if (errors_.empty()) return {};
            error first = errors_.front();
            if (errors_.size() > 1) {
                first.with_context("parsing, " + std::to_string(errors_.size() - 1) + " more syntax error(s) found");
            }
            return fail(std::move(first));
        }

    private:
        std::vector<error> errors_;
    };

    /// Iterative parse tree walker that can be interrupted: it stops as soon as should_stop() returns true after a
    /// listener callback. ANTLR walkers have no other way to abort a walk than throwing from the listener.
    class stoppable_tree_walker : public antlr4::tree::ParseTreeWalker {
    public:
        explicit stoppable_tree_walker(std::function<bool()> should_stop) : should_stop(std::move(should_stop)) {}

        void walk(antlr4::tree::ParseTreeListener *listener, antlr4::tree::ParseTree *t) const override {
            using namespace antlr4::tree;
            std::vector<std::pair<ParseTree *, size_t>> stack;
            ParseTree *current = t;
            size_t index = 0;

            while (current != nullptr) {
                if (ErrorNode::is(*current)) {
                    listener->visitErrorNode(antlrcpp::downCast<ErrorNode *>(current));
                } else if (TerminalNode::is(*current)) {
                    listener->visitTerminal(antlrcpp::downCast<TerminalNode *>(current));
                } else {
                    enterRule(listener, current);
                }
                if (should_stop()) return;

                if (!current->children.empty()) {
                    stack.emplace_back(current, index);
                    index = 0;
                    current = current->children[0];
                    continue;
                }

                do {
                    if (!TerminalNode::is(*current)) {
                        exitRule(listener, current);
                        if (should_stop()) return;
                    }

                    if (stack.empty()) {
                        current = nullptr;
                        index = 0;
                        break;
                    }

                    if (stack.back().first->children.size() > ++index) {
                        current = stack.back().first->children[index];
                        break;
                    }

                    std::tie(current, index) = stack.back();
                    stack.pop_back();
                } while (current != nullptr);
            }
        }

    private:
        std::function<bool()> should_stop;
    };

}

#endif //FCORE_TOOLCHAIN_ANTLR_SUPPORT_HPP
