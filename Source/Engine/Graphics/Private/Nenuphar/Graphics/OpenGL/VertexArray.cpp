
#include "Nenuphar/Graphics/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_vertexArrayID);
		Bind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}

    void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_vertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}


