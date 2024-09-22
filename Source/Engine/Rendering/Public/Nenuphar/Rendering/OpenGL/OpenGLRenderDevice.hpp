#pragma once

#include "Nenuphar/Rendering/RenderDevice.hpp"

namespace Nenuphar 
{
    class OpenGLRenderDevice : public RenderDevice
    {
    public:
        virtual void Enable() override;

        virtual SharedRef<Shader> CreateShader(const ShaderConstructOptions& options) override;

        virtual SharedRef<CommandBuffer> CreateCommandBuffer() override;

        virtual SharedRef<Texture> CreateTexture(SharedRef<ImageAsset> asset,
                                                 const SubmitTextureOption& option = {}) override;

    private:
        OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window);
        virtual ~OpenGLRenderDevice() override;

    };
}