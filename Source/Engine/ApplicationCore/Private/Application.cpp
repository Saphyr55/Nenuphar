#include "Nenuphar/ApplicationCore/Application.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include <Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp>

namespace Nenuphar
{

    SharedRef<Application> Application::Create()
    {
        return std::make_unique<WindowsApplication>();
    }

}

#else

namespace Nenuphar
{

    SharedRef<Application> Application::Create()
    {
        return nullptr;
    }

}

#endif
