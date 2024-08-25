
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_vertexArrayId);
		Bind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_vertexArrayId);
	}

    void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_vertexArrayId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}


