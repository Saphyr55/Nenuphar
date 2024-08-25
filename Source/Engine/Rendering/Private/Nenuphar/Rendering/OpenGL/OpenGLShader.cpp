#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

#include <fmt/core.h>

namespace Nenuphar 
{

	OpenGLShaderPart::OpenGLShaderPart(OpenGLShaderType shaderType) 
		: m_shaderType(shaderType)
        , m_shaderID(NPOGL_CHECK_RCALL(glCreateShader(m_shaderType)))
	{
    }

    OpenGLShaderPart::~OpenGLShaderPart()
	{
        DeleteShader(m_shaderID);
    }

	void OpenGLShaderPart::Source(const char* source) const
	{
        NPOGL_CHECK_CALL(glShaderSource(m_shaderID, 1, &source, nullptr));
    }

	void OpenGLShaderPart::Compile() const
	{
        CompileShader(m_shaderID);
        CheckInfo(GL_COMPILE_STATUS);
    }

	OpenGLShader::OpenGLShader()
	{
		m_programID = CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		DeleteProgram(m_programID);
	}

	void OpenGLShader::Use() const
	{
        NPOGL_CHECK_CALL(glUseProgram(m_programID));
    }

	void OpenGLShader::Link() const
	{
		NPOGL_CHECK_CALL(glLinkProgram(m_programID));
		m_parts.clear();
		CheckInfo(GL_LINK_STATUS);
    }

	const OpenGLShader& OpenGLShader::Attach(
        OpenGLShaderType st, 
        StringView source) const
	{
		auto shader = MakeUnique<OpenGLShaderPart>(st);

		shader->Source(source.data());
		shader->Compile();

		NPOGL_CHECK_CALL(glAttachShader(m_programID, shader->Id()));

		m_parts.push_back(std::move(shader));
        
		return *this;
    }

	void OpenGLShaderPart::CheckInfo(OpenGLShaderStatus status) const
	{
		const UInt16 size = 512;
		Int success;
		char infoLog[size];
		NPOGL_CHECK_CALL(glGetShaderiv(m_shaderID, status, &success));

		if (!success) 
        {
			NPOGL_CHECK_CALL(glGetShaderInfoLog(m_shaderID, size, nullptr, infoLog));
            NP_ERROR(OpenGLShaderPart::CheckInfo, "OpenGL Shader : {}", infoLog);
			throw std::exception();
        }
    }

	void OpenGLShader::CheckInfo(OpenGLShaderStatus status) const
	{
		const UInt16 size = 512;
		Int success;
		char infoLog[size];
		NPOGL_CHECK_CALL(glGetProgramiv(m_programID, status, &success));

		if (!success) 
        {
			NPOGL_CHECK_CALL(glGetProgramInfoLog(m_programID, size, nullptr, infoLog));
            NP_ERROR(OpenGLShader::CheckInfo, "OpenGL Program : {}", infoLog);
			throw std::exception();
        }
    }

    OpenGLShader::OpenGLShader(StringView vs, StringView fs)
        : OpenGLShader()
	{
        SetupShaderProgram(*this, vs, fs);
    }

    void SetupShaderProgram(OpenGLShader& program, StringView vs, StringView fs)
	{
        program
                .Attach(VertexShader, vs)
                .Attach(FragmentShader, fs)
                .Link();
    }

}
