#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    struct WindowDefinition;
    class Window;
    class EventBus;
    class WindowEventHandler;

    class Application
    {

    public:

        static Ptr<Application> CreateApplication();

        virtual ~Application() = default;

        virtual void Stop() = 0;

        virtual bool IsRunning() = 0;

        virtual void SetRunning(bool isRunning) = 0;

        virtual SharedRef<Window> CreateApplicationWindow(WindowDefinition definition) = 0;
            
        virtual EventBus& GetEventBus() = 0;

        virtual WindowEventHandler& GetWindowEventHandler() = 0;

    };  

    using ApplicationPtr = Ptr<Application>;

}

