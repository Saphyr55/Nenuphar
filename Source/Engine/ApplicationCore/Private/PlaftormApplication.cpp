#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

#ifdef NP_PLATFORM_WINDOWS
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

namespace Nenuphar
{

    PlatformApplication& PlatformApplication::GetPlatformApplication()
    {
        static SharedRef<PlatformApplication> platformApplication =
            MakeSharedRef<WindowsApplication>();

        return *platformApplication;
    }

}
#else


#endif
