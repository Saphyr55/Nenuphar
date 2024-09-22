#pragma once

#include "Nenuphar/Rendering/OpenGL/OpenGLMainShader.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"

namespace Nenuphar
{

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

        virtual SharedRef<CommandQueue> CreateCommandQueue() override;

        virtual SharedRef<MainShaderProgram> GetMainShaderProgram() override;

    public:
        OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window);
        virtual ~OpenGLRenderDevice() override;

    private:
        SharedRef<OpenGLMainShaderProgram> m_mainShaderProgram;
    };
    
}// namespace Nenuphar