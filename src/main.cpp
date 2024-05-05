#include <map>
#include <iostream>

#define RPNDEBUG

#include <Grammar/Classes/FA/FA.hpp>
#include <Grammar/Debug/PrintFA.hpp>
#include <Grammar/Algorithms/NFA2DFA.hpp>
#include <Grammar/Algorithms/FunctionsNFA.hpp>

#include <Grammar/Classes/RPN/CreatorNFA.hpp>
#include <Grammar/Filework/SimpleReadFA.hpp>

#include <Grammar/Algorithms/PosixPlusRPN.hpp>

int main() {
    using DFA = sb::FA<0, char>;
    using NFA = sb::FA<1>;
    auto f = sb::makePosixPlusRPN();
    auto& rpn = *std::get<0>(f);

    std::string str;
    std::getline(std::cin, str, '\n');
    for (auto chr: str) {
        rpn.put(chr);
        //std::cout << chr << '\n';
    }
    auto nfa = rpn.get();
    sb::printFA(std::cout, nfa) << '\n';
    auto dfa = sb::nfa2dfa<DFA>(nfa);
    sb::printFA(std::cout, dfa) << '\n';
}