#pragma once

#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/Shader.hpp"


namespace Nenuphar
{
    class UniformRegistry;

    enum class RenderAPI
    {
        OpenGL,
        None
    };

    class Renderer
    {
    public:
        virtual SharedRef<MainShaderProgram> GetMainShaderProgram() = 0;

        virtual Texture SubmitTexture(
            SharedRef<ImageAsset> asset, 
            const SubmitTextureOption& option = {}) const = 0;

        virtual RenderObject SubmitRenderData(
                const std::vector<Vertex>& vertices,
                const std::vector<VIndice>& indices) const = 0;

        virtual void Render(RenderObject& object) const = 0;

        virtual ~Renderer() = default;
    };

}// namespace Nenuphar
