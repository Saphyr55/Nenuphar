#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMaterialShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLSkyboxShader.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"

namespace Nenuphar
{
    constexpr const char* GMainUniformBlockName = "MainUniformBlock";
    constexpr std::size_t GMainBindingBlockIndex = 0; 

    class OpenGLRenderDevice final : public RenderDevice
    {
    public:
        virtual void Enable() override;

        virtual SharedRef<Shader> CreateShader(const ShaderConstructOptions& options) override;
        
        virtual SharedRef<RenderHandle> CreateRenderHandle(const std::vector<Vertex>& vertices,
                                                           const std::vector<VIndice>& indices) override;

        virtual SharedRef<Texture> CreateTexture(SharedRef<ImageAsset> asset,
                                                 const TextureConstructOptions& option = {}) override;

        virtual SharedRef<CommandBuffer> CreateCommandBuffer() override;

        virtual RenderCommand CreateProjectionViewCommand(const Matrix4f& projection, const Matrix4f& view) override;
        
        virtual SharedRef<CommandQueue> CreateCommandQueue() override;

        virtual SharedRef<Skybox> CreateSkybox(const std::array<SharedRef<ImageAsset>, 6>& faces) override;

        virtual SharedRef<MaterialShaderProgram> GetMaterialShaderProgram() override;

        virtual SharedRef<SkyboxShaderProgram> GetSkyboxShaderProgram() override;

    public:
        OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window);
        virtual ~OpenGLRenderDevice() override;

    private:
        MainUniformBlock m_uMainUniformBlock;
        SharedRef<OpenGLUniformBuffer> m_mainUniformBuffer;
        SharedRef<OpenGLSkyboxShaderProgram> m_skyboxShaderProgram;
        SharedRef<OpenGLMaterialShaderProgram> m_mainShaderProgram;
    };
    
}// namespace Nenuphar