#pragma once

#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{

    enum class ImageFormat : Int
    {
        RED,
        RG,
        RGB,
        RGBA
    };

    struct ImageDefinition
    {
        Word8* Data;
        ImageFormat Format;
        UInt Width;
        UInt Height;
    };

}