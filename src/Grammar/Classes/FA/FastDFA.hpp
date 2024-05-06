#pragma once

#include <vector>
#include <utility>
#include <map>
#include <algorithm>

#include <Base/Classes/CompareIterators.hpp>
#include "../Requirements/FA.hpp"

namespace sb {
    template<
        class Type = bool,
        class Letter = char,
        class Allocator = std::allocator<Type>
    > class FastDFA {
      // classes
        class _State;
      // usings
       // allocators
        template<class U>
        using _Alloc = typename std::allocator_traits<
            Allocator
        >::template rebind_alloc<U>;
       // other
        using _States = std::vector<_State, _Alloc<_State>>;
        using _CIter = typename _States::const_iterator;
        using _Iter = typename _States::iterator;
        using _Transition = std::pair<Letter, _CIter>;
        using _Transitions = std::vector<
            _Transition,
            _Alloc<_Transition>
        >;
      // _State
        class _State {
          // friends
            friend class FastDFA;  
          // members
            _Transitions _trans;
            Type _type;
        public:
          // metods
            template<class... Args>
            _State(Allocator alloc, Args&&... args):
                _type(std::forward<Args>(args) ...),
                _trans(alloc)
            {}
            const _Transitions& trans() const { return _trans; }
            const Type& type() const { return _type; }
            constexpr size_t count(Letter letter) const {
                return 1;
            }
            auto get(Letter letter) const {
                size_t l = 0, r = _trans.size();
                while (l + 1 < r) {
                    size_t c = (l + r) / 2;
                    if (_trans[c].first <= letter) {
                        l = c;
                    } else {
                        r = c;
                    }
                }
                return _trans[l].second;
            }
        };
      // metods
        template<C_cDFA DFA>
        auto _allocate(const DFA& other) {
            _states.reserve(other.size() + 1);
            for (auto state: other) {
                _states.emplace_back(
                    _states.get_allocator(),
                    state.type()
                );
            }
            _states.emplace_back(_states.get_allocator(), Type());
        }

        template<C_cDFA DFA>
        auto _createSt2Num(const DFA& other) {
            std::map<
                T_FAPtrCSt<DFA>,
                _Iter,
                CompIter
            > o2t;
            
            auto st_other = other.begin();
            auto st_this = _states.begin();

            while (st_other != other.end()) {
                o2t.emplace(st_other ++, st_this ++);
            }
            return o2t;
        }

        template<C_cDFA DFA>
        void _make(const DFA& other) {
            _allocate(other);

            auto o2t = _createSt2Num(other);
            auto trash = --_states.end();

            for (
                auto st_other = other.begin();
                st_other != other.end();
                ++ st_other
                ) {
                auto st_this = o2t[st_other];
                for (auto& trans: st_other->trans()) {
                    st_this->_trans.emplace_back(
                        trans.first,
                        o2t[trans.second]
                    );
                }
                std::sort(
                    st_this->_trans.begin(),
                    st_this->_trans.end()
                );
                _Transitions good;
                good.emplace_back(Letter(), trash);
                if (st_this->_trans.size()) {
                    good.emplace_back(st_this->_trans.front());
                    
                    for (size_t i = 1;
                        i < st_this->_trans.size();
                        ++ i
                        ) {
                        auto l1 = st_this->_trans[i - 1].first;
                        auto it1 = st_this->_trans[i - 1].second;
                        auto l2 = st_this->_trans[i].first;
                        auto it2 = st_this->_trans[i].second;
                        if (l1 + 1 == l2 && it1 != it2) {
                            good.emplace_back(l2, it2);
                        } 
                        if (l1 + 1 < l2) {
                            good.emplace_back(l1 + 1, trash);
                            good.emplace_back(l2, it2);
                        }
                    }
                    auto l = st_this->_trans.back().first;
                    good.emplace_back(l + 1, trash);
                }
                st_this->_trans = std::move(good);
            }
            _states.back()._trans.emplace_back(Letter(), trash);
        }
      // members
        _States _states;
    public:
      // metods
        template<C_cDFA DFA>
        FastDFA(const DFA& other, Allocator alloc = Allocator()):
            _states(alloc) {
            _make(other);
        }

        auto begin() const { return _states.begin(); }
        auto end() const { return _states.end(); }

        auto cbegin() const { return _states.begin(); }
        auto cend() const { return _states.end(); }

        size_t size() const {
            return _states.size();
        }
    };

    template<C_cDFA DFA, class Alloc>
    FastDFA(const DFA&, const Alloc&) -> 
        FastDFA<T_FALe<DFA>, T_FATy<DFA>, Alloc>;

    template<C_cDFA DFA>
    FastDFA(const DFA&) -> FastDFA<T_FALe<DFA>, T_FATy<DFA>>;

} // namespace sb