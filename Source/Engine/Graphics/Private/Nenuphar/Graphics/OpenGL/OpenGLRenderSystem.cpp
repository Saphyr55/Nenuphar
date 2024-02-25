#include "Nenuphar/Graphics/OpenGL/OpenGLRenderSystem.hpp"
#include "Nenuphar/Graphics/OpenGL/OpenGL.hpp"

namespace Nenuphar 
{

    void OpenGLRenderSystem::Enable()
    {

    }

    void OpenGLRenderSystem::Clear() 
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(OpenGLBufferMask::ColorBuffer | OpenGLBufferMask::DepthBuffer);
    }

}