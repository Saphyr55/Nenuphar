#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Nenuphar
{

    SharedRef<ImageAsset> ImageAssetLoader::Load(const Path& filePath,
                                                 const ImageAssetOptions& options)
    {
        SharedRef<ImageAsset> asset = MakeSharedRef<ImageAsset>();
        ImageDefinition& definition = asset->Definition;
        Int format;
        Int width;
        Int height;

        stbi_set_flip_vertically_on_load(true);

        definition.Data = stbi_load(
                filePath.GetFilePath().c_str(),
                &width,
                &height,
                &format,
                STBI_default);

        if (!definition.Data)
        {
            NP_ERROR(LoadDataImage, "Cannot load '{}' image.\n", filePath.GetFilePath());
            return nullptr;
        }

        switch (format)
        {
            case 4:
                definition.Format = ImageFormat::RGBA;
                break;
            case 3:
                definition.Format = ImageFormat::RGB;
                break;
            case 1:
                definition.Format = ImageFormat::RED;
                break;
            default: {
                NP_ERROR(LoadDataImage, "Error Load Textures: Automatic Textures type recognition failed");
                break;
            }
        }

        NCHECK(height >= 0 && width >= 0)

        definition.Height = height;
        definition.Width = width;

        return asset;
    }

    void ImageAssetLoader::Unload(SharedRef<ImageAsset> asset)
    {
        stbi_image_free(asset->Definition.Data);
    }

}// namespace Nenuphar