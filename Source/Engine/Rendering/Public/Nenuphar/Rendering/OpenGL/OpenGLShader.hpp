#pragma once

#include "Nenuphar/Rendering/Shader.hpp"

#include <glad/glad.h>

namespace Nenuphar
{
    constexpr const char* GVertexFileExtension = ".Vertex.glsl";
    constexpr const char* GFragmentFileExtension = ".Fragment.glsl";

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
	    virtual void Use() const override;

        virtual UniformLocation GetUniformLocation(std::string_view name) const override;

        virtual ShaderProgramId Id() const override;

	public:
        void CheckInfo(OpenGLShaderStatus status) const;

        void Link();
	
		OpenGLShader& Attach(OpenGLShaderType st, StringView source);

    public:
        OpenGLShader(StringView vs, StringView fs);
        OpenGLShader();
		~OpenGLShader();

	private:
		ShaderProgramId m_programID = -1;
        std::vector<UniquePtr<OpenGLShaderPart>> m_parts;
    };

	//
	SharedRef<OpenGLShader> ShaderCreateProgram(std::string_view shaderName);

	// 
    void SetupShaderProgram(OpenGLShader& program, StringView vs, StringView fs);

}
