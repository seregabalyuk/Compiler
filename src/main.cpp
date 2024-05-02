#include <map>
#include <iostream>

#include <Grammar/Classes/FA/FA.hpp>
#include <Grammar/Debug/PrintFA.hpp>
#include <Grammar/Algorithms/NFA2DFA.hpp>
#include <Grammar/Algorithms/FunctionsNFA.hpp>


int main() {
    using DFA = sb::FA<0>;
    using NFA = sb::FA<1>;
    NFA nfa;
    NFA nfa2;
    nfa.emplace_back();
    nfa.begin()->emplace('a', nfa.begin());
    nfa.begin()->emplace('a', nfa.begin());
    nfa.begin()->emplace('a', nfa.begin());

    nfa.begin()->type() = true;
    

    sb::printFA(std::cout, nfa);

    auto dfa = nfa2dfa<DFA>(nfa);

    sb::printFA(std::cout, dfa);    
}