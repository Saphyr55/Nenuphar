#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    struct WindowDefinition;
    class Window;

    class Application
    {

    public:

        virtual ~Application() = default;

        virtual bool IsRunning() = 0;

        virtual void SetRunning(bool isRunning) = 0;

        virtual SharedRef<Window> CreateApplicationWindow(WindowDefinition definition) = 0;

    };

}

