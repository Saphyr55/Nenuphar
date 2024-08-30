#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Rendering/Windows/WGLContext.hpp"

#if NP_PLATFORM_WINDOWS


namespace Nenuphar
{

    Ptr<GraphicContext> GraphicContext::Create(Window& window)
    {
        NP_CALL_ONCE(WGLContext::Init(););
        auto& ww = reinterpret_cast<WindowsWindow&>(window);
        return MakeUnique<WGLContext>(MakeUnique<WindowsDeviceContext>(ww));
    }

}// namespace Nenuphar

#else

namespace Nenuphar
{

    Ptr<GraphicContext> GraphicContext::Create(Window& window)
    {
        NCHECK(false)
        return nullptr;
    }


}// namespace Nenuphar
#endif
