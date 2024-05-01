#pragma once

#include "../Requirements/Iterator.hpp"

namespace sb {
    struct CompareIterators {
        template<class Iter>
        bool operator()(
            const Iter& left,
            const Iter& right
        ) const {
            return &*left < &*right;
        }
    };
    using CompIter = CompareIterators;
} // namespace sb