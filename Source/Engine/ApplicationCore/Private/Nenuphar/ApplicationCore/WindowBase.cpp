#include "Nenuphar/ApplicationCore/WindowBase.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

namespace Nenuphar
{

    SharedRef<WindowBase> WindowBase::Create(WindowDefinition definition)
    {
        auto& windowsApplication = reinterpret_cast<WindowsApplication&>(PlatformApplication::GetApplication());
        return MakeSharedRef<WindowsWindow>(windowsApplication, definition);
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

