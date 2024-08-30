#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

#ifdef NP_PLATFORM_WINDOWS

namespace Nenuphar
{

    SharedRef<WindowBase> WindowBase::Create(const WindowDefinition& definition)
    {
        auto& application = PlatformApplication::GetPlatformApplication();
        auto& windowsApplication = reinterpret_cast<WindowsApplication&>(application);
        return MakeSharedRef<WindowsWindow>(windowsApplication, definition);
    }

}// namespace Nenuphar

#else

namespace Nenuphar
{
    SharedRef<WindowBase> WindowBase::Create(const WindowDefinition& definition)
    {
        return nullptr;
    }
}// namespace Nenuphar

#endif
