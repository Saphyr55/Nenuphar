#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    using TextureID = UInt32;

    struct DataImage
    {
        Word8* Data;
        Int Format;
        Int Width;
        Int Height;
    };


}