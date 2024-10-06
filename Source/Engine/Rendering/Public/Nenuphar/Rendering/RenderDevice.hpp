#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"

#include "Nenuphar/Asset/AssetRegistry.hpp"

#include "Nenuphar/Common/Type/Type.hpp"

#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/CommandQueue.hpp"
#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/RenderHandle.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#include <vector>


namespace Nenuphar
{
    enum class RenderAPI
    {
        OpenGL,
        None
    };

    struct ShaderConstructOptions
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    struct TextureConstructOptions
    {
        AssetRegistry& Registry = AssetRegistry::Instance();
        Bool AutoRelease = true;
    };

    /**
     * @brief 
     * 
     */
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
         * @brief Create a Shader Program
         * 
         * @param options 
         * @return SharedRef<Shader> 
         */
        virtual SharedRef<Shader> CreateShader(const ShaderConstructOptions& options) = 0;

        /**
         * @brief Create a Render Handle
         * 
         * @param vertices 
         * @param indices 
         * @return SharedRef<RenderHandle> 
         */
        virtual SharedRef<RenderHandle> CreateRenderHandle(const std::vector<Vertex>& vertices,
                                                           const std::vector<VIndice>& indices) = 0;

        /**
         * @brief Create a Texture object
         * 
         * @return SharedRef<Texture> 
         */
        virtual SharedRef<Texture> CreateTexture(SharedRef<ImageAsset> asset,
                                                 const TextureConstructOptions& option = {}) = 0;

        /**
         * @brief Create a Command Buffer
         * 
         * @return SharedRef<CommandBuffer> 
         */
        virtual SharedRef<CommandBuffer> CreateCommandBuffer() = 0;

        /**
         * @brief Create a Command Queue
         * 
         * @return SharedRef<CommandQueue> 
         */
        virtual SharedRef<CommandQueue> CreateCommandQueue() = 0;

        /**
         * @brief Get the Main Shader Program
         * 
         * @return SharedRef<MainShaderProgram> 
         */
        virtual SharedRef<MainShaderProgram> GetMainShaderProgram() = 0;

        /**
         * @brief Get the Graphics Context
         * 
         * @return SharedRef<GraphicsContext> 
         */
        inline SharedRef<GraphicsContext> GetGraphicsContext()
        {
            return m_graphicsContext;
        }

    protected:
        RenderDevice(RenderAPI renderAPI, SharedRef<Window> window);
        virtual ~RenderDevice() = default;

    protected:
        RenderAPI m_api;
        SharedRef<Window> m_window;
        SharedRef<GraphicsContext> m_graphicsContext;
    };

}// namespace Nenuphar