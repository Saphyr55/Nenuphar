
#include "Nenuphar/Graphics/OpenGL/VertexArray.hpp"

namespace Nenuphar
{

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vertexArrayID);
		Bind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}

    void VertexArray::Bind() const
	{
		glBindVertexArray(m_vertexArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}


