#include "Nenuphar/Rendering/OpenGL/OpenGLMaterialShader.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"


namespace Nenuphar
{
    constexpr const char* GMaterialShaderName = "Material";
    
    void MaterialShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry)
    {
        // TODO: Better way to store this.
        uniformRegistry
            ->Register("UModel", Matrix4f::Identity())
            
            .Register("UCameraPosition", Vector3f(0.0f))

            .Register("ULight.Position", Vector3f(0.0f))
            .Register("ULight.Ambient", Vector3f(0.1f))
            .Register("ULight.Diffuse", Vector3f(0.5f))
            .Register("ULight.Specular", Vector3f(1.0f))

            .Register("UMaterial.Textures[0]", Int(0))
            .Register("UMaterial.Textures[1]", Int(0))
            .Register("UMaterial.ArraySize", 0)
            .Register("UMaterial.Diffuse", Vector3f(0.5f))
            .Register("UMaterial.Specular", Vector3f(1.0f))
            .Register("UMaterial.Shininess", 1.0f);
    }

    OpenGLMaterialShaderProgram::~OpenGLMaterialShaderProgram()
    {
    }

    void OpenGLMaterialShaderProgram::Initialize()
    { 
        if (m_isInitialize) 
        {
            return;
        }

        constexpr std::size_t bindingIndex = 0;
        m_OpenGLMainShader.Delegate = ShaderCreateProgram(GMaterialShaderName);        
        m_OpenGLMainShader.MainUniformRegistry = MakeSharedRef<UniformRegistry>(m_OpenGLMainShader.Delegate);
        MaterialShaderInitializeUniformRegistry(m_OpenGLMainShader.MainUniformRegistry);
        
        m_isInitialize = true;
    }
    
    SharedRef<Shader> OpenGLMaterialShaderProgram::GetDelegate()
    {
        return m_OpenGLMainShader.Delegate;
    }

    SharedRef<UniformRegistry> OpenGLMaterialShaderProgram::GetRegistry()
    {
        NCHECK(m_isInitialize)
        return m_OpenGLMainShader.MainUniformRegistry;
    }


}// namespace Nenuphar