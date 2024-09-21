#include "Nenuphar/Rendering/OpenGL/OpenGLMainShader.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"


namespace Nenuphar
{
    constexpr const char* GMainShaderName = "Main";
    constexpr const char* GMainUniformBlockName = "MainUniformBlock";
    
    void MainShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry)
    {
        // TODO: Better way to store this.
        uniformRegistry
            ->Register("UModel", Matrix4f::Identity())
            .Register("UTexture", Int(0))

            .Register("UCameraPosition", Vector3f(0.0f))

            .Register("ULight.Position", Vector3f(1.0f))
            .Register("ULight.Ambient", Vector3f(0.8f))
            .Register("ULight.Diffuse", Vector3f(0.5f))
            .Register("ULight.Specular", Vector3f(1.0f))

            .Register("UMaterial.Diffuse", Vector3f(0.5f))
            .Register("UMaterial.Specular", Vector3f(1.0f))
            .Register("UMaterial.Shininess", 1.0f)
            .Register("UMaterial.SpecularTexture", Int(0))
            .Register("UMaterial.DiffuseTexture", Int(0));

    }

    void OpenGLMainShaderProgram::Initialize()
    { 
        if (m_isInitialize) 
        {
            return;
        }

        constexpr std::size_t bindingIndex = 0;
        m_OpenGLMainShader.UMainUniformBlock = MainUniformBlock();
        m_OpenGLMainShader.Delegate = ShaderCreateProgram(GMainShaderName);
        m_OpenGLMainShader.MainUniformRegistry = MakeSharedRef<UniformRegistry>(m_OpenGLMainShader.Delegate);
        MainShaderInitializeUniformRegistry(m_OpenGLMainShader.MainUniformRegistry);

        UInt blockIndex = OpenGL_GetUniformBlock(m_OpenGLMainShader.Delegate, GMainUniformBlockName);
        NP_GL_CHECK_CALL(glUniformBlockBinding(m_OpenGLMainShader.Delegate->Id(), blockIndex, 0))

        SharedRef<OpenGLUniformBuffer> ubo = MakeSharedRef<OpenGLUniformBuffer>(sizeof(MainUniformBlock));

        NCHECK(&m_OpenGLMainShader.UMainUniformBlock)

        ubo->Bind();
        ubo->BufferData(&m_OpenGLMainShader.UMainUniformBlock, OpenGLBufferUsage::DynamicDraw);
        ubo->Unbind();

        ubo->BindBufferBase(bindingIndex);
            
        m_OpenGLMainShader.MainUniformBuffer = ubo;
        
        m_isInitialize = true;
    }
    
    void OpenGLMainShaderProgram::UpdateBlock(const MainUniformBlock& mainUniformBlock)
    {
        constexpr std::size_t offset = 0;
        constexpr std::size_t size = sizeof(MainUniformBlock);

        m_OpenGLMainShader.UMainUniformBlock = mainUniformBlock;

        const void* value = &m_OpenGLMainShader.UMainUniformBlock;
        
        m_OpenGLMainShader.MainUniformBuffer->Bind();
        m_OpenGLMainShader.MainUniformBuffer->BufferSubData(offset, size, value);
        m_OpenGLMainShader.MainUniformBuffer->Unbind();
    }

    void OpenGLMainShaderProgram::UpdateProjection(const Matrix4f& projection)
    {
        m_OpenGLMainShader.UMainUniformBlock.Projection = projection;

        constexpr std::size_t offset = sizeof(Matrix4f) * 0;
        constexpr std::size_t size = sizeof(Matrix4f);

        const void* value = &m_OpenGLMainShader.UMainUniformBlock.Projection;

        m_OpenGLMainShader.MainUniformBuffer->Bind();
        m_OpenGLMainShader.MainUniformBuffer->BufferSubData(offset, size, value);
        m_OpenGLMainShader.MainUniformBuffer->Unbind();
    }

    void OpenGLMainShaderProgram::UpdateView(const Matrix4f& view)
    {
        m_OpenGLMainShader.UMainUniformBlock.View = view;

        constexpr std::size_t offset = sizeof(Matrix4f) * 1;
        constexpr std::size_t size = sizeof(Matrix4f);

        const void* value = &m_OpenGLMainShader.UMainUniformBlock.View;

        m_OpenGLMainShader.MainUniformBuffer->Bind();
        m_OpenGLMainShader.MainUniformBuffer->BufferSubData(offset, size, value);
        m_OpenGLMainShader.MainUniformBuffer->Unbind();
    }

    const MainUniformBlock& OpenGLMainShaderProgram::UMainUniformBlock() const
    {
        return m_OpenGLMainShader.UMainUniformBlock;
    } 

    SharedRef<Shader> OpenGLMainShaderProgram::GetDelegate()
    {
        return m_OpenGLMainShader.Delegate;
    }

    SharedRef<UniformRegistry> OpenGLMainShaderProgram::GetRegistry()
    {
        NCHECK(m_isInitialize)
        return m_OpenGLMainShader.MainUniformRegistry;
    }


}// namespace Nenuphar