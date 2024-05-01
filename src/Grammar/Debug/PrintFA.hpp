#pragma once

#include <map>

#include <Base/Classes/CompareIterators.hpp>

#include "../Classes/Requirements/FA.hpp"

namespace sb {
    template<class OUT, C_cFA FA>
    OUT& printFA(OUT& out, const FA& fa) {
        std::map<
            T_FAPtrCSt<FA>, 
            size_t,
            CompIter
        > ptr2num;
        size_t count = 0;
        for (auto iter = fa.begin(); iter != fa.end(); ++ iter) {
            ptr2num[iter] = count ++;
        }
        count = 0;
        for (auto& state: fa) {
            out << count << "," << state.type() << ":";
            for (auto& [letter, next]: state.trans()) {
                out << letter << ">" << ptr2num[next] << ", ";
            }
            out << "\n";
        }
        return out;
    }
} // namespace sb