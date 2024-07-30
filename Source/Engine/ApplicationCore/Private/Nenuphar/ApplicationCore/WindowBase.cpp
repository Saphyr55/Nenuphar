#include "Nenuphar/ApplicationCore/WindowBase.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

namespace Nenuphar
{

    SharedRef<WindowBase> WindowBase::Create(WindowDefinition definition, PlatformApplication& app)
    {
        auto& windowsApplication = reinterpret_cast<WindowsApplication&>(app);
        return MakeSharedRef<WindowsWindow>(windowsApplication, definition);
    }

}

#else

namespace Nenuphar
{
    SharedRef<WindowBase> WindowBase::Create(WindowDefinition definition, PlatformApplication& app)
    {
        return nullptr;
    }
}

#endif

