#pragma once

namespace sb {
    template<class From, class To, class In>
    struct G_Replace { 
        using Type = In;
    };

    template<class From, class To, class In>
    using G_ReplaceT = typename G_Replace<From, To, In>::Type;

    template<class From, class To, class... Args, template<class...> class Class>
    struct G_Replace<From, To, Class<Args ...>> {
        using Type = Class<G_ReplaceT<From, To, Args>...>;
    };

    template<class From, class To>
    struct G_Replace<From, To, From> {
        using Type = To;
    };
} // namespace sb