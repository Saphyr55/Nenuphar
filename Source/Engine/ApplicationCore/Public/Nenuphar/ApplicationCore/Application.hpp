#pragma once

#include "WindowInterface.hpp"

namespace Nenuphar
{

    class EventBus;

    class ApplicationInterface
    {
    public:
        virtual ~ApplicationInterface() = default;

        virtual void Destroy() const = 0;

        virtual EventBus& GetEventBus() = 0;

    };

    class Application : public ApplicationInterface
    {

    };

    using ApplicationRef = SharedRef<Application>;

}

