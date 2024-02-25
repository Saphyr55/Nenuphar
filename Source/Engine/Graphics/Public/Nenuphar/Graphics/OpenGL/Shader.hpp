#pragma once

#include <functional>
#include <memory>

#include <glad/glad.h>

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    using OpenGLProgramID = UInt;
    using OpenGLShaderID = UInt;
    using OpenGLShaderStatus = UInt;


	class OpenGLShader;


	enum OpenGLShaderType : UInt32
	{
		VertexShader   = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER
	};


	class OpenGLShaderPart final
	{

	friend class OpenGLShader;

	private:
		void Source(const char* source) const;
		void Compile() const;

	public:
		explicit OpenGLShaderPart(OpenGLShaderType type);
		~OpenGLShaderPart();

	private:
		void CheckInfo(OpenGLShaderID status) const;

	private:
		OpenGLShaderType m_shaderType;
		OpenGLShaderID m_shaderID;
	};


	class OpenGLShader final
	{

	public:

		void Use() const;

		OpenGLShaderID GetID() const { return m_programID; }

        void Link() const;

		const OpenGLShader& Attach(OpenGLShaderType st, StringView source) const;

        OpenGLShader(StringView vs, StringView fs);
        OpenGLShader();
		~OpenGLShader();

    private:
        void CheckInfo(OpenGLShaderStatus status) const;

	private:
		OpenGLProgramID m_programID = -1;
        mutable std::vector<std::unique_ptr<OpenGLShaderPart>> m_parts;
    };


    void SetupShaderProgram(OpenGLShader& program, StringView vs, StringView fs);

}
