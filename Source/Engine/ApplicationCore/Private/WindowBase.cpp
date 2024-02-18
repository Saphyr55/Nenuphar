#include "Nenuphar/ApplicationCore/WindowBase.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

namespace Nenuphar
{
    SharedRef<WindowBase> WindowBase::Create(WindowDefinition definition)
    {
        auto windowsApplication =
            std::dynamic_pointer_cast<WindowsApplication>(PlatformApplication::GetPlatformApplication());

        auto window =
            MakeSharedRef<WindowsWindow>(*windowsApplication, definition);

        return window;
    }
}

#else

namespace Nenuphar
{
    SharedRef<WindowBase> WindowBase::Create()
    {
        return nullptr;
    }
}

#endif

