#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"


namespace Nenuphar
{
    class TOLModelLoader;

    class ModelAsset;

    using ModelAssetRef = SharedRef<ModelAsset>;

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
        bool IsSubmit = false;
        SharedRef<RenderDevice> RenderDevice = nullptr;
    };


    struct TOLModelAssetOptions : ModelAssetOptions
    {
        std::optional<Path> MtlPathDir = std::nullopt;
        Bool AutoReleaseTextue = false;
    };


    class ModelAssetLoader : public AssetLoader<ModelAsset, ModelAssetOptions>
    {
    public:
        ModelAssetLoader();

        virtual SharedRef<ModelAsset> Load(const Path& path,
                                           const ModelAssetOptions& options) override;

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

}// namespace Nenuphar