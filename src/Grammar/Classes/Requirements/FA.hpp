#pragma once

#include <Base/Requirements/Iterable.hpp>
#include "../Traits/FA.hpp"

namespace sb {
  // FA
   // Const
    template<class FA>
    concept C_cFA =
        C_Iterable<const FA> &&
    requires(
        const FA fa,
        const T_FALe<FA> letter,
        const T_FATr<FA> trans,
        const T_FASt<FA> state,
        T_FAPtrCSt<FA> ptr
    ) {
        {trans.first} -> std::convertible_to<T_FALe<FA>>;
        {trans.second} -> std::convertible_to<T_FAPtrCSt<FA>>;
        
        {state.trans()} -> C_Iterable;
        {*state.trans().begin()} -> std::same_as<const T_FATr<FA>&>;
        state.type();

        {*ptr} -> std::same_as<const T_FASt<FA>&>;
        
        {fa.size()} -> std::same_as<size_t>;
    };
   // No const
    template<class FA>
    concept C_FA =
        C_cFA<FA> &&
        C_Iterable<FA> &&
    requires(
        FA fa,
        const T_FALe<FA> letter,
        T_FATr<FA> trans,
        T_FASt<FA> state,
        T_FATy<FA> type,
        T_FAPtrSt<FA> ptr
    ) {
        {trans.first} -> std::convertible_to<T_FALe<FA>>;
        {trans.second} -> std::convertible_to<T_FAPtrSt<FA>>;
        
        {state.trans()} -> C_Iterable;
        {*state.trans().begin()} -> std::same_as<T_FATr<FA>&>;
        {state.type()} -> std::same_as<T_FATy<FA>&>;

        state.emplace(letter, ptr);
        state.erase(letter);

        {type = type} -> std::same_as<T_FATy<FA>&>;
        {type |= type} -> std::same_as<T_FATy<FA>&>;
        {type | type} -> std::convertible_to<T_FATy<FA>>;

        {*ptr} -> std::same_as<T_FASt<FA>&>;

        {fa.emplace()} -> std::same_as<T_FAPtrSt<FA>>;
        fa.erase(ptr);
    };
  // DFA
   // Const
    template<class DFA>
    concept C_cDFA =
        C_cFA<DFA> &&
    requires(
        const T_FASt<DFA> state,
        const T_FALe<DFA> letter
    ) {
        {state.get(letter)} -> std::same_as<T_FAPtrCSt<DFA>>;
    };
   // No const
    template<class DFA>
    concept C_DFA =
        C_cDFA<DFA> &&
        C_FA<DFA> &&
    requires(
        T_FASt<DFA> state,
        const T_FALe<DFA> letter
    ) {
        {state.get(letter)} -> std::same_as<T_FAPtrSt<DFA>>;
    };
  // NFA
   // Const
    template<class NFA>
    concept C_cNFA =
        C_cFA<NFA> &&
    requires(
        const T_FASt<NFA> state,
        const T_FALe<NFA> letter
    ) {
        {*state.get(letter).begin()} -> std::same_as<const T_FATr<NFA>&>;
        {*state.get(letter).end()} -> std::same_as<const T_FATr<NFA>&>;    
    };
   // No const
    template<class NFA>
    concept C_NFA =
        C_cNFA<NFA> &&
        C_FA<NFA> &&
    requires(
        T_FASt<NFA> state,
        const T_FALe<NFA> letter
    ) {
        {*state.get(letter).begin()} -> std::same_as<T_FATr<NFA>&>;
        {*state.get(letter).end()} -> std::same_as<T_FATr<NFA>&>;
    };
  // Checkers
    template<C_cFA FA>
    void checkcFA(const FA& fa) {}
    template<C_FA FA>
    void checkFA(const FA& fa) {}

    template<C_cDFA DFA>
    void checkcDFA(const DFA& fa) {}
    template<C_DFA DFA>
    void checkDFA(const DFA& fa) {}

    template<C_cDFA DFA>
    void checkcNFA(const DFA& fa) {}
    template<C_DFA DFA>
    void checkNFA(const DFA& fa) {}
} // namespace sb