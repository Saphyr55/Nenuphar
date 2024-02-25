#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

namespace Nenuphar
{

    SharedRef<PlatformApplication> PlatformApplication::Application = nullptr;

    PlatformApplication& PlatformApplication::GetPlatformApplication()
    {
        if (!Application)
        {
            Application = MakeSharedRef<WindowsApplication>();
        }

        return *Application;
    }

    Application& PlatformApplication::GetApplication()
    {
        if (!Application)
        {
            Application = MakeSharedRef<WindowsApplication>();
        }

        return *std::reinterpret_pointer_cast<class Application>(Application);
    }

}

#else

#endif
