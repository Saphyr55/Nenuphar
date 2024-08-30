#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

#ifdef NP_PLATFORM_WINDOWS

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
