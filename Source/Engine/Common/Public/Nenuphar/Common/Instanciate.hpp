#pragma once

#include "Type/Type.hpp"

namespace Nenuphar
{

    template<typename T, typename ...Args>
    constexpr SharedRef<T> MakeSharedRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename ...Args>
    constexpr Ptr<T> MakeUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

}