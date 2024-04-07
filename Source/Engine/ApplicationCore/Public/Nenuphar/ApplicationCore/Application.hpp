#pragma once

#include "Nenuphar/ApplicationCore/WindowInterface.hpp"

namespace Nenuphar
{

    using ApplicationID = Word16;

    class Application
    {
    public:
        virtual void Destroy() const = 0;

        virtual ApplicationID Id() const = 0;

        virtual ~Application() = default;
    };

    using ApplicationRef = SharedRef<Application>;

}

