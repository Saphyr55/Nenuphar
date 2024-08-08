#include "Nenuphar/Rendering/OpenGL/OpenGLRenderSystem.hpp"

#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "glad/glad.h"

namespace Nenuphar 
{

    RenderSystem& RenderSystem::Instance(GraphicsAPI type)
    {
        static auto renderSystem = MakeUnique<OpenGLRenderSystem>();

        return *renderSystem;
    }

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