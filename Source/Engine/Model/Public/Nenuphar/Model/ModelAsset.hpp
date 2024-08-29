#pragma once

#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"

namespace Nenuphar
{

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
    struct ModelAssetOptions : public AssetOptions 
    {
        // TODO: MtlPathDir must not be here. 
        std::optional<Path> MtlPathDir = std::nullopt;
    };

    
    class ModelAssetLoader : public AssetLoader<ModelAsset, ModelAssetOptions>
    {
    public:
        virtual SharedRef<ModelAsset> Load(
                const Path& path, const ModelAssetOptions& options) override;

        virtual void Unload(SharedRef<ModelAsset> asset) override;

    private:
        TOLModelLoader m_objLoader;
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