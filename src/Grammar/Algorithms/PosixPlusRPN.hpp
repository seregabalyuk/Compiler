#pragma once

#include "PosixRPN.hpp"

namespace sb {
    namespace posix {
        using NFAPlus = FA<1, Letter, Letter>;
        using DFAPlus = FA<0, Letter, Letter>;
        using CreatorNFAPlus = ::sb::CreatorNFA<NFAPlus, Letter>;
        using TableRPNPlus = ::sb::TableRPN<NFAPlus, Letter>;
        using RPNPlus = ::sb::RPN<DFAPlus, CreatorNFAPlus, TableRPNPlus>;
    }

    auto makePosixPlusRPN() {
      // make dfa
         posix::DFA* dfa = new posix::DFA();
        {
            std::ifstream fin("../src/Grammar/Filework/PosixPlusDFA.txt");
            simpleReadFileFA(fin, *dfa);
        }
      // make creator
        posix::CreatorNFAPlus* creator = new posix::CreatorNFAPlus();
        creator->putAcceptLetters('!', '~'); // all letter
        // https://www.industrialnets.ru/files/misc/ascii.pdf
        creator->putTypeSimple('m');
        creator->putTypeReverse('r');
        creator->putTypeLoop('l');
        creator->putTypeInBrackets('b');
        creator->putTypeOutBrackets('p');
        creator->putTypeSpecial('s');
        creator->putTypeKind('k');
        creator->putLetterEmpty('e');
      // make table
        posix::TableRPNPlus* table = new posix::TableRPNPlus();
		    table->addBinary('\0', 1, concatNFA<posix::NFAPlus>);
        table->addBinary('|', 0, alterNFA<posix::NFAPlus>);
        table->addBinary(':', 3, setTypeNFA<posix::NFAPlus>);
        
        table->addSufUnary('*', 2, kleeneNFA<posix::NFAPlus>);
        table->addSufUnary('+', 2, plusNFA<posix::NFAPlus>);
        table->addSufUnary('?', 2, questionNFA<posix::NFAPlus>);
      // make rpn
        posix::RPNPlus* rpn = new posix::RPNPlus(*dfa, *creator, *table);
        rpn->putTypeTable('t');
        rpn->putTypeBrackets('o', 'c');
        rpn->putTypeEmpty(' ');
        return std::tuple{rpn, dfa, creator, table};
    }
};
