#pragma once

#include <list>
#include <string>

#include "../Requirements/FA.hpp"
#include "../Requirements/RPN.hpp"

namespace sb {
    template<
        C_cDFA DFA,
        C_CreatorRPN<
            T_FALe<DFA>,
            T_FATy<DFA>
        > Creator,
        C_TableRPN<
            T_FALe<DFA>,
            T_CreatorRPNT<Creator>
        > Table,
        class Allocator = std::allocator<void>
    > class RPN {
      // usings
       // from DFA
        using _Letter = T_FALe<DFA>;
        using _State = T_FAPtrCSt<DFA>;
        using _TypeDFA = T_FATy<DFA>;

       // from Creator
        using _T = T_CreatorRPNT<Creator>;

       // from Table
        using _Rule = const T_TableRPNR<Table, _Letter>;
        using _Priority = T_TableRPNP<Table, _Letter>;
        using _TypeTable = T_TableRPNT<Table, _Letter>;
        using _PtrRule = _Rule*;

       // from Allocator
        template<class U>
        using _Alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<U>;
        template<class U>
        using _AllocTraits = typename std::allocator_traits<Allocator>::template rebind_traits<U>;
        template<class U>
        using _Ptr = _AllocTraits<U>::pointer;

       // other
        using _StackT = std::list<_T, _Alloc<_T>>;
        using _StackR = std::list<_PtrRule, _Alloc<_PtrRule>>;
      // function
        void _removeOneRuleFromStack() {
            _executeRule(_stackR.back());
            if (_stackR.back()->type() == RuleRPNType::Binary) {
                -- _counterTbyR;
            }
             _stackR.pop_back();
        }
        void _removeRulesFromStack(_PtrRule rule) {
            while (
                _stackR.size() &&
                _stackR.back() &&
                _stackR.back()->priority() >= rule->priority()) 
            {
                _removeOneRuleFromStack();
            }
        }
        void _addRuleToStack(_PtrRule rule) {
            _stackR.emplace_back(rule);
            if (rule->type() == RuleRPNType::Binary) {
                ++ _counterTbyR;
            }
        }
        void _addEpsRuleToStack() {
            _PtrRule rule = &_table->get(_Letter());
            if (rule->type() == RuleRPNType::Binary) {
                _removeRulesFromStack(rule);
                _addRuleToStack(rule);
            } else {
                throw std::string{"Eps rule is not binary"};
            }
        }
        void _tryAddEpsRuleToStack() {
            if (_stackT.size() > _counterTbyR) {
                _addEpsRuleToStack();
            }
        }
        void _executeRule(_PtrRule rule) {
            switch(rule->type()) {
            case RuleRPNType::Binary:
                if (_stackT.size() < 2) {
                    throw std::string{"StackT is little for binary rule "}
                        + rule->letter();
                }
                {
                    auto& first = *(++_stackT.rbegin());
                    auto& second = _stackT.back();
                    (*rule)(first, std::move(second));
                    _stackT.pop_back();
                }
                break;
            case RuleRPNType::PrefixUnary:
                if (!_stackT.size()) {
                    throw std::string{"StackT is little for prifix rule "}
                        + rule->letter();
                }
                (*rule)(_stackT.back());
                break;
            case RuleRPNType::SuffixUnary:
                if (!_stackT.size()) {
                    throw std::string{"StackT is little for suffix rule "} 
                        + rule->letter();
                }
                (*rule)(_stackT.back());
                break;
            default:
                throw  std::string{"This rule unknow type in rpn"}; 
            }
        }
        void _defaultSettings() {
            _stackT.clear();
            _stackR.clear();
            _creator->clear();
            _state = _dfa->begin();
            _counterTbyR = 0;
        }
       #ifdef RPNDEBUG
        void drawCondition(_Letter letter, const _TypeDFA& type) {
            std::cout << "--------\n";
            std::cout << letter << ' ' << type << '\n';
            std::cout << _stackT.size() << ' ' << _stackR.size() << '\n';
            for (auto& rule: _stackR) {
                if (!rule) {
                    std::cout << '(';
                } else if (rule->letter() == _Letter()) {
                    std::cout << 'e';
                } else {
                    std::cout << rule->letter();
                }
            }
            std::cout << '\n';
            for (auto& t:_stackT) {
                printFA(std::cout, t) << '\n';
            }
            std::cout << '\n';
        }
       #endif
      // members
        const DFA* _dfa;
        Creator* _creator;
        const Table* _table;
        
        _State _state;
        
        _StackT _stackT;
        _StackR _stackR;
        size_t _counterTbyR = 0;

        _TypeDFA _typeTable;
        _TypeDFA _typeOpen;
        _TypeDFA _typeClose;
        _TypeDFA _typeEmpty;
   
    public:
      // functions
       // constructors
        RPN(const Allocator& alloc):
            _stackT(alloc),
            _stackR(alloc) {}

        RPN() {}

        RPN(const DFA& dfa, Creator& creator, const Table& table) {
            putDFA(dfa);
            putCreator(creator);
            putTable(table);
        }

        RPN(const DFA& dfa, Creator& creator, const Table& table, const Allocator& alloc):
            _stackT(alloc),
            _stackR(alloc) {
            putDFA(dfa);
            putCreator(creator);
            putTable(table);
        }
       // metods
        void putDFA(const DFA& dfa) {
            _dfa = &dfa;
            _state = _dfa->begin();
        }

        void putTable(const Table& table) {
            _table = &table;
        }

        void putCreator(Creator& creator) {
            _creator = &creator;
        }

        void putTypeTable(const _TypeDFA& type) {
            _typeTable = type;
        }

        void putTypeBrackets(const _TypeDFA& open, const _TypeDFA& close) {
            _typeOpen = open;
            _typeClose = close;
        }

        void putTypeEmpty(const _TypeDFA& type) {
            _typeEmpty = type;
        }
        
        RPN& put(_Letter letter) try {
			if(!_state->count(letter)) {
				throw std::string{"State DFA cannot go by "} + letter;
			}
			_state = _state->get(letter);
            const auto& type = _state->type();
			if (type == _typeTable) { // is operation
				_PtrRule rule = &_table->get(letter);
                switch (rule->type()) {
                case RuleRPNType::PrefixUnary:
                    _stackR.emplace_back(rule);
                    break;
                case RuleRPNType::SuffixUnary:
                    _removeRulesFromStack(rule);
                    _executeRule(rule);
                    break;
                case RuleRPNType::Binary:
                    _removeRulesFromStack(rule);
                    _addRuleToStack(rule);
                    break;
                default:
                    throw std::string{"Unknow type rule"};
                }
            } else if (type == _typeOpen) { // is open bracket
                _tryAddEpsRuleToStack();
                _stackR.emplace_back(nullptr);
            } else if (type == _typeClose) { // is close bracket
                while(_stackR.size() && _stackR.back()) {
                    _removeOneRuleFromStack();
                }
                if (_stackR.empty()) {
                    throw std::string{"Missing open bracket"};
                }
                _stackR.pop_back();
            } else if (type != _typeEmpty) { // is simple letter
                _creator->put(letter, type);
                if (!_creator->empty()) {
                    _tryAddEpsRuleToStack();
                    _stackT.emplace_back(_creator->get());
                }
            }
           #ifdef RPN_DEBUG
            drawCondition(letter, type);
           #endif
            return *this;
        } catch (const std::string& error) {
            _defaultSettings();
            throw std::string{"In put letter = "} + letter + " type = " +  _state->type() + ": " + error;
        }

        _T get() try {
            while (_stackR.size()) {
                if (!_stackR.back()) {
                    throw std::string{"Missing close bracket"};
                }
                _executeRule(_stackR.back());
                _stackR.pop_back();
            }
            if (_stackT.size() > 1) {
                throw std::string{"Many argues"};
            }
            if (_stackT.empty()) {
                throw std::string{"Little argues"};
            }
            _T out = std::move(_stackT.back());
            _table->getEnd()(out);
            _defaultSettings();
            return out;
        } catch(const std::string& error) {
            _defaultSettings();
            throw std::string{"In get: "} + error;
        } 
    };

    template<class DFA, class Creator, class Table>
    RPN(const DFA&, Creator&, const Table&) -> RPN<DFA, Creator, Table>;

    template<class DFA, class Creator, class Table, class Allocator>
    RPN(const DFA&, Creator&, const Table&, const Allocator&) -> RPN<DFA, Creator, Table, Allocator>;
};
