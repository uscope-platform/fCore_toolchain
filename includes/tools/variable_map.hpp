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

#ifndef FCORE_TOOLCHAIN_VARIABLE_MAP_HPP
#define FCORE_TOOLCHAIN_VARIABLE_MAP_HPP

#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <iterator>
#include <utility>
#include <cmath>
#include "data_structures/common/variable.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"

namespace fcore {

    class variable_map {
    public:
        variable_map();
        std::shared_ptr<variable> operator[](const std::string& key);
        std::shared_ptr<variable> at(const std::string& key);
        void insert(const std::string& key, std::shared_ptr<variable>item);
        unsigned int count(const std::string& key);
        unsigned int size();

        unsigned int n_inputs() const {return n_inputs_;};
        unsigned int n_outputs() const {return n_outputs_;};
        unsigned int n_variables() const {return n_variables_;};
        friend bool operator==(const variable_map& lhs, const variable_map& rhs) {
            bool retval = true;

            retval &= lhs.n_inputs_ == rhs.n_inputs_;
            retval &= lhs.n_outputs_ == rhs.n_outputs_;
            retval &= lhs.n_variables_ == rhs.n_variables_;

            for(auto &i: lhs.map){
                if(rhs.map.count(i.first)){
                    retval &= *rhs.map.at(i.first) == *lhs.map.at(i.first);
                } else{
                    retval &= false;
                }

            }
            for(auto &i: rhs.map){
                if(lhs.map.count(i.first)){
                    retval &= *rhs.map.at(i.first) == *lhs.map.at(i.first);
                } else{
                    retval &= false;
                }
            }
            return retval;
        };

        std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> begin() {return map.begin();}
        std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> begin() const { return map.begin();}
        std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> end() {return map.end();}
        std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> end() const { return map.end();}

    private:
        unsigned int n_inputs_ = 0;
        unsigned int n_outputs_ = 0;
        unsigned int n_variables_ = 0;
        std::unordered_map<std::string, std::shared_ptr<variable>> map;
    };
}


#endif //FCORE_TOOLCHAIN_VARIABLE_MAP_HPP
