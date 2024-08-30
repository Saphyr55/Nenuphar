#pragma once

#ifndef NENUPHAR_FUNCTIONAL_HPP
#define NENUPHAR_FUNCTIONAL_HPP

#include <functional>

namespace Nenuphar
{

    constexpr auto Partial(auto&& f, auto&&... args)
    {
        return [&f, &args...]<typename... Ts>(Ts&&... lambdaArgs) {
            return std::forward<decltype(f)>(f)(
                    std::forward<decltype(args)>(args)...,
                    std::forward<Ts>(lambdaArgs)...);
        };
    }

    constexpr auto Compose(auto&& f1, auto&& f2)
    {
        return [&f1, &f2](auto&& arg) {
            return f1(f2(arg));
        };
    }

}// namespace Nenuphar

#endif
