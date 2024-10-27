#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"

namespace Nenuphar 
{

    void SkyboxShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry); 

    /**
     * @brief 
     * 
     */
    class OpenGLSkyboxShaderProgram : public SkyboxShaderProgram
    {
    public:
        virtual SharedRef<UniformRegistry> GetRegistry() override;

        virtual SharedRef<Shader> GetDelegate() override;

    public:
        ~OpenGLSkyboxShaderProgram();

        void Initialize();

    private:
        SharedRef<UniformRegistry> m_mainUniformRegistry;
        SharedRef<OpenGLShader> m_delegate;
        Bool m_isInitialize = false;
    };

}