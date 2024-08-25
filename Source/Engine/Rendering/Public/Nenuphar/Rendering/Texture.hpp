#pragma once

#include "Nenuphar/Common/Common.hpp"
#include <functional>

namespace Nenuphar
{

    using Texture = UInt32;

    struct TextureInformation
    {
        Word8* Data;
        Int Format;
        Int Width;
        Int Height;
    };


}