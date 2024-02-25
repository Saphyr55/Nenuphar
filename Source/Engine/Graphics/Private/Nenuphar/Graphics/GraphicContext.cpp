#include "Nenuphar/Graphics/GraphicContext.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"

#ifdef NP_PLATFORM_WINDOWS

#include "Nenuphar/Graphics/Windows/WGLContext.hpp"

namespace Nenuphar
{

    Void GraphicContext::Init()
    {
        WGLContext::Init();
    }

    Ptr<GraphicContext> GraphicContext::Create(Window& window)
    {
        auto& ww = reinterpret_cast<WindowsWindow&>(window.Base());
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
