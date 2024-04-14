#include "Nenuphar/Rendering/OpenGL/OpenGLRenderSystem.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"

namespace Nenuphar 
{

    void OpenGLRenderSystem::Enable() const
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderSystem::Clear(const Vector4f& color) const
    {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(OpenGLBufferMask::ColorBuffer | OpenGLBufferMask::DepthBuffer);
    }

}