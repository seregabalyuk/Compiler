#pragma once

#include "../Classes/Traits/FA.hpp"

namespace sb {
    template<C_NFA NFA>
    void concatNFA(NFA& left,
                NFA&& right) {
        auto eps = T_FALe<NFA>();
        left.rbegin()->emplace(eps, right.begin());
        left.splice(right);
    } // OK

    template<C_NFA NFA>
    void alterNFA(NFA& left,
               NFA&& right) {
        auto eps = T_FALe<NFA>();

        auto lstart = left.begin();
        auto rstart = right.begin();

        auto lfinish = left.rbegin();
        auto rfinish = right.rbegin();

        left.splice(right);
        left.emplace_front();
        left.emplace_back();

        left.begin()->emplace(eps, lstart);
        left.begin()->emplace(eps, rstart);
        
        lfinish->emplace(eps, left.rbegin().base());
        rfinish->emplace(eps, left.rbegin().base());
    } // OK

    template<C_NFA NFA>
    void kleeneNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();

        auto prevstart = nfa.begin();
        auto prevfinish = nfa.rbegin();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        nfa.begin()->emplace(eps, nfa.rbegin().base());
        nfa.rbegin()->emplace(eps, nfa.begin());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, nfa.rbegin().base());
    } // OK

    template<C_NFA NFA>
    void plusNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();
        
        auto prevstart = nfa.begin();
        auto prevfinish = nfa.rbegin();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        nfa.rbegin()->emplace(eps, nfa.begin());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, nfa.rbegin().base());
    } // OK

    template<C_NFA NFA>
    void questionNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();

        auto prevstart = nfa.begin();
        auto prevfinish = nfa.rbegin();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        nfa.begin()->emplace(eps, nfa.rbegin().base());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, nfa.rbegin().base());
    } // OK

    template<C_NFA NFA>
    void setTypeNFA(
        NFA& left,
        NFA&& right) {
        left.rbegin()->type() |= right.rbegin()->type();
    }
} // namespace sb