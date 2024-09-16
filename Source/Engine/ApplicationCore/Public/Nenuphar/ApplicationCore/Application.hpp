#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    using ApplicationId = UInt16;

    class Application
    {
    public:
        virtual Double GetAbsoluteTime() const = 0;

        virtual void Destroy() const = 0;

        virtual ApplicationId Id() const = 0;

        virtual ~Application() = default;
    };

    using ApplicationRef = SharedRef<Application>;

}

