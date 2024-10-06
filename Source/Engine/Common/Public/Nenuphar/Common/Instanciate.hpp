#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    template<typename T, typename ...Args>
    SharedRef<T> MakeSharedRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

}