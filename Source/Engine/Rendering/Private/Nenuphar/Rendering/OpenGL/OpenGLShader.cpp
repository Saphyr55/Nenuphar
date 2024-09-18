#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Uniform.hpp"

#include <string_view>

#include <fmt/core.h>
#include <glad/glad.h>

namespace Nenuphar 
{
	
    SharedRef<OpenGLShader> ShaderCreateProgram(std::string_view name)
    {
        auto vertexFileName = String(name) + GVertexFileExtension;
        Path vertexFilepath = FromAssets("/Shaders/" + vertexFileName);
        Path::TRes vertexResult = ReadFileContent(vertexFilepath);
        NCHECK(vertexResult.HasValue())

        auto fragmentFileName = String(name) + GFragmentFileExtension;
        Path fragmentFilepath = FromAssets("/Shaders/" + fragmentFileName);
        Path::TRes fragmentResult = ReadFileContent(fragmentFilepath);
        NCHECK(fragmentResult.HasValue())

        // Create the main OpenGL shader.
        return MakeSharedRef<OpenGLShader>(vertexResult.Value(), fragmentResult.Value());
    };

	OpenGLShaderPart::OpenGLShaderPart(OpenGLShaderType shaderType) 
		: m_shaderType(shaderType)
        , m_shaderID(NP_GL_CHECK_RCALL(glCreateShader(m_shaderType)))
	{
    }

    OpenGLShaderPart::~OpenGLShaderPart()
	{
        DeleteShader(m_shaderID);
    }

	void OpenGLShaderPart::Source(const char* source) const
	{
        NP_GL_CHECK_CALL(glShaderSource(m_shaderID, 1, &source, nullptr));
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
        NP_GL_CHECK_CALL(glUseProgram(m_programID));
    }

    UniformLocation OpenGLShader::GetUniformLocation(std::string_view name) const
	{
		return NP_GL_CHECK_RCALL(glGetUniformLocation(Id(), name.data()));
	}

	void OpenGLShader::Link()
	{
		NP_GL_CHECK_CALL(glLinkProgram(m_programID));
		m_parts.clear();
		CheckInfo(GL_LINK_STATUS);
    }
	
	OpenGLShader& OpenGLShader::Attach(OpenGLShaderType st, std::string_view source)
	{
		auto shader = MakeUnique<OpenGLShaderPart>(st);

		shader->Source(source.data());
		shader->Compile();

		NP_GL_CHECK_CALL(glAttachShader(m_programID, shader->Id()));

		m_parts.push_back(std::move(shader));
        
		return *this;
    }

	void OpenGLShaderPart::CheckInfo(OpenGLShaderStatus status) const
	{
		const UInt16 size = 512;
		Int success;
		char infoLog[size];
		NP_GL_CHECK_CALL(glGetShaderiv(m_shaderID, status, &success));

		if (!success) 
        {
			NP_GL_CHECK_CALL(glGetShaderInfoLog(m_shaderID, size, nullptr, infoLog));
            NP_ERROR(OpenGLShaderPart::CheckInfo, "OpenGL Shader : {}", infoLog);
			throw std::exception();
        }
    }

	void OpenGLShader::CheckInfo(OpenGLShaderStatus status) const
	{
		const UInt16 size = 512;
		Int success;
		char infoLog[size];
		NP_GL_CHECK_CALL(glGetProgramiv(m_programID, status, &success));

		if (!success) 
        {
			NP_GL_CHECK_CALL(glGetProgramInfoLog(m_programID, size, nullptr, infoLog));
            NP_ERROR(OpenGLShader::CheckInfo, "OpenGL Program : {}", infoLog);
			throw std::exception();
        }
    }

    OpenGLShader::OpenGLShader(std::string_view vs, std::string_view fs)
        : OpenGLShader()
	{
        SetupShaderProgram(*this, vs, fs);
    }

	ShaderProgramId OpenGLShader::Id() const
	{
		return m_programID;
	}

    void SetupShaderProgram(OpenGLShader& program, std::string_view vs, std::string_view fs)
	{
        program
                .Attach(VertexShader, vs)
                .Attach(FragmentShader, fs)
                .Link();
    }

}
