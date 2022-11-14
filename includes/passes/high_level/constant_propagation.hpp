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
// limitations under the License.05/07/2021.
//

#ifndef FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
#define FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP

#include <unordered_map>
#include <unordered_set>

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/variable_map.hpp"

class constant_propagation :public pass_base<hl_ast_node> {
public:
    explicit constant_propagation();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;

    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::shared_ptr<hl_ast_node> substitute_constant(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_node> substitute_constant(std::shared_ptr<hl_expression_node> element);
    std::shared_ptr<hl_ast_node> substitute_constant(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_ast_operand> substitute_constant(std::shared_ptr<hl_ast_operand> element);

    bool map_constants(std::shared_ptr<hl_ast_node> element);
    bool map_constants(std::shared_ptr<hl_expression_node> element);
    bool map_constants(std::shared_ptr<hl_definition_node> element);

    void map_assignments(std::shared_ptr<hl_ast_node> element);


    class constant_tracker{
    public:
        void add_constant(const std::string& s, std::shared_ptr<hl_ast_operand> op) {constants_map[s] = std::move(op);};
        void add_exclusion(const std::string& s) {excluded_constants.insert(s);};
        bool is_constant(const std::string& s){return constants_map.contains(s);};
        bool is_excluded(const std::string& s){return excluded_constants.contains(s);};
        std::shared_ptr<hl_ast_operand> get_constant(const std::string& s){return constants_map[s];};
        void clear(){
            constants_map.clear();
            excluded_constants.clear();
        };

    private:
        std::unordered_map<std::string, std::shared_ptr<hl_ast_operand>> constants_map;
        std::unordered_set<std::string> excluded_constants;
    };

    constant_tracker tracker;

};


#endif //FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
