#include "Nenuphar/Rendering/OpenGL/OpenGLRenderSystem.hpp"

#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

#include <glad/glad.h>

namespace Nenuphar 
{

    RenderSystem& RenderSystem::Instance(GraphicsAPI type)
    {
        static auto renderSystem = MakeUnique<OpenGLRenderSystem>();

        return *renderSystem;
    }

    void OpenGLRenderSystem::Enable() const
    {
        NPOGL_CHECK_CALL(glEnable(GL_DEPTH_TEST));
    }

    void OpenGLRenderSystem::Clear(const Vector4f& color) const
    {
        NPOGL_CHECK_CALL(glClearColor(color.x, color.y, color.z, color.w));
        NPOGL_CHECK_CALL(glClear(OpenGLBufferMask::ColorBuffer | OpenGLBufferMask::DepthBuffer));
    }

}