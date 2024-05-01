#pragma once

#include "HelperFA.hpp"

namespace sb {
/// Set has to work with your states

    template<C_FA FA>
    void removeEpsNFA(FA& fa, T_FALe<FA> eps = T_FALe<FA>());

/// Realization
    template<C_FA FA>
    void findEps(
        T_FAPtrSt<FA> state, 
        T_FALe<FA> eps, 
        SetFA<FA>& visits
    ) {
        if (visits.count(state)) { return; }
        visits.emplace(state);

        for(auto& trans: state->trans()) {
            if (trans.first == eps) {
                findEps<FA>(trans.second, eps, visits);
            }
        }
    }

    template<C_FA FA>
    void visitAll(
        T_FAPtrSt<FA> state,
        T_FALe<FA> eps,
        SetFA<FA>& visits
    ) {
        if (visits.count(state)) { return; }
        visits.emplace(state);

        SetFA<FA> epsmates;
        findEps<FA>(state, eps, epsmates);
        epsmates.erase(state);
    
        for (auto& mate: epsmates) {
            state->type() |= mate->type();
            for(auto& trans: mate->trans()) {
                state->emplace(trans.first, trans.second);
            }
        }

        for(auto& trans: state->trans()) {
            visitAll<FA>(trans.second, eps, visits);
        }
    }

    template<C_FA FA>
    void removeEpsNFA(FA& fa, T_FALe<FA> eps) {
        SetFA<FA> visits;
        visitAll<FA>(fa.begin(), eps, visits);
        for (auto& state: visits) {
            state->erase(eps);
        }
    }

    
} // namespace sb