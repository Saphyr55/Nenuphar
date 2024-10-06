#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"

namespace Nenuphar
{

    SharedRef<RenderDevice> RenderDevice::Create(RenderAPI renderAPI, SharedRef<Window> window)
    {
        switch (renderAPI)
        {
            case RenderAPI::OpenGL: {
                return MakeSharedRef<OpenGLRenderDevice>(renderAPI, window);
            }
            case RenderAPI::None: {
                NCHECK(false);
                return nullptr;
            }
        }
    }

    RenderDevice::RenderDevice(RenderAPI renderAPI, SharedRef<Window> window)
        : m_window(window)
        , m_api(renderAPI)
    {
        m_graphicsContext = GraphicsContext::Create(m_api, m_window);
    }

}// namespace Nenuphar