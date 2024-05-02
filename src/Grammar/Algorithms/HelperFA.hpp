#pragma once

#include <Base/Classes/CompareIterators.hpp>
#include "../Classes/Traits/FA.hpp"

#include <set>
#include <map>
#include <list>

namespace sb {
  // use in removers
    template<C_FA FA>
    using SetFA = std::set<
        T_FAPtrSt<FA>,
        CompIter
    >;

    template<C_cFA FA>
    using SetCFA = std::set<
        T_FAPtrCSt<FA>,
        CompIter
    >;

  // Use in Determine
    template<C_cFA FA>
    using SetPtrCFA = std::set<
        const T_FASt<FA>*
    >;

    template<C_cFA InFA, C_FA OutFA>
    using SetPtrC2StFA = std::map<
        SetPtrCFA<InFA>,
        T_FAPtrSt<OutFA>
    >;

    template<C_cFA FA>
    using Le2SetPtrCFA = std::map<
        T_FALe<FA>,
        SetPtrCFA<FA>
    >;
  // 
    
} // namespace sb