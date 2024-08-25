#pragma once

#include <functional>
#include <memory>

#include <glad/glad.h>

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/Shader.hpp"

namespace Nenuphar
{

    using OpenGLShaderStatus = UInt;

	class OpenGLShader;


	enum OpenGLShaderType : UInt32
	{
		VertexShader   = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER
	};


	class OpenGLShaderPart
	{
    public:
        void Source(const char* source) const;

		inline OpenGLShaderType Type() const { return m_shaderType; }

        inline ShaderId Id() const { return m_shaderID; }

        void Compile() const;

        void CheckInfo(ShaderId status) const;

    public:
        explicit OpenGLShaderPart(OpenGLShaderType type);
		~OpenGLShaderPart();

	private:
		OpenGLShaderType m_shaderType;
		ShaderId m_shaderID;
	};


	class OpenGLShader : public Shader
	{
	public:
        void CheckInfo(OpenGLShaderStatus status) const;

        virtual void Use() const override;

        virtual ShaderProgramId Id() const override
        {
            return m_programID;
        }

        void Link() const;

		const OpenGLShader& Attach(OpenGLShaderType st, StringView source) const;

    public:
        OpenGLShader(StringView vs, StringView fs);
        OpenGLShader();
		~OpenGLShader();

	private:
		ShaderProgramId m_programID = -1;
        mutable std::vector<UniquePtr<OpenGLShaderPart>> m_parts;
    };


    void SetupShaderProgram(OpenGLShader& program, StringView vs, StringView fs);

}
