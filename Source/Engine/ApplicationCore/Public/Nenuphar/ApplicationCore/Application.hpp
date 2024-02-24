#pragma once

#include "WindowInterface.hpp"

namespace Nenuphar
{

    class Application
    {
    public:
        virtual void Destroy() const = 0;

        virtual ~Application() = default;
    };

    using ApplicationRef = SharedRef<Application>;

}

