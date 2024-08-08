#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/Rendering/Windows/WGLContext.hpp"

namespace Nenuphar
{

    Ptr<GraphicContext> GraphicContext::Create(Window& window)
    {
        NP_CALL_ONCE( WGLContext::Init(); );
        auto& ww = reinterpret_cast<WindowsWindow&>(window);
        return MakeUnique<WGLContext>(MakeUnique<WindowsDeviceContext>(ww));
    }

}

#else

namespace Nenuphar
{

    Void GraphicContext::Init()
    {
        NP_ASSERT("Enable to init device context.", false);
    }

    Ptr<GraphicContext> GraphicContext::Create(DeviceContext& deviceContext)
    {
        NP_ASSERT("Enable to create device context.", false);
    }

}
#endif

