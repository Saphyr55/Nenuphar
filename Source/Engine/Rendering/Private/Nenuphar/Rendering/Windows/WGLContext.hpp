#pragma once

#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/Windows/WindowsDeviceContext.hpp"

namespace Nenuphar
{
    
    class WGLContext : public GraphicsContext
    {
    public:
        static Void Init();

        virtual void Current() const override;

        virtual void SwapBuffers() const override;

        WGLContext(Ptr<WindowsDeviceContext> deviceContext);

        ~WGLContext();

    private:
        Ptr<WindowsDeviceContext> m_deviceContext;
        HGLRC m_context;
    };

}

#endif
