#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Image.hpp"


namespace Nenuphar
{

    struct ImageAsset : public Asset
    {
        ImageDefinition Definition;
    };

    struct ImageAssetOptions : AssetOptions
    {

    };

    class ImageAssetLoader : public AssetLoader<ImageAsset, ImageAssetOptions>
    {
    public:
        virtual SharedRef<ImageAsset> Load(const Path& filePath,
                                           const ImageAssetOptions&) override;

        virtual void Unload(SharedRef<ImageAsset> asset) override;
    };

}// namespace Nenuphar