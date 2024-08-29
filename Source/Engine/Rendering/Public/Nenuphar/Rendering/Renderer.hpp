#pragma once

#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"


namespace Nenuphar
{

    struct PersitTextureOption
    {
        AssetRegistry& Registry = AssetRegistry::Instance();
        Bool ReleaseData = true;
    };

    class Renderer
    {
    public:
        virtual Texture PersistTexture(SharedRef<TextureAsset> asset,
                                       const PersitTextureOption& option = {}) const = 0;

        virtual ModelId PersistModel(const Model& model) const = 0;

        virtual MeshId PersistMesh(const Mesh& mesh) const = 0;

        virtual void TextureModel(const MeshId& model,
                                  const Texture& texture) const = 0;

        virtual void TextureMesh(const MeshId& mesh,
                                 const Texture& texture) const = 0;

        virtual void DrawModel(const Shader& shader,
                               const ModelId& model) const = 0;

        virtual void DrawMesh(const Shader& shader,
                              const MeshId& mesh) const = 0;

    };  

}

