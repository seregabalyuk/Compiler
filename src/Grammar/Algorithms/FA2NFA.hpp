#pragma once

#include "HelperFA.hpp"

namespace sb {
    template<C_NFA NFA, C_cFA FA>
    NFA& fa2nfa(const FA& fa, NFA& nfa) {
        for (auto state: fa) {
            nfa.emplace_back(state.type());
        }

        std::map<
            T_FAPtrCSt<FA>,
            T_FAPtrSt<NFA>,
            CompIter
        > o2t;
        {
            auto st_fa = fa.begin();
            auto st_nfa = nfa.begin();
            
            while (st_fa != fa.end()) {
                o2t.emplace(st_fa ++, st_nfa ++);
            }
        }

        for (auto  st_fa = fa.begin(); st_fa != fa.end(); ++ st_fa) {
            auto st_nfa = o2t[st_fa];
            for (auto& trans: st_fa->trans()) {
                st_nfa->emplace(trans.first, o2t[trans.second]);
            }
        }
        return nfa;
    }
} // namespace sb