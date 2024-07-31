#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

namespace Nenuphar
{

    SharedRef<PlatformApplication> PlatformApplication::Application = nullptr;

    PlatformApplication& PlatformApplication::GetPlatformApplication()
    {
        if (!Application)
        {
#ifdef NP_PLATFORM_WINDOWS
            Application = MakeSharedRef<WindowsApplication>();
#endif
        }

        return *Application;
    }

    Application& PlatformApplication::GetApplication()
    {
        if (!Application)
        {
#ifdef NP_PLATFORM_WINDOWS
            Application = MakeSharedRef<WindowsApplication>();
#endif
        }

        return *std::reinterpret_pointer_cast<class Application>(Application);
    }

}

