#include "Nenuphar/Rendering/TextureAsset.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Nenuphar
{

    SharedRef<TextureAsset> TextureAssetLoader::Load(const Path& filePath) const
    {
        SharedRef<TextureAsset> asset = MakeSharedRef<TextureAsset>();
        TextureInformation& info = asset->Information;
        Int format;

        stbi_set_flip_vertically_on_load(true);

        info.Data = stbi_load(
                filePath.GetFilePath().c_str(),
                &info.Width,
                &info.Height,
                &format,
                STBI_default);

        if (!info.Data)
        {
            NP_ERROR(LoadDataImage, "Cannot load '{}' image.\n", filePath.GetFilePath());
            return nullptr;
        }

        switch (format)
        {
            case 4:
                info.Format = ImageFormat::RGBA;
                break;
            case 3:
                info.Format = ImageFormat::RGB;
                break;
            case 1:
                info.Format = ImageFormat::RED;
                break;
            default:
            {
                NP_ERROR(LoadDataImage, "Error Load Textures: Automatic Textures type recognition failed");
                break;
            }
        }

        return asset;
    }

    void TextureAssetLoader::Unload(SharedRef<TextureAsset> asset) const
    {
        stbi_image_free(asset->Information.Data);
    }

}