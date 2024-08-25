
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		NPOGL_CHECK_CALL(glGenVertexArrays(1, &m_vertexArrayId));
		Bind();
    }

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		NPOGL_CHECK_CALL(glDeleteVertexArrays(1, &m_vertexArrayId));
    }

    void OpenGLVertexArray::Bind() const
	{
		NPOGL_CHECK_CALL(glBindVertexArray(m_vertexArrayId));
    }

	void OpenGLVertexArray::Unbind() const
	{
		NPOGL_CHECK_CALL(glBindVertexArray(0));
    }

}


