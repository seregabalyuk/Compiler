#pragma once

#include <list>
#include <map>
#include <ranges>

namespace sb {
    template<
        bool IsNFA,
        class Type = bool,
        class Letter = char,
        class Allocator = std::allocator<Type>
    > class FA {
      // classes
        class _State;
        class _StoragePtrState;
      // usings
       // allocators
        template<class U>
        using _Alloc = typename std::allocator_traits<
            Allocator
        >::template rebind_alloc<U>;
       // other
        using _States = std::list<_State, _Alloc<_State>>;
        using _Iter = typename _States::iterator;
        using _CIter = typename _States::const_iterator;
        using _Transitions = std::conditional_t<
            IsNFA,
            std::multimap<
                Letter,
                _StoragePtrState,
                std::less<Letter>,
                _Alloc<std::pair<
                    const Letter,
                    _StoragePtrState
                >>
            >,
            std::map<
                Letter,
                _StoragePtrState,
                std::less<Letter>,
                _Alloc<std::pair<
                    const Letter,
                    _StoragePtrState
                >>
            >
        >;
      // _State
        class _State {
          // metods
            _Iter get(Letter letter, std::bool_constant<0> isnfa) {
                return _trans.find(letter)->second;
            }

            _CIter get(Letter letter, std::bool_constant<0> isnfa) const {
                return _trans.find(letter)->second;
            }


            auto get(Letter letter, std::bool_constant<1> isnfa) {
                auto [begin, end] = _trans.equal_range(letter);
                return std::ranges::subrange{begin, end};
            }

            auto get(Letter letter, std::bool_constant<1> isnfa) const {
                auto [begin, end] = _trans.equal_range(letter);
                return std::ranges::subrange{begin, end};
            }
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
            
            _Transitions& trans() { return _trans; }
            const _Transitions& trans() const { return _trans; }
            Type& type() { return _type; }
            const Type& type() const { return _type; }

            void emplace(Letter letter, _Iter next) {
                _trans.emplace(letter, next);
            }
            void erase(Letter letter) {
                _trans.erase(letter);
            }

            auto get(Letter letter) {
                return get(letter, std::bool_constant<IsNFA>());
            }
            auto get(Letter letter) const {
                return get(letter, std::bool_constant<IsNFA>());
            }
        };
      // _StoragePtrState
        class _StoragePtrState {
          // members
            _Iter _iter;
        public:
          // members
           // constructors
            _StoragePtrState(_Iter iter): _iter(iter) {}
           // operators
            _StoragePtrState& operator=(const _StoragePtrState& other) {
                _iter = other._iter;
                return *this;
            }
            _State* operator->() {
                return &*_iter;
            }

            const _State* operator->() const {
                return &*_iter;
            }
            operator _Iter() {
                return _iter;
            }
            operator _CIter() const {
                return _iter;
            }
        };
      // members
        _States _states;
    public:
      // usings 
        using iterator       = _Iter;
        using const_iterator = _CIter;
        using State          = _State;
        using Transition     = _States::value_type;
      // metods
       // iterators
        auto begin() { return _states.begin(); }
        auto end()   { return _states.end(); }
        auto begin() const { return _states.begin(); }
        auto end() const   { return _states.end(); }
        auto cbegin() const { return _states.cbegin(); }
        auto cend() const   { return _states.cend(); }
       // change
        template<class... Args>
        auto emplace(Args&&... args) { 
            return _states.emplace(
                end(),
                _states.get_allocator(),
                std::forward<Args>(args) ...
            );
        }

        auto erase(iterator state) {
            return _states.erase(state);
        }
       // info
        size_t size() const { return _states.size(); }
    };
} // namespace sb