#pragma once

#include "../Classes/Traits/FA.hpp"

namespace sb {
    template<C_NFA NFA>
    void concatNFA(NFA& left,
                NFA&& right) {
        auto eps = T_FALe<NFA>();
        (--left.end())->emplace(eps, right.begin());
        left.splice(right);
    } // OK

    template<C_NFA NFA>
    void alterNFA(NFA& left,
               NFA&& right) {
        auto eps = T_FALe<NFA>();

        auto lstart = left.begin();
        auto rstart = right.begin();

        auto lfinish = -- left.end();
        auto rfinish = -- right.end();

        left.splice(right);
        left.emplace_front();
        left.emplace_back();

        left.begin()->emplace(eps, lstart);
        left.begin()->emplace(eps, rstart);
        
        lfinish->emplace(eps, --left.end());
        rfinish->emplace(eps, --left.end());
    } // OK

    template<C_NFA NFA>
    void kleeneNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();

        auto prevstart = nfa.begin();
        auto prevfinish = -- nfa.end();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        nfa.begin()->emplace(eps, --nfa.end());
        (--nfa.end())->emplace(eps, nfa.begin());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, --nfa.end());
    } // OK

    template<C_NFA NFA>
    void plusNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();
        
        auto prevstart = nfa.begin();
        auto prevfinish = --nfa.end();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        (--nfa.end())->emplace(eps, nfa.begin());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, --nfa.end());
    } // OK

    template<C_NFA NFA>
    void questionNFA(NFA& nfa) {
        auto eps = T_FALe<NFA>();

        auto prevstart = nfa.begin();
        auto prevfinish = --nfa.end();
        
        nfa.emplace_front();
        nfa.emplace_back();
        
        nfa.begin()->emplace(eps, --nfa.end());
        
        nfa.begin()->emplace(eps, prevstart);
        prevfinish->emplace(eps, --nfa.end());
    } // OK

    template<C_NFA NFA>
    void setTypeNFA(
        NFA& left,
        NFA&& right) {
        (--left.end())->type() |= (--right.end())->type();
    }
} // namespace sb