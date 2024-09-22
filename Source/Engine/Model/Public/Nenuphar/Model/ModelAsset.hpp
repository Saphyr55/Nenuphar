#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"


namespace Nenuphar
{
    class TOLModelLoader;

    class ModelAsset : public Asset
    {
    public:
        inline Model& GetModel();

        inline const Model& GetModel() const;

        ModelAsset(Model&& model);

    private:
        Model m_model;
    };


    // TODO: Change to a more concrete specification model file.
    struct ModelAssetOptions : AssetOptions
    {
        bool PersistTexture = false;
        SharedRef<Renderer> Renderer = nullptr;
    };


    struct TOLModelAssetOptions : ModelAssetOptions
    {
        std::optional<Path> MtlPathDir = std::nullopt;
    };

    
    class ModelAssetLoader : public AssetLoader<ModelAsset, ModelAssetOptions>
    {
    public:
        ModelAssetLoader();

        virtual SharedRef<ModelAsset> Load(
                const Path& path, const ModelAssetOptions& options) override;

        virtual void Unload(SharedRef<ModelAsset> asset) override;

    private:
        SharedRef<TOLModelLoader> m_objLoader;
    };

    inline Model& ModelAsset::GetModel()
    {
        return m_model;
    }

    inline const Model& ModelAsset::GetModel() const
    {
        return m_model;
    }

}