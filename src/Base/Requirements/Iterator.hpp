#pragma once

#include <concepts>

#include "../Traits/Iterator.hpp"

namespace sb {
    template<class Iter>
    concept C_Iterator = 
    requires(Iter iter) {
        {++ iter} -> std::same_as<Iter&>;
        {*iter};
        {iter != iter} -> std::same_as<bool>;
    };
} // namespace sb