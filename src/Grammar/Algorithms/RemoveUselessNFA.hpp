#pragma once

#include "HelperFA.hpp"


namespace sb {
/// Set has to work with your states

    template<C_FA FA>
    void removeUselessNFA(FA& fa, T_FATy<FA> useless = T_FATy<FA>());

/// Realization
    template<C_FA FA>
    bool visitUseAndUseless(
        T_FAPtrSt<FA> state,
        const T_FATy<FA>& useless, 
        SetFA<FA>& visits,
        SetFA<FA>& use) 
    {
        if (visits.count(state)) { 
            return use.count(state);
        }
        visits.emplace(state);

        bool isUse = false;
        if (state->type() != useless) {
            use.emplace(state);
            isUse = true;
        }
        for(auto& trans: state->trans()) {
            bool isNextUse = visitUseAndUseless<FA>(
                trans.second,
                useless, 
                visits, 
                use
            );
            if (!isUse && isNextUse) {
                use.emplace(state);
                isUse = true;
            }
        }
        return isUse;
    }

    template<C_FA FA>
    void removeUselessNFA(FA& fa, T_FATy<FA> useless) {
        SetFA<FA> visits;
        SetFA<FA> use;
        visitUseAndUseless<FA>(fa.begin(), useless, visits, use);
        for (auto iter = fa.begin(); iter != fa.end();) {
            if (use.count(iter)) {
                ++ iter;
            } else {
                auto del = iter ++;
                fa.erase(del);
            }
        }
        if (fa.size() == 0) {
            fa.emplace_back();
        }
    }    
} // namespace sb