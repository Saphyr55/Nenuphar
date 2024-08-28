#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"

#include <functional>

namespace Nenuphar
{

    using Texture = UInt32;
    using TextureUnit = UInt32;

    enum class ImageFormat : Int
    {
        RED,
        RGB,
        RGBA
    };

    
    struct TextureIdentication
    {
        Texture Handle;
        TextureUnit Unit;
    };

    
    struct TextureInformation
    {
        Word8* Data;
        ImageFormat Format;
        Int Width;
        Int Height;
    };

    
    using OnLoadTextureInformation = std::function<void(const TextureInformation&)>;

    


    /**
     *
     */
    Bool LoadDataImage(const Path& path, const OnLoadTextureInformation& after);
    
}