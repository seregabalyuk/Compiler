#include <map>
#include <iostream>

#include <Grammar/Classes/FA/FA.hpp>
#include <Grammar/Debug/PrintFA.hpp>
#include <Grammar/Algorithms/RemoveEpsNFA.hpp>
//#include <Grammar/Algorithms/RemoveUselessNFA.hpp>
#include <Grammar/Algorithms/DetermineNFA.hpp>

int main() {
    using DFA = sb::FA<0>;
    using NFA = sb::FA<1>;
    NFA nfa;
    nfa.emplace();
    nfa.begin()->emplace('a', nfa.begin());
    sb::removeEpsNFA(nfa);
    //sb::removeUselessNFA(nfa);
    //auto dfa = sb::determineNFA<DFA>(nfa);
    
    sb::printFA(std::cout, nfa);
}