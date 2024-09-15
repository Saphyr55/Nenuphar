
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		NP_GL_CHECK_CALL(glGenVertexArrays(1, &m_vertexArrayId));
		Bind();
    }

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		// NP_GL_CHECK_CALL(glDeleteVertexArrays(1, &m_vertexArrayId));
    }

    void OpenGLVertexArray::Bind() const
	{
		NP_GL_CHECK_CALL(glBindVertexArray(m_vertexArrayId));
    }

	void OpenGLVertexArray::Unbind() const
	{
		NP_GL_CHECK_CALL(glBindVertexArray(0));
    }

}


