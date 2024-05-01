#pragma once

#include "../Requirements/Iterator.hpp"

namespace sb {
    template<class Iter>
    struct CompareIterators {
        bool operator()(
            const Iter& left,
            const Iter& right
        ) const {
            return &*left < &*right;
        }
    };
    template<class Iter>
    using CompIter = CompareIterators<Iter>;
} // namespace sb