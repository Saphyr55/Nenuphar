
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Nenuphar
{

    Bool LoadDataImage(const Path& path, const OnLoadTextureInformation& after)
    {
        TextureInformation dataImage{};
        Int format;

        stbi_set_flip_vertically_on_load(true);

        dataImage.Data = stbi_load(
                path.GetFilePath().c_str(),
                &dataImage.Width,
                &dataImage.Height,
                &format,
                STBI_default);

        if (!dataImage.Data)
        {
            NP_ERROR(LoadDataImage, "Cannot load '{}' image.\n", path.GetFilePath());
            return false;
        }

        switch (format)
        {
            case 4:
                dataImage.Format = ImageFormat::RGBA;
                break;
            case 3:
                dataImage.Format = ImageFormat::RGB;
                break;
            case 1:
                dataImage.Format = ImageFormat::RED;
                break;
            default: {
                NP_ERROR(LoadDataImage, "Error Load Textures: Automatic Textures type recognition failed");
                return false;
            }
        }

        after(dataImage);

        stbi_image_free(dataImage.Data);

        return true;
    }

}