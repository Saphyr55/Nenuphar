#pragma once

#include "Nenuphar/Rendering/Mesh.hpp"

namespace Nenuphar
{
    using ModelId = std::size_t;

    struct Model
    {
        std::vector<Mesh> Meshes;
    };

}