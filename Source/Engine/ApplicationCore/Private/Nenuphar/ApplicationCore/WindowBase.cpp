#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"

#ifdef NP_PLATFORM_WINDOWS

namespace Nenuphar
{
    
    SharedRef<WindowBase> WindowBase::Create(const WindowDefinition& definition)
    {
        NCHECK(AppGetCurrent())
        NCHECK(AppGetCurrent()->GetPlatformApplication())
        
        PlatformApplication& platformApp = *AppGetCurrent()->GetPlatformApplication();
        WindowsApplication& windowsApplication = static_cast<WindowsApplication&>(platformApp);
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
