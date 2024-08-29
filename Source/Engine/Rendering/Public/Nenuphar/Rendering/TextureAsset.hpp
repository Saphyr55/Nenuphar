#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


namespace Nenuphar
{

    struct TextureAsset : public Asset
    {
        TextureInformation Information; 
    };
    
    class TextureAssetLoader : public AssetLoader<TextureAsset>
    {
    public:
        virtual SharedRef<TextureAsset> Load(const Path& filePath,
                                             const AssetOptions&) override;

        virtual void Unload(SharedRef<TextureAsset> asset) override;
    };
    
}