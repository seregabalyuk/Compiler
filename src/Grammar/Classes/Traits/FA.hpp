#pragma once

#include <type_traits>

#include <Base/Traits/DeclVal.hpp>
#include <Base/Traits/Iterable.hpp>


namespace sb {
  // Transition
    template<class Trans>
    class T_TransitionFA;
    
    template<class Trans>
    using T_TransitionFALe     = T_TransitionFA<Trans>::Letter;

  // State
    template<class State>
    class T_StateFA;

    template<class State>
    using T_StateFALe     = T_StateFA<State>::Letter;
    template<class State>
    using T_StateFATy     = T_StateFA<State>::Type;
    template<class State>
    using T_StateFATr     = T_StateFA<State>::Transition;

  // FA
    template<class FA>
    class T_FA;

    template<class FA>
    using T_FASt  = T_FA<FA>::State;
    template<class FA>
    using T_FAPtrSt  = T_FA<FA>::PtrState;
    template<class FA>
    using T_FAPtrCSt = T_FA<FA>::PtrConstState;
    template<class FA>
    using T_FALe     = T_FA<FA>::Letter;
    template<class FA>
    using T_FATy     = T_FA<FA>::Type;
    template<class FA>
    using T_FATr     = T_FA<FA>::Transition;
// realization
  // Transition
   // local
    template<class Trans>
    concept lC_T_TransitionFA = 
    requires(const Trans c_trans) {
        c_trans.first;
    };

    template<class Trans, bool Okey>
    struct lT_TransitionFA {
        using Letter = void;
    };
    
    template<class Trans>
    struct lT_TransitionFA<Trans, 1> {
        using Letter = std::remove_cvref_t<
            decltype(DeclLVal<const Trans>().first)
        >;
    };
   // global
    template<class Trans>
    class T_TransitionFA {
        using _Traits = lT_TransitionFA<
            Trans,
            lC_T_TransitionFA<Trans>
        >;
    public:
        using Letter = typename _Traits::Letter;
    };
  // State
   // local
    template<class State>
    concept lC_T_StateFA = 
    requires(const State c_state) {
        c_state.type();
        *c_state.trans().begin();
    };

    template<class State, bool Okey>
    struct lT_StateFA {
        using Type = void;
        using Transition = void;
    };
    
    template<class State>
    struct lT_StateFA<State, 1> {
        using Type = std::remove_cvref_t<
            decltype(DeclLVal<const State>().type())
        >;
        using Transition = std::remove_cvref_t<
            decltype(*DeclLVal<const State>().trans().begin())
        >;
    };
   // global
    template<class State>
    class T_StateFA {
        using _Traits = lT_StateFA<
            State,
            lC_T_StateFA<State>
        >;
    public:
        using Type          = typename _Traits::Type;
        using Transition    = typename _Traits::Transition;
        using Letter        = T_TransitionFALe<Transition>;
    };
  // FA
   // global
    template<class FA>
    class T_FA {
    public:
        using State = std::remove_cvref_t<
            T_IterableTy<const FA>
        >;
        using PtrConstState = T_IterableIt<const FA>;
        using PtrState      = T_IterableIt<FA>;
        using Transition    = T_StateFATr<State>;
        using Type          = T_StateFATy<State>;
        using Letter        = T_StateFALe<State>;
    };
} // namespace sb