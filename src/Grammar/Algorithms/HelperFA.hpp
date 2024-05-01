#pragma once

#include <Base/Classes/CompareIterators.hpp>
#include "../Classes/Traits/FA.hpp"

#include <set>
#include <map>

namespace sb {
    template<C_FA FA>
    using SetFA = std::set<
        T_FAPtrSt<FA>,
        CompIter<T_FAPtrSt<FA>>
    >;

    template<C_FA FA>
    using SetCFA = std::set<
        T_FAPtrCSt<FA>,
        CompIter<T_FAPtrCSt<FA>>
    >;

    template<C_FA InFA, C_FA OutFA>
    using Set2StFA = std::map<
        SetCFA<InFA>,
        T_FAPtrSt<OutFA>
    >;

    template<C_FA FA>
    using Le2SetCFA = std::map<
        T_FALe<FA>,
        SetCFA<FA>
    >;

    
} // namespace sb