#pragma once

#include "Iterator.hpp"

namespace sb {
    template<class T>
    class T_Iterable;

    template<class T>
    using T_IterableTy = T_Iterable<T>::Type;
    template<class T>
    using T_IterableIt = T_Iterable<T>::Iterator;
// realization
  // local
    template<class T>
    concept lC_T_Iterable =  // concept Iter Type
    requires(T value) {
        value.begin();
    };

    template<class T, bool HaveType>
    struct lT_Iterable { // traits Iter Type
        using Iterator = void;
    };

    template<class T>
    struct lT_Iterable<T, 1> {
        using Iterator = std::remove_reference_t<
            decltype(DeclLVal<T>().begin())
        >;
    };
  // global
    template<class T>
    class T_Iterable {
        using _Traits = lT_Iterable<
            T,
            lC_T_Iterable<T>
        >;
    public:
        using Iterator = typename _Traits::Iterator;
        using Type = T_IteratorTy<Iterator>;
    };

} // namespace sb