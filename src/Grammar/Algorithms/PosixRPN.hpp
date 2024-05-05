#pragma once

#include <tuple>

#include "../Classes/RPN/CreatorNFA.hpp"

#include "../Filework/SimpleReadFA.hpp"
#include "../Classes/FA/FA.hpp"
#include "../Algorithms/FunctionsNFA.hpp"

#include "../Classes/RPN/RPN.hpp"
#include "../Classes/RPN/Table.hpp"

namespace sb {
    namespace posix {
        using Letter = char;
        using NFA = FA<1, Letter, char>;

        using Type = char;
        using DFA = FA<0, Letter, Type>;
        using CreatorNFA = CreatorNFA<NFA, Type>;
        using TableRPN = TableRPN<NFA, Letter>;
        using RPN = RPN<DFA, CreatorNFA, TableRPN>;

        void endUnary(NFA& nfa) {
            (--nfa.end())->type() = 1;
        }
    }
    
    auto makePosixRPN() {
      // make dfa
        posix::DFA* dfa = new posix::DFA();
        {
            std::ifstream fin("../src/Grammar/Filework/PosixDFA.txt");
            simpleReadFileFA(fin, *dfa);
        }
      // make creator
        posix::CreatorNFA* creator = new posix::CreatorNFA();
        creator->putAcceptLetters('!', '~'); // all letter
        // https://www.industrialnets.ru/files/misc/ascii.pdf
        creator->putTypeSimple('m');
        creator->putTypeReverse('r');
        creator->putTypeLoop('l');
        creator->putTypeInBrackets('b');
        creator->putTypeOutBrackets('p');
        creator->putTypeSpecial('s');
        creator->putLetterEmpty('e');
      // make table
        posix::TableRPN* table = new posix::TableRPN();
		table->addBinary('\0', 1, concatNFA<posix::NFA>);
        table->addBinary('|', 0, alterNFA<posix::NFA>);
        table->addSufUnary('*', 2, kleeneNFA<posix::NFA>);
        table->addSufUnary('+', 2, plusNFA<posix::NFA>);
        table->addSufUnary('?', 2, questionNFA<posix::NFA>);
        table->putEndUnary(posix::endUnary);
      // make rpn
        posix::RPN* rpn = new posix::RPN(*dfa, *creator, *table);
        rpn->putTypeTable('t');
        rpn->putTypeBrackets('o', 'c');
        rpn->putTypeEmpty(' ');
        return std::tuple{rpn, dfa, creator, table};
    }
};
