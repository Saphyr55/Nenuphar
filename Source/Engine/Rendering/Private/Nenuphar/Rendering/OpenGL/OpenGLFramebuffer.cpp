#include "Nenuphar/Rendering/OpenGL/OpenGLFrameBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "glad/glad.h"


namespace Nenuphar 
{

    void OpenGLFramebuffer::Initialize()
    {
        NP_GL_CHECK_CALL(glCreateFramebuffers(1, &m_handle))
    }
    
    void OpenGLFramebuffer::Destroy()
    {
        NP_GL_CHECK_CALL(glDeleteFramebuffers(1, &m_handle))
    }

}