#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/Uniform.hpp"

namespace Nenuphar 
{

    void MainShaderInitializeUniformRegistry(SharedRef<UniformRegistry> uniformRegistry); 

    /**
     * @brief 
     * 
     */
    class OpenGLMainShaderProgram : public MainShaderProgram
    {
    public:
        virtual void UpdateBlock(const MainUniformBlock& mainUniformBlock) override;

        virtual void UpdateProjection(const Matrix4f& projection) override;

        virtual SharedRef<UniformRegistry> GetRegistry() override;

        virtual void UpdateView(const Matrix4f& view) override;

        virtual const MainUniformBlock& UMainUniformBlock() const override; 

        virtual SharedRef<Shader> GetDelegate() override;

    public:
        // 
        void Initialize();

    private:

        struct OpenGLMainShader
        {
            MainUniformBlock UMainUniformBlock;
            SharedRef<OpenGLUniformBuffer> MainUniformBuffer;
            SharedRef<UniformRegistry> MainUniformRegistry;
            SharedRef<OpenGLShader> Delegate;
        };

        OpenGLMainShader m_OpenGLMainShader;
        Bool m_isInitialize = false;
    };

}