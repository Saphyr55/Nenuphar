#pragma once

#include "Nenuphar/Common/Common.hpp"
#include <functional>

namespace Nenuphar
{

    using Texture = UInt32;
    using TextureUnit = UInt32;

    struct TextureIdentication
    {
        Texture Handle;
        TextureUnit Unit;
    };

    struct TextureInformation
    {
        Word8* Data;
        Int Format;
        Int Width;
        Int Height;
    };


}