#pragma once

namespace sb {
    template<size_t Id>
    struct Label {
        static constexpr size_t value = Id;
    }
} // namespace sb