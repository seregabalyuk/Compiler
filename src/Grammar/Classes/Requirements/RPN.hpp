#pragma once

#include <concepts>

#include "../Traits/RPN.hpp"
#include "../RPN/RuleType.hpp"

namespace sb {
// Concepts
  // CreatorRPN
    template<class Creator, class Letter, class Type>
    concept C_CreatorRPN = 
    requires(
        Creator creator,
        const Letter letter,
        const Type type)
    {
        creator.put(letter, type);
        {creator.empty()} -> std::same_as<bool>;
        {creator.get()} -> std::same_as<T_CreatorRPNT<Creator>>;
    };
  // TableRPN
    template<class Table, class Letter, class T>
    concept C_TableRPN = 
        std::same_as<RuleRPNType, T_TableRPNT<Table, Letter>> &&
    requires(
        const Table table,
        const Letter letter,
        const T_TableRPNR<Table, Letter> rule,
        T value) 
    {
        {table.get(letter)} -> std::same_as<const T_TableRPNR<Table, Letter>&>;
        rule.type();
        rule.priority();
        rule(value, std::move(value));
    };
} // namespace sb