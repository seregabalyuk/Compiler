#pragma once

#include "RemoveEpsNFA.hpp"
#include "DetermineNFA.hpp"
#include "RemoveUselessNFA.hpp"
#include "MinimizeDFA.hpp"

namespace sb {
    template<C_DFA DFA, C_FA NFA>
    DFA nfa2dfa(NFA& nfa,
        T_FALe<NFA> eps = T_FALe<NFA>(), 
        T_FATy<NFA> useless = T_FATy<NFA>()) 
    {
        removeEpsNFA(nfa, eps);
        removeUselessNFA(nfa, useless);
        DFA dfa = determineNFA<DFA>(nfa);
        return minimizeDFA<DFA>(dfa);
    }

} // namespace sb