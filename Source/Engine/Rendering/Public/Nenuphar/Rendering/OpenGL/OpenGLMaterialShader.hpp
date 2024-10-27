#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/Uniform.hpp"

namespace Nenuphar 
{
    class OpenGLRenderDevice;

    void MaterialShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry); 

    /**
     * @brief 
     * 
     */
    class OpenGLMaterialShaderProgram : public MaterialShaderProgram
    {
    public:
        virtual SharedRef<UniformRegistry> GetRegistry() override;

        virtual SharedRef<Shader> GetDelegate() override;

    public:
        ~OpenGLMaterialShaderProgram();

        void Initialize();

    private:

        struct OpenGLMaterialShader
        {
            SharedRef<UniformRegistry> MainUniformRegistry;
            SharedRef<OpenGLShader> Delegate;
        };

        OpenGLMaterialShader m_OpenGLMainShader;
        Bool m_isInitialize = false;
    };

}