#pragma once

#include "Nenuphar/Graphics/GraphicContext.hpp"
#include "Nenuphar/Graphics/Windows/WindowsDeviceContext.hpp"
#include "Nenuphar/Graphics/OpenGL/OpenGL.hpp"

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