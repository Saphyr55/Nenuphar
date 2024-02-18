#pragma once

#include "Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class EventBus;

    class Application
    {
    public:
        static SharedRef<Application> Create();

        virtual ~Application() = default;

        virtual void Destroy() const = 0;

        virtual bool IsRunning() const = 0;

        virtual void Stop() = 0;

        virtual void SetRunning(bool enable) = 0;

        virtual EventBus& GetEventBus() = 0;

    };


}

