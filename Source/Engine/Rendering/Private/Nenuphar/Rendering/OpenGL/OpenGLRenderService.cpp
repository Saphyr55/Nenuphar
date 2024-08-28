#include "Nenuphar/Rendering/OpenGL/OpenGLRenderService.hpp"

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"

#include <glad/glad.h>


namespace Nenuphar 
{

    SharedRef<Renderer> OpenGLRenderService::GetRenderer()
    {
        return m_renderer;
    }

    void OpenGLRenderService::Enable() const
    {
        NPOGL_CHECK_CALL(glEnable(GL_DEPTH_TEST));
        NPOGL_CHECK_CALL(glEnable(GL_BLEND));
        NPOGL_CHECK_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void OpenGLRenderService::Clear(const Vector4f& color) const
    {
        NPOGL_CHECK_CALL(glClearColor(color.x, color.y, color.z, color.w));
        NPOGL_CHECK_CALL(glClear(OpenGLBufferMask::ColorBuffer
                                         | OpenGLBufferMask::DepthBuffer));
    }

    OpenGLRenderService::OpenGLRenderService()
    {
        m_renderer = MakeSharedRef<OpenGLRenderer>();
    }

    OpenGLRenderService::~OpenGLRenderService() = default;
}