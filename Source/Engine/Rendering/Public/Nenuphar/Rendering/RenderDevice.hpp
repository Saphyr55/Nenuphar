#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


namespace Nenuphar
{

    struct ShaderConstructOptions
    {
        std::string VertexSource;
        std::string FragmentSource;
    };
    
    struct SubmitTextureOption
    {
        AssetRegistry& Registry = AssetRegistry::Instance();
        Bool AutoRelease = true;
    };

    class RenderDevice
    {
    public:
        /**
         * @brief 
         * 
         * @param renderAPI 
         * @param window 
         * @return SharedRef<RenderDevice> 
         */
        static SharedRef<RenderDevice> Create(RenderAPI renderAPI, SharedRef<Window> window);

        /**
         * @brief 
         * 
         */
        virtual void Enable() = 0;

        /**
         * @brief Create a Shader object
         * 
         * @param options 
         * @return SharedRef<Shader> 
         */
        virtual SharedRef<Shader> CreateShader(const ShaderConstructOptions& options) = 0;

        /**
         * @brief Create a Texture object
         * 
         * @return SharedRef<Texture> 
         */
        virtual SharedRef<Texture> CreateTexture(SharedRef<ImageAsset> asset,
                                                 const SubmitTextureOption& option = {}) = 0;

        /**
         * @brief Create a Command Buffer object
         * 
         * @return SharedRef<CommandBuffer> 
         */
        virtual SharedRef<CommandBuffer> CreateCommandBuffer() = 0;

    protected:
        RenderDevice(RenderAPI renderAPI, SharedRef<Window> window);
        virtual ~RenderDevice() = default;

    protected:
        RenderAPI m_api;
        SharedRef<Window> m_window;
        SharedRef<GraphicsContext> m_graphicsContext;
    };

}// namespace Nenuphar