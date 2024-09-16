#pragma once

#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/Core/IO/Console.hpp"

namespace Nenuphar 
{
    class WindowsConsole : public Console
    {
    public:
        virtual void WriteMessage(std::string message) override;

    };

}

#endif