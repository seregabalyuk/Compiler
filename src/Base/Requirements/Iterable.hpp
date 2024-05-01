#pragma once

#include <concepts>

#include "Iterator.hpp"
#include "../Traits/Iterable.hpp"

namespace sb {
    template<class T>
    concept C_Iterable = 
    requires(T value) {
        {value.begin()} -> C_Iterator;
        {value.end()  } ->std::same_as<T_IterableIt<T>>;
    };
} // namespace sb