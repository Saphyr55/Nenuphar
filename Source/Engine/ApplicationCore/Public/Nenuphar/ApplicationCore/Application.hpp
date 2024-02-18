#pragma once

#include "WindowInteface.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class EventBus;

    class ApplicationInterface
    {
    public:
        static SharedRef<ApplicationInterface> Create();

        virtual ~ApplicationInterface() = default;

        virtual void Destroy() const = 0;

        virtual bool IsRunning() const = 0;

        virtual void Stop() = 0;

        virtual void SetRunning(bool enable) = 0;

        virtual EventBus& GetEventBus() = 0;

    };


}

