#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/MeshLoader.hpp"

namespace Nenuphar
{

    class WavefrontObjParser
    {
    public:
        SharedRef<Mesh> Parse(StringView content);
    };

}