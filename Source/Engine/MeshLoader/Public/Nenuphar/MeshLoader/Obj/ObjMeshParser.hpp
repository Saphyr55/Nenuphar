#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/MeshLoader/MeshLoader.hpp"

namespace Nenuphar
{

    class ObjParser
    {
    public:
        SharedRef<Mesh> Parse(std::string_view content);
    };

}