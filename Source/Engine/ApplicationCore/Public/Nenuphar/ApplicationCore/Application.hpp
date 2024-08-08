#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"

namespace Nenuphar
{

    using ApplicationId = Word16;

    class Application
    {
    public:
        virtual void Destroy() const = 0;

        virtual ApplicationId Id() const = 0;

        virtual ~Application() = default;
    };

    using ApplicationRef = SharedRef<Application>;

}

