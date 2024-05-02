#pragma once

#include "HelperFA.hpp"

namespace sb {
    template<C_cFA FA>
    auto getAllLetterDFA(const FA& fa) {
        using SetLetter = std::set<T_FALe<FA>>;
        SetLetter letters;
        for (auto& state: fa) {
            for (auto& trans: state.trans()) {
                letters.emplace(trans.first);
            }
        }
        using Letters = std::list<T_FALe<FA>>;
        Letters ret;
        for (auto letter: letters) { ret.emplace_back(letter); }
        return ret;
    }

    template<C_DFA OutFA, C_cDFA InFA> 
    requires C_AssociateFA<OutFA, InFA>
    OutFA minimizeDFA(const InFA& fa) {
        using Class = SetCFA<InFA>;
        
        using QueClass = std::set<Class*>;
        using Classes = std::list<Class>;

        Classes classes;
        { // First classes
            using Type2Class = std::map<T_FATy<InFA>, Class*>;
            Type2Class type2class;
            for (auto state = fa.begin(); state != fa.end(); ++ state) {
                if (!type2class.count(state->type())) {
                    auto& _class = classes.emplace_back();
                    type2class.emplace(state->type(), &_class);
                }
                type2class[state->type()]->emplace(state);
            }
        }
        auto letters = getAllLetterDFA(fa);
        QueClass queClass;
        { // First que
            for(auto& _class: classes) {
                queClass.emplace(&_class);
            }
        }

        { // find partition  FA
         while(queClass.size()) {
          auto spliter = *queClass.begin();
          queClass.erase(spliter);
          for (auto letter: letters) {
           for (auto& _class: classes) {
            Class left, right;
            // split by spliter and letter
            for (auto& state: _class) {
              if (state->count(letter) && 
                  spliter->count(state->get(letter))) {
                left.emplace(state);
              } else {
                right.emplace(state);
              }
            }
            // emplace in queClass
            if (left.size() && right.size()) {
              if (queClass.count(&_class)) {
                _class.swap(left);
                auto& back = classes.emplace_back(std::move(right));
                queClass.emplace(&back);
              } else {
                _class.swap(left);
                auto& back = classes.emplace_back(std::move(right));
                if (back.size() < _class.size()) {
                  queClass.emplace(&back);
                } else {
                  queClass.emplace(&_class);
                }
              }
            } // emplace in queClass
           } // for by classes
          } // for by letters
         } // while
        }

        OutFA ret;
        { // Create ret by classes
            using In2Out = std::map<
                T_FAPtrCSt<InFA>,
                T_FAPtrSt<OutFA>,
                CompIter
            >;
            In2Out translator;
            // class with start make first
            auto iter = classes.begin();
            while ( iter != classes.end() &&
                    !iter->count(fa.begin())) {
                ++ iter;
            }
            classes.emplace_front(std::move(*iter));
            classes.erase(iter);
            // add state in out
            for (auto& _class: classes) {
                auto stateOut = ret.emplace_back();
                for (auto stateIn: _class) {
                    translator[stateIn] = stateOut;
                }
            }
            // add transition in out
            for (auto& _class: classes) {
                auto stateIn = *_class.begin();
                auto stateOutPrev = translator[stateIn];
                stateOutPrev->type() = stateIn->type();
                for (auto& trans: stateIn->trans()) {
                    auto stateOutNext = translator[trans.second];
                    stateOutPrev->emplace(trans.first, stateOutNext);
                }
            }
        }
        return ret;
    }

} // namespace sb