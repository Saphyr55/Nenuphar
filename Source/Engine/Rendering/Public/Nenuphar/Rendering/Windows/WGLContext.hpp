#pragma once

#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/Windows/WindowsDeviceContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"

namespace Nenuphar
{
    
    class WGLContext : public GraphicContext
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