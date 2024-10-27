#include "Nenuphar/Rendering/OpenGL/OpenGLSkyboxShader.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"


namespace Nenuphar
{
    constexpr const char* GSkyboxShaderName = "Skybox";

    void SkyboxShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry)
    {
        // TODO: Better way to store this.
        uniformRegistry->Register("USkybox", Int(0));
    }

    OpenGLSkyboxShaderProgram::~OpenGLSkyboxShaderProgram()
    {   
    }

    void OpenGLSkyboxShaderProgram::Initialize()
    {
        if (m_isInitialize)
        {
            return;
        }
        
        m_delegate = ShaderCreateProgram(GSkyboxShaderName);
        m_delegate->Use();
        
        m_mainUniformRegistry = MakeSharedRef<UniformRegistry>(m_delegate);
        SkyboxShaderInitializeUniformRegistry(m_mainUniformRegistry);
        
        UInt skyboxMainBlockIndex = OpenGL_GetUniformBlock(m_delegate, GMainUniformBlockName);
        NP_GL_CHECK_CALL(glUniformBlockBinding(
            m_delegate->Id(), 
            skyboxMainBlockIndex, 
            GMainBindingBlockIndex))
            
        m_isInitialize = true;
    }

    SharedRef<Shader> OpenGLSkyboxShaderProgram::GetDelegate()
    {
        return m_delegate;
    }

    SharedRef<UniformRegistry> OpenGLSkyboxShaderProgram::GetRegistry()
    {
        NCHECK(m_isInitialize)
        return m_mainUniformRegistry;
    }


}// namespace Nenuphar